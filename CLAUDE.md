# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

This is a **fork of the P4C reference compiler** (p4lang/p4c) carrying substantial
local work on top of upstream. The standard P4C pipeline is *frontend → midend →
target backend*; the goal of P4C's design is to make adding backends easy. The
fork-specific additions below are the parts that differ from upstream and are
where most active work happens.

`AGENTS.md` (root, and per-backend `backends/*/AGENTS.md`) is the authoritative,
detailed contributor guide — read it for build/test/style specifics. This file
captures the big picture and the fork-specific pieces that span multiple dirs.

## Fork-specific architecture

- **ANTLR4 frontend (`frontends/p4-antlr4/`, runtime `tools/antlr4/`).** The
  ANTLR4 grammar parser is the *default and only* top-level P4-16 parser; the old
  flex/bison P4 parser is gone. `flex`/`bison` are still required but **only** for
  `tools/ir-generator/` (which parses `.def` IR files), not for user P4. The
  vendored ANTLR4 C++ runtime builds as the `antlr4_static` library. Grammar files
  (`P4Lexer.g4`, `P4Parser.g4`) and generated parser/visitor sources also live in
  the root `p4-antlr4/` directory.

- **DSLX backend (`backends/dslx-translator/`).** Translates P4 (post-midend) to
  Google XLS DSLX. Entry point `run_dslx_backend(...)` in `dslxBackend.{h,cpp}`;
  standalone driver `p4c-dslx.cpp`; `verify_dslx.py` validates output. Targets
  TNA/T2NA. Used both standalone and wired into the Tofino backend. Built by
  default (`ENABLE_DSLX=ON`); produces the `dslx-translator` lib + `p4c-dslx`
  binary.

- **Tofino backend (`backends/tofino/bf-p4c/`).** Barefoot/Tofino target
  (`IR::BFN::*` / `IR::MAU::*` nodes). See its `AGENTS.md`.

