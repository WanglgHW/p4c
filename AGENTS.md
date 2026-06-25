# Repository Guidelines

## Project Structure & Module Organization
Two-level map of the repository (major folders only):
```text
.
|-- .github/               # CI config (workflows/).
|-- backends/              # Backends.
|   |-- {bmv2,dpdk,ebpf,graphs,p4fmt,p4test,p4tools,tc,tofino,ubpf}/ # Targets.
|-- bazel/                 # Bazel build.
|-- build/                 # Local build output (generated).
|-- cmake/                 # CMake helpers.
|-- control-plane/         # Control-plane APIs.
|-- debian/                # Debian packaging.
|-- docs/                  # Docs.
|-- extensions/            # Extensions.
|-- frontends/             # Frontend stages.
|   |-- {common,p4,p4-14,parsers}/ # Frontend layers.
|-- ir/                    # IR definitions (.def files + hand-written nodes).
|   |-- static-ir/         # Pre-generated static IR (used when ENABLE_TOFINO=OFF).
|-- json_outputs/          # JSON output helpers.
|-- lib/                   # Shared libraries.
|-- midend/                # Midend passes.
|-- model/                 # MILP/SCIP MAU resource allocator (ralloc, --use-ralloc).
|-- p4include/             # P4 headers.
|-- test/                  # Unit tests.
|-- testdata/              # Test inputs/outputs.
|   |-- {p4_14_*,p4_16_*,p4tc_*}/ # Test suites.
|-- tests/                 # Integration tests.
|-- tools/                 # Dev scripts.
```

## Build, Test, and Development Commands
- `mkdir -p build `
- `cmake -B build -DCMAKE_BUILD_TYPE=Release`: configure.
- `cmake --build build`: compile.
- `cmake --build build --target check`: run tests.


Optional tools:
- `cmake --build build --target clang-format cpplint black isort`: format/lint checks (`*-fix-errors` to fix).

## IR Generation Strategy (two modes, picked by `ENABLE_TOFINO`)
The `ir-generated` translation unit (the `IR::*` node classes) is produced one of
two ways, selected automatically in the top-level `CMakeLists.txt`:

- **`ENABLE_TOFINO=ON` → build-time generation.** The `tools/ir-generator`
  `irgenerator` tool parses every collected `.def` file (core IR **plus** the
  Tofino `.def` extensions under `backends/tofino/bf-p4c/ir/`) and emits
  `ir-generated.{h,cpp}` + `gen-tree-macro.h` into `${P4C_BINARY_DIR}/ir/` via the
  `genIR` target. This is **required** for Tofino — its `IR::BFN::*` / `IR::MAU::*`
  node classes exist only in those `.def` files and cannot be pre-generated.
- **`ENABLE_TOFINO=OFF` (bmv2 and the other open-source backends) → static IR.**
  The pre-generated, hand-split files in **`ir/static-ir/`** (core/frontend nodes
  only) are staged into `${P4C_BINARY_DIR}/ir/` at configure time and compiled
  directly. No `irgenerator` is built — these backends do not need the flex/bison
  IR-generator step, and their IR is identical to what they always built against.

Either way the sources land under `${P4C_BINARY_DIR}/ir/`, so `#include
"ir/ir-generated.h"` resolves identically regardless of mode. If you change an IR
`.def` file, the static copies in `ir/static-ir/` must be regenerated to match
(build once with `ENABLE_TOFINO=ON` and copy `build/ir/ir-generated*` across, or
keep `.def` edits Tofino-only).

## Coding Style & Naming Conventions
- Follow the P4 coding standard philosophy and `.clang-tidy`.
- C++ uses `clang-format` and `cpplint`; Python uses `black` and `isort`.
- Prefer IR node casts via `node->to<Node>()`; use `node->checkedTo<Node>()` when `nullptr` is not acceptable. Avoid `dynamic_cast`.
- Main C++ dependency is Abseil; do not introduce new Boost dependencies.

## P4 Language Notes
- Follow the P4 language spec.
- `p4include/` has `core.p4` plus target models: `v1model.p4` (BMv2), `ebpf_model.p4`, `ubpf_model.p4`, `xdp_model.p4`, `pna.p4`, and `p4include/{bmv2,dpdk,tc}/{pna,psa}.p4`. Tofino uses `backends/tofino/bf-p4c/p4include/tna.p4`.

## Backend Guides
- See `backends/{bmv2,dpdk,ebpf,graphs,p4fmt,p4test,p4tools,tc,tofino,ubpf}/AGENTS.md` for backend-specific guidance.

## Testing Guidelines
- Run the full suite with `cmake --build build --target check` (additional `check-*` targets are defined in CMake files when present).
- Idiomatic filtered runs: `ctest --test-dir build -j<N> --output-on-failure -R <filter>` (use the relevant suite or backend filter).
- Expected outputs live under `testdata/*_outputs/`; refresh them with `P4TEST_REPLACE=1 cmake --build build --target check`.
- Pass compiler flags via `P4C_ARGS`, e.g. `P4C_ARGS="-Xp4c=MY_CUSTOM_FLAG" cmake --build build --target check`.

## Commit & Pull Request Guidelines
- Use DCO sign-off for every commit (`git commit --signoff`).
- Use a ~50-character summary plus a body explaining why/how and linking issues.
- Single-commit PRs inherit the message; multi-commit PRs should include a synopsis and be squashed on merge.
- Code review is required; tests and format/lint must pass.
- Install hooks to enforce formatting checks: `./tools/install_git_hooks.sh`.
