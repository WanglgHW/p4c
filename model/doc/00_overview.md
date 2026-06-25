# Tofino Resource Allocation via MILP — Project Overview

**Document set:** `model/doc/00..07`
**Source tree:** `model/include`, `model/src`
**Target compiler:** `backends/tofino/bf-p4c` (Intel/Barefoot Tofino & Tofino2 backend of `p4c`)
**Solver:** [SCIP](https://www.scipopt.org/) (Solving Constraint Integer Programs)

---

## 1. Motivation

The Tofino backend (`bf-p4c`) compiles a P4 program into a configuration for the
Protocol Independent Switch Architecture (PISA) reconfigurable match-action
pipeline. The hardest part of this compilation is **physical resource
allocation**: deciding how the program's logical entities (fields, tables,
actions, hash computations) map onto a fixed, heavily constrained set of physical
resources (PHV containers, MAU stages, SRAM/TCAM, VLIW action ALUs, input
crossbar, hash units, …).

Today `bf-p4c` solves these problems with a set of *greedy + backtracking +
heuristic* allocators:

| Problem | Backend pass | Source |
|---|---|---|
| PHV (field → container) allocation | `PHV_AnalysisPass` / `AllocatePHV` | `bf-p4c/phv/allocate_phv.cpp` |
| Table placement (table → stage) | `TablePlacement` | `bf-p4c/mau/table_placement.cpp` (6300+ LOC) |
| Memory allocation (SRAM/TCAM/mapram) | `Memories` | `bf-p4c/mau/memories.cpp` |
| Input crossbar allocation | `IXBar` | `bf-p4c/mau/tofino/input_xbar.cpp` |
| VLIW / instruction memory | `InstructionMemory` | `bf-p4c/mau/instruction_memory.cpp` |
| Action data bus / format | `ActionDataBus`, `ActionData::Format` | `bf-p4c/mau/action_data_bus.cpp` |

These passes are **locally optimal at best**, frequently backtrack, and can fail
to fit programs that are in fact feasible. They also make no attempt at a global
objective (minimize stages, minimize power, balance PHV pressure).

This project replaces (or augments) those heuristics with a **single
mathematical optimization model** that captures the resource constraints exactly
and is solved to (near-)optimality by SCIP.

## 2. Goals

1. **Analyze** the Tofino backend and enumerate every programmable resource and
   the constraints/relations among them (Doc 01, Doc 02).
2. **Model** resource allocation as Mixed-Integer Linear Programs — primarily
   **Binary ILP (BILP)** for assignment decisions, with auxiliary integer/continuous
   variables — see Doc 03. Every constraint formula is annotated with the exact
   device specification constant it derives from and the source file/line.
3. **Extract** model input parameters directly from the backend midend IR
   (`IR::MAU::*`, `PhvInfo`, `DependencyGraph`, `LayoutChoices`, device specs) —
   see Doc 04.
4. **Solve** with SCIP and translate the optimal/feasible solution back into the
   backend's native data structures (`PHV::ConcreteAllocation`,
   `TableResourceAlloc`, stage assignments) so the remaining compiler stages
   (assembly emission, `bf-asm`) proceed unchanged — see Doc 05, Doc 06.
5. **Deliver** a clean C++ interface (`model/include/ralloc/resource_model.h`)
   that the backend can call, plus an out-of-process / in-process SCIP backend.

## 3. Scope & strategy

Resource allocation on Tofino is too large to solve as one monolithic MILP for
realistic programs (thousands of field slices × hundreds of containers ×
hundreds of tables × 12–20 stages produces millions of binary variables). The
design therefore uses **staged decomposition** that mirrors the natural
dependency order of the hardware, while still letting each sub-model be solved
optimally:

