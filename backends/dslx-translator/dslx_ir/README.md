# `dslx_ir/` — reusable DSLX-IR core

A self-contained, source-DSL-agnostic library for **building and emitting
DSLX** (Google XLS's HDL-flavored Rust-like language).

## Why a separate directory?

The wider `dslx-translator/` project is the bf-p4c integration of this core
plus a P4-IR adapter. Everything here in `dslx_ir/`:

- depends only on the C++20 standard library (no Abseil, no XLS, no p4c, no
  protobuf, no `IR::P4*`),
- can be lifted verbatim into a different repository to retarget DSLX from a
  different source language.

## How to retarget to a new source DSL

1. Drop `dslx_ir/` into your project unchanged.
2. Write `<your-lang>_to_dslx.cc` that walks your source AST and constructs
   `dslx_ir::Module` using the helpers in `build.h`.
3. Call `module.ToString()` to get DSLX source text and write it to disk.

The bf-p4c integration in `../p4_adapter/` is a worked example of step 2.

## File layout

| File          | Purpose                                                         |
| ------------- | --------------------------------------------------------------- |
| `pos.h`       | Optional `Pos`/`Span` for source-back-references (default empty)|
| `ast.h`       | All DSLX node types — see XLS_DSLX_EXPR_NODE_EACH for taxonomy  |
| `ast.cc`      | `Format(Formatter&)` impls (single-pass appender)               |
| `module.h/.cc`| Top-level container; owns nodes; renders to a string            |
| `formatter.h` | Indentation- and whitespace-tracking text appender              |
| `build.h`     | `T_*` / `E_*` / `S_*` ergonomic factory helpers                 |

## Relationship to upstream XLS

We deliberately did **not** copy `xls/dslx/frontend/ast.h` (~4400 LOC) wholesale
because it carries Abseil + protobuf + the full XLS IR as transitive deps,
which would defeat the portability goal. Instead we kept its **node taxonomy
and DSLX syntax conventions** as a reference and re-implemented a slim subset
in plain C++20.

If you need a DSLX node we don't yet model (e.g. `Match`, `ChannelDecl`),
add it here following the same shape as the existing nodes — define the class
in `ast.h`, implement `Format` in `ast.cc`, add a builder helper in `build.h`.
