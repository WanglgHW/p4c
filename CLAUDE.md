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
  TNA/T2NA. Used both standalone and wired into the Tofino backend.

- **Tofino backend (`backends/tofino/bf-p4c/`).** Barefoot/Tofino target
  (`IR::BFN::*` / `IR::MAU::*` nodes). See its `AGENTS.md`.

- **MILP/SCIP MAU resource allocator (`model/`, `--use-ralloc`).** Experimental
  table-placement allocator. In the Tofino backend, `--use-ralloc` (see
  `backends/tofino/bf-p4c/bf-p4c-options.cpp`, `backend.cpp:~450`) swaps the
  classic table placement for the MILP allocator. `model/run_ralloc.py` drives it.

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