```
   ┌────────────────────────────────────────────────────────────────┐
   │ M0  Device spec + IR ingestion  (parameters, sets, costs)        │
   └────────────────────────────────────────────────────────────────┘
                 │
   ┌─────────────▼──────────┐     ┌──────────────────────────────┐
   │ M1  PHV allocation MILP │◄───►│  feedback: PHV pressure,     │
   │  (field slice→container)│     │  container availability      │
   └─────────────┬──────────┘     └──────────────────────────────┘
                 │ alloc slices
   ┌─────────────▼───────────────────────────────────────────────┐
   │ M2  MAU placement + memory MILP                              │
   │  (table→stage, logical-id, SRAM/TCAM/mapram, ixbar, ALUs)    │
   └─────────────┬───────────────────────────────────────────────┘
                 │ per-table per-stage resources
   ┌─────────────▼───────────────────────────────────────────────┐
   │ M3  VLIW / action MILP                                       │
   │  (action→imem row+color, action-data-bus slots)             │
   └─────────────┬───────────────────────────────────────────────┘
                 │
   ┌─────────────▼──────────┐
   │ M4  Write-back to bf-p4c │
   └────────────────────────┘
```

Each `Mi` is a self-contained MILP with a documented variable/constraint set.
They are linked by a small number of *coupling parameters* (Doc 02 §6). A
"global" mode that fuses M1+M2+M3 into one model is described as an optional
research extension (Doc 03 §9) but is **not** the default because of size.

## 4. Document map (phases)

| File | Phase | Contents |
|---|---|---|
| `00_overview.md` | — | This file. |
| `01_resource_analysis.md` | Analysis | Every Tofino programmable resource, exact spec numbers, source locations. |
| `02_constraints_relations.md` | Analysis | Constraint catalogue + inter-resource relations / coupling. |
| `03_model_formulation.md` | Model | Full MILP/BILP formulation: sets, parameters, variables, objective, constraints (formulas). |
| `04_input_extraction.md` | Integration | How each parameter is read from the bf-p4c midend IR. |
| `05_scip_integration.md` | Solver | SCIP encoding, decomposition, warm-start, performance. |
| `06_compiler_interface.md` | Integration | The C++ API, pass insertion points, write-back, fallback. |
| `07_implementation_plan.md` | Plan | Milestones, file-by-file work breakdown, testing & validation. |
| `MANUAL.md` | Operations | **User manual** — build, enable (`--use-ralloc`), run, log, troubleshoot. |

> **Status:** implemented and **built/tested in-tree against SCIP** — the pass
> ingests real IR and SCIP solves the MAU+VLIW model to optimality. It ships in
> **advisory mode** (solves + logs, legacy emits the binary; a proven no-op on
> output); committing the placement awaits the memory-realization step (Doc 06
> §4.1, Doc 07 P2). See `MANUAL.md`.

## 5. Source deliverables (this repository)

```
model/
├── doc/                      ← all documents (this set)
├── include/ralloc/
│   ├── resource_model.h      ← MAIN public interface API (Doc 06)
│   ├── device_spec.h         ← device resource constants (mirrors bf-p4c specs)
│   ├── phv_model.h           ← M1 PHV model builder
│   ├── mau_model.h           ← M2 MAU/stage/memory model builder
│   ├── vliw_model.h          ← M3 VLIW/action model builder
│   ├── scip_solver.h         ← SCIP backend abstraction
│   ├── compiler_bridge.h     ← IR ingestion + write-back to bf-p4c
│   └── ralloc_model_pass.h   ← BFN::RallocModelPass (the hosting pass)
├── src/
│   ├── model/                ← model builders + facade + device spec
│   ├── solver/               ← LinearModel + SCIP backend
│   └── bridge/               ← compiler_bridge + ralloc_model_pass + spec_check
├── test/                     ← structural unit test
├── CMakeLists.txt
└── README.md
```

Compiler-side wiring (outside `model/`): `--use-ralloc` in
`backends/tofino/bf-p4c/bf-p4c-options.{h,cpp}`, the gated `&table_alloc` entry
in `backend.cpp`, and the `ralloc_bridge` library in that backend's
`CMakeLists.txt`.

## 6. Non-goals

- Parser/deparser state allocation, CLOT allocation, and long-branch tags are
  *modeled as fixed inputs* (read from earlier passes), not optimized here
  (extension noted in Doc 03 §9).
- We do not re-implement the P4 frontend or IR. The model consumes the existing
  `IR::BFN::Pipe`.
- This is a **design + interface** deliverable. The `.cpp` files are documented
  skeletons that compile against the declared API; the numerical model logic is
  specified completely in Doc 03 for implementation.
