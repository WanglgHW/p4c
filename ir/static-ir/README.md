# Static (pre-generated) IR

This directory holds the **pre-generated** IR node sources — the `IR::*` classes
that the `ir-generator` would otherwise emit at build time from the `.def` files,
hand-split into per-category files (`ir-generated-base`, `-types`, `-expressions`,
`-statements`, `-declarations`, `-v1`) re-exported by the umbrella
`ir-generated.{h,cpp}`, plus `gen-tree-macro.h`.

These contain **core/frontend node classes only** (no backend IR extensions).

## When it is used

The top-level `CMakeLists.txt` selects the IR strategy by `ENABLE_TOFINO`:

* `ENABLE_TOFINO=OFF` (bmv2 and the other open-source backends): these files are
  staged into `${build}/ir/` at configure time and compiled directly — no
  `irgenerator` is built.
* `ENABLE_TOFINO=ON`: this directory is **ignored**; `tools/ir-generator` instead
  generates the IR from all `.def` files (including the Tofino `.def` extensions
  that define `IR::BFN::*` / `IR::MAU::*`) into `${build}/ir/` via the `genIR`
  target.

## Keeping it in sync

If you change a core IR `.def` file, regenerate these files so the static
(non-Tofino) build matches: build once with `-DENABLE_TOFINO=ON`, then copy the
generated `build/ir/ir-generated*` / `build/ir/gen-tree-macro.h` back here
(re-splitting as needed). They are not produced automatically in a static build.