- **MILP/OR-Tools MAU resource allocator (`model/`, `--use-ralloc`).** Experimental
  table-placement allocator solved with Google OR-Tools (CP-SAT for the all-discrete
  ralloc models, MPSolver for mixed ones). In the Tofino backend, `--use-ralloc` (see
  `backends/tofino/bf-p4c/bf-p4c-options.cpp`, `backend.cpp:~450`) swaps the
  classic table placement for the MILP allocator. `model/run_ralloc.py` drives it.
  Requires `ENABLE_TOFINO=ON` and OR-Tools (`find_package(ortools CONFIG)`); without
  OR-Tools it degrades to an `.lp`/MPS exporter. OR-Tools is **not** linked into
  `p4c-barefoot` by default (its own abseil/protobuf/re2 collide with p4c's), so
  solving normally happens out of process in `ralloc-solve` via the decoupled flow
  (`--ralloc-emit` → `ralloc-solve` → `--ralloc-resume`); in-process solving is
  opt-in with `-DP4C_USE_PREINSTALLED_ABSEIL=ON -DRALLOC_INPROCESS_SOLVER=ON`.
  It is a **strictly optional optimizer** that falls back to the legacy allocator on
  any infeasibility/timeout/error, and today runs in *advisory mode* (solves + logs
  the optimal placement; legacy still emits the binary, so it's a proven no-op on
  output). Committing the MILP placement is gated behind the `RALLOC_COMMIT` compile
  define. The allocator also builds fully standalone (no compiler):
  `cmake -S model -B model/build [-DCMAKE_PREFIX_PATH=/opt/homebrew]`, then
  `cmake --build model/build`, `cmake --build model/build --target ralloc_tests` and
  `ctest --test-dir model/build`. Deep design docs in `model/doc/` and root
  `AGENTS.md`.

- **MiniZinc edition of the allocator (`model-minizinc/`).** A parallel copy of
  `model/` whose only difference is the solver backend: the same solver-agnostic
  `LinearModel` is serialized by `LinearModel::toMiniZincString` to a `.mzn` file
  and handed to an external `minizinc` process with a CP-SAT FlatZinc backend
  (`minizinc_solver.{h,cpp}` in place of `ortools_solver.{h,cpp}`). Consequently
  it has **no build- or link-time solver dependency** — availability is a runtime
  probe of the `minizinc` binary (`$RALLOC_MINIZINC`, solver tag
  `$RALLOC_MINIZINC_SOLVER`, default `cp-sat`). It is **standalone only**: the
  in-tree `ralloc_bridge` in `backends/tofino/bf-p4c/CMakeLists.txt` hardcodes
  `${CMAKE_SOURCE_DIR}/model`, so `model-minizinc/` is never compiled into
  `p4c-barefoot`. Build/test: `cmake -S model-minizinc -B model-minizinc/build &&
  cmake --build model-minizinc/build && ctest --test-dir model-minizinc/build`.
  Everything outside `src/solver/` is a near-duplicate of `model/` — **a change to
  the shared model core, JSON seam, device spec, or docs usually has to be made in
  both trees**.

## IR generation: two modes selected by `ENABLE_TOFINO`

The `ir-generated` translation unit (the `IR::*` node classes) is produced one of
two ways, picked automatically in the top-level `CMakeLists.txt`. Both modes land
sources under `${P4C_BINARY_DIR}/ir/`, so `#include "ir/ir-generated.h"` resolves
identically.

- **`ENABLE_TOFINO=ON` → build-time generation.** `tools/ir-generator`
  (`irgenerator`) parses all `.def` files — core IR **plus** Tofino extensions
  under `backends/tofino/bf-p4c/ir/` — and emits `ir-generated.{h,cpp}` +
  `gen-tree-macro.h` via the `genIR` target. Required for Tofino, whose
  `IR::BFN::*`/`IR::MAU::*` nodes exist only in those `.def` files.
- **`ENABLE_TOFINO=OFF` (bmv2 + other open-source backends) → static IR.** The
  pre-generated, hand-split files in **`ir/static-ir/`** (core/frontend nodes
  only) are staged in at configure time. No `irgenerator` is built.

**If you change an IR `.def` file**, the static copies in `ir/static-ir/` must be
regenerated to match (build once with `ENABLE_TOFINO=ON` and copy
`build/ir/ir-generated*` across), or keep `.def` edits Tofino-only.

## Build, test, develop

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release   # configure (add -DENABLE_TOFINO=ON for Tofino/IR .def work)
cmake --build build                          # compile
cmake --build build --target check           # full test suite
```

`ENABLE_TOFINO` and `ENABLE_DSLX` are dependent options gated on
`ENABLE_CONTROL_PLANE` — with it off they are forced off regardless of what you
pass. `ENABLE_TOFINO` defaults to OFF, `ENABLE_DSLX` to ON. Two
build trees are already configured in the working copy — reuse them instead of
reconfiguring: **`build/`** (Release, `ENABLE_TOFINO=ON` — Tofino, ralloc, and
build-time IR generation) and **`build-bmv2/`** (Release, `ENABLE_TOFINO=OFF` —
open-source backends on the static IR). A Tofino change must be checked in
`build/`; an IR `.def` change must be checked in both.

- **Single / filtered tests:** `ctest --test-dir build -jN --output-on-failure -R <regex>`
- **Refresh expected outputs:** `P4TEST_REPLACE=1 cmake --build build --target check`
  (expected outputs live under `testdata/*_outputs/`).
- **Pass compiler flags through tests:** `P4C_ARGS="-Xp4c=MY_FLAG" cmake --build build --target check`
- **Format / lint:** `cmake --build build --target clang-format cpplint black isort`
  (append `-fix-errors` to auto-fix). Install hooks: `./tools/install_git_hooks.sh`.

## Conventions

- IR casts: `node->to<Node>()`, or `node->checkedTo<Node>()` when null is
  unacceptable. Avoid `dynamic_cast`.
- C++ deps: Abseil is the main dependency — **do not add Boost**.
- C++: `clang-format` + `cpplint`; Python: `black` + `isort`.
- Commits: DCO sign-off required (`git commit --signoff`).
