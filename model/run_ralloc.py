#!/usr/bin/env python3
# Copyright (C) 2026
# SPDX-License-Identifier: Apache-2.0
"""
run_ralloc.py — one driver for every ralloc (MILP/OR-Tools) operation.

This wraps the workflows documented in model/doc/MANUAL.md so they can be run
with a single command instead of long copy-pasted invocations:

  build     configure + build the compiler (p4c-barefoot, ralloc_bridge) and the
            standalone model core + ralloc-solve binary
  test      run the standalone model unit tests (ctest)
  run       in-process compile with --use-ralloc (needs -DRALLOC_INPROCESS_SOLVER=ON)
  emit      decoupled phase 1: write model_input.json + ir_middle.json, then stop
  solve     decoupled phase 2: run ralloc-solve  (model_input.json -> model_out.json)
  resume    decoupled phase 3: consume model_out.json + ir_middle.json, finish
  flow      run emit -> solve -> resume in sequence (the whole decoupled flow)
  verify    compile a program twice (legacy vs model/OR-Tools) and compare the outputs

Paths are auto-detected relative to this script (model/ lives inside the p4c
tree); override any of them with the global options below.

Examples
--------
  ./model/run_ralloc.py build
  ./model/run_ralloc.py flow   testdata/dpvs-l4LB/dpvs_l4lb.p4
  ./model/run_ralloc.py verify testdata/dpvs-l4LB/dpvs_l4lb.p4
  ./model/run_ralloc.py run    my_prog.p4 -o /tmp/out
"""

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

# --------------------------------------------------------------------------- #
# Path discovery (all overridable on the command line)
# --------------------------------------------------------------------------- #
MODEL_DIR = Path(__file__).resolve().parent          # .../model
REPO_ROOT = MODEL_DIR.parent                          # the p4c tree root


def default_paths(args):
    """Fill in any path the user did not override, derived from REPO_ROOT."""
    args.build_dir = Path(args.build_dir) if args.build_dir else REPO_ROOT / "build"
    args.model_build = Path(args.model_build) if args.model_build else MODEL_DIR / "build"
    args.p4c = (
        Path(args.p4c)
        if args.p4c
        else args.build_dir / "backends" / "tofino" / "bf-p4c" / "p4c-barefoot"
    )
    args.solve = Path(args.solve) if args.solve else args.model_build / "ralloc-solve"
    args.p4include = Path(args.p4include) if args.p4include else args.build_dir / "p4include"
    return args


# --------------------------------------------------------------------------- #
# Small process helpers
# --------------------------------------------------------------------------- #
class Colors:
    BOLD = "\033[1m"
    GREEN = "\033[32m"
    RED = "\033[31m"
    YELLOW = "\033[33m"
    DIM = "\033[2m"
    OFF = "\033[0m"


def _c(s, color):
    return f"{color}{s}{Colors.OFF}" if sys.stdout.isatty() else str(s)


def info(msg):
    print(_c("==> ", Colors.BOLD) + _c(msg, Colors.BOLD))


def warn(msg):
    print(_c("warning: ", Colors.YELLOW) + msg)


def die(msg, code=1):
    print(_c("error: ", Colors.RED) + msg, file=sys.stderr)
    sys.exit(code)


def run(cmd, *, cwd=None, env=None, check=True, capture=False, quiet=False):
    """Run a command, echoing it. Returns CompletedProcess."""
    printable = " ".join(str(c) for c in cmd)
    if not quiet:
        print(_c("$ ", Colors.DIM) + _c(printable, Colors.DIM))
    proc = subprocess.run(
        [str(c) for c in cmd],
        cwd=str(cwd) if cwd else None,
        env=env,
        text=True,
        capture_output=capture,
    )
    if check and proc.returncode != 0:
        if capture:
            sys.stdout.write(proc.stdout or "")
            sys.stderr.write(proc.stderr or "")
        die(f"command failed (exit {proc.returncode}): {printable}", proc.returncode)
    return proc


def need_binary(path, hint):
    if not Path(path).exists():
        die(f"{path} not found.\n  {hint}")


def brew_prefix():
    exe = shutil.which("brew")
    if not exe:
        return None
    try:
        return subprocess.check_output([exe, "--prefix"], text=True).strip()
    except subprocess.CalledProcessError:
        return None


# --------------------------------------------------------------------------- #
# Compiler invocation helpers
# --------------------------------------------------------------------------- #
def base_compile_cmd(args, src, out_dir, extra):
    """The common p4c-barefoot invocation for a Tofino/TNA compile."""
    cmd = [
        args.p4c,
        "--target", "tofino",
        "--arch", "tna",
        "-I", args.p4include,
    ]
    cmd += extra
    cmd += [str(src), "-o", str(out_dir)]
    return cmd


def ensure_compiler(args):
    need_binary(
        args.p4c,
        f"build it first:  {Path(__file__).name} build   (or `make p4c-barefoot` in {args.build_dir})",
    )
    if not args.p4include.exists():
        warn(f"p4include not found at {args.p4include}; pass --p4include if includes fail")


def ensure_solver(args):
    need_binary(
        args.solve,
        f"build it first:  {Path(__file__).name} build   "
        f"(or `cmake --build {args.model_build} --target ralloc-solve`)",
    )


# --------------------------------------------------------------------------- #
# Sub-commands
# --------------------------------------------------------------------------- #
def cmd_build(args):
    """Configure + build the compiler and the standalone model/ralloc-solve."""
    prefix = args.ortools_prefix or brew_prefix()
    info("Building the standalone model core + ralloc-solve")
    cfg = ["cmake", "-S", MODEL_DIR, "-B", args.model_build]
    if prefix:
        cfg += [f"-DCMAKE_PREFIX_PATH={prefix}"]
    run(cfg)
    run(["cmake", "--build", args.model_build, "-j", str(args.jobs)])

    if args.model_only:
        info("Done (model-only build).")
        return

    if not args.build_dir.exists():
        die(
            f"in-tree build dir {args.build_dir} does not exist.\n"
            f"  Configure the full p4c/Tofino build there first, or pass --build-dir,\n"
            f"  or use --model-only to build just the model core + ralloc-solve."
        )
    info(f"Reconfiguring in-tree build at {args.build_dir} (to find ralloc)")
    cfg = ["cmake", "."]
    if prefix:
        cfg += [f"-DCMAKE_PREFIX_PATH={prefix}"]
    run(cfg, cwd=args.build_dir)
    info("Building ralloc_bridge + p4c-barefoot")
    run(["make", "ralloc_bridge", "p4c-barefoot", f"-j{args.jobs}"], cwd=args.build_dir)
    info("Build complete.")
    print(f"  compiler   : {args.p4c}")
    print(f"  ralloc-solve: {args.solve}")


def cmd_test(args):
    """Run the standalone model unit tests."""
    need_binary(
        args.model_build / "CMakeCache.txt",
        f"configure/build first:  {Path(__file__).name} build --model-only",
    )
    # The test executables are EXCLUDE_FROM_ALL, so build them before ctest.
    info("Building model unit tests")
    run(["cmake", "--build", args.model_build, "--target", "ralloc_tests", "-j", str(args.jobs)])
    info("Running model unit tests (ctest)")
    run(["ctest", "--test-dir", args.model_build, "--output-on-failure"])


def cmd_run(args):
    """In-process compile with --use-ralloc (needs OR-Tools linked into p4c-barefoot)."""
    ensure_compiler(args)
    out = Path(args.out) if args.out else REPO_ROOT / "ralloc_run_out"
    out.mkdir(parents=True, exist_ok=True)
    extra = ["--use-ralloc", f"-Tralloc_model_pass:{args.trace}"]
    info(f"In-process --use-ralloc compile of {args.src}")
    run(base_compile_cmd(args, args.src, out, extra))
    info(f"Done. Outputs in {out}")


def cmd_emit(args):
    """Decoupled phase 1: write model_input.json + ir_middle.json, then stop."""
    ensure_compiler(args)
    io = Path(args.io)
    io.mkdir(parents=True, exist_ok=True)
    extra = ["--ralloc-emit", str(io), f"-Tralloc_model_pass:{args.trace}"]
    info(f"[phase 1/3 emit] {args.src} -> {io}")
    run(base_compile_cmd(args, args.src, io / "emit", extra))
    for f in ("model_input.json", "ir_middle.json"):
        p = io / f
        status = f"{p.stat().st_size} bytes" if p.exists() else _c("MISSING", Colors.RED)
        print(f"  {f}: {status}")
    if not (io / "model_input.json").exists():
        die("emit did not produce model_input.json")


def cmd_solve(args):
    """Decoupled phase 2: ralloc-solve model_input.json -> model_out.json."""
    ensure_solver(args)
    io = Path(args.io)
    inp = io / "model_input.json"
    need_binary(inp, f"run the emit phase first:  {Path(__file__).name} emit <prog.p4> --io {io}")
    out = io / "model_out.json"
    cmd = [args.solve, inp, "-o", out, "--time-limit", str(args.time_limit)]
    if args.gap is not None:
        cmd += ["--gap", str(args.gap)]
    if args.objective:
        cmd += ["--objective", args.objective]
    if args.seed is not None:
        cmd += ["--seed", str(args.seed)]
    if args.dump_dir:
        cmd += ["--dump-dir", args.dump_dir]
    info(f"[phase 2/3 solve] {inp.name} -> {out.name}")
    # ralloc-solve prints the solver log to stderr and a one-line summary at the end.
    proc = run(cmd, check=False, capture=not args.verbose_solver)
    if proc.returncode != 0:
        if not args.verbose_solver:
            sys.stderr.write(proc.stderr or "")
        die(f"ralloc-solve failed (exit {proc.returncode})", proc.returncode)
    if not args.verbose_solver and proc.stderr:
        # echo only the final summary line(s) from ralloc-solve
        for line in proc.stderr.splitlines():
            if line.startswith("ralloc-solve:"):
                print("  " + line)
    if not out.exists():
        die("solve did not produce model_out.json")


def cmd_resume(args):
    """Decoupled phase 3: consume model_out.json + ir_middle.json, finish."""
    ensure_compiler(args)
    io = Path(args.io)
    need_binary(io / "model_out.json", f"run the solve phase first:  {Path(__file__).name} solve --io {io}")
    out = Path(args.out) if args.out else io / "resume_out"
    out.mkdir(parents=True, exist_ok=True)
    extra = ["--ralloc-resume", str(io), f"-Tralloc_model_pass:{args.trace}"]
    info(f"[phase 3/3 resume] {args.src} + {io} -> {out}")
    run(base_compile_cmd(args, args.src, out, extra))
    bfa = list(out.glob("**/*.bfa"))
    info(f"Done. {len(bfa)} .bfa produced under {out}")


def cmd_flow(args):
    """Run the entire decoupled flow: emit -> solve -> resume."""
    io = Path(args.io)
    io.mkdir(parents=True, exist_ok=True)
    info(f"Decoupled flow on {args.src}  (io dir: {io})")
    cmd_emit(args)
    cmd_solve(args)
    cmd_resume(args)
    info("Decoupled flow complete.")


# ----- verify --------------------------------------------------------------- #
# Fields that legitimately differ between any two compiles (not real content).
_IGNORE_TOKENS = ("run_id", "build_date")


def _strip_ignored(path):
    """Return file text with lines containing volatile tokens removed.
    Binary files are returned as bytes (compared verbatim)."""
    try:
        text = Path(path).read_text()
    except UnicodeDecodeError:
        return Path(path).read_bytes()
    return "\n".join(
        ln for ln in text.splitlines() if not any(tok in ln for tok in _IGNORE_TOKENS)
    )


def _compare_trees(orig, model):
    """Compare two output trees. Returns (only_volatile, real_diffs, missing)."""
    orig, model = Path(orig), Path(model)
    only_volatile = []   # differ, but only in run_id/build_date
    real_diffs = []      # differ in actual content
    missing = []         # present in orig, absent in model (or vice versa)

    orig_files = {p.relative_to(orig) for p in orig.rglob("*") if p.is_file()}
    model_files = {p.relative_to(model) for p in model.rglob("*") if p.is_file()}

    for rel in sorted(orig_files ^ model_files):
        missing.append(rel)

    for rel in sorted(orig_files & model_files):
        a, b = orig / rel, model / rel
        if a.read_bytes() == b.read_bytes():
            continue
        if _strip_ignored(a) == _strip_ignored(b):
            only_volatile.append(rel)
        else:
            real_diffs.append(rel)
    return only_volatile, real_diffs, missing


def cmd_verify(args):
    """Compile twice (legacy vs model/OR-Tools) and compare every output artifact."""
    ensure_compiler(args)
    ensure_solver(args)
    work = Path(args.work)
    orig_dir = work / "orig"
    model_dir = work / "model"
    io = work / "io"
    for d in (orig_dir, model_dir, io):
        if d.exists():
            shutil.rmtree(d)
        d.mkdir(parents=True)

    info("RUN 1 — ORIGINAL algorithm (legacy allocator, no ralloc)")
    run(base_compile_cmd(args, args.src, orig_dir, []))

    info("RUN 2 — MODEL/OR-TOOLS method (decoupled emit -> solve -> resume)")
    flow_args = argparse.Namespace(**vars(args))
    flow_args.io = str(io)
    flow_args.out = str(model_dir)
    cmd_emit(flow_args)
    cmd_solve(flow_args)
    cmd_resume(flow_args)

    info("Comparing every output artifact (ignoring run_id / build_date)")
    only_volatile, real_diffs, missing = _compare_trees(orig_dir, model_dir)

    n_orig = sum(1 for _ in orig_dir.rglob("*") if _.is_file())
    print(f"  output files compared : {n_orig}")
    print(f"  identical content     : {n_orig - len(only_volatile) - len(real_diffs)}")
    print(f"  differ (run_id/date)  : {len(only_volatile)}")
    for rel in only_volatile:
        print(f"      ~ {rel}")
    if real_diffs:
        print(_c(f"  differ (REAL content) : {len(real_diffs)}", Colors.RED))
        for rel in real_diffs:
            print(_c(f"      ! {rel}", Colors.RED))
    if missing:
        print(_c(f"  present in only one run: {len(missing)}", Colors.RED))
        for rel in missing:
            print(_c(f"      ? {rel}", Colors.RED))

    # Report the solver's own solution (out-of-process optimum) for context.
    mout = io / "model_out.json"
    if mout.exists():
        import json

        try:
            data = json.loads(mout.read_text())
            stages = data.get("mau", {}).get("stages_used")
            ntables = len(data.get("mau", {}).get("tables", []))
            info(f"Model/OR-Tools solution: {stages} stage(s), {ntables} table(s) "
                 f"(advisory — legacy still emits the binary; see MANUAL §11)")
        except (ValueError, KeyError):
            pass

    if real_diffs or missing:
        die("VERIFY FAILED — the model/OR-Tools path changed real output (see above).")
    info(_c("VERIFY OK — model/OR-Tools output is byte-identical to legacy "
            "(modulo run_id/build_date).", Colors.GREEN))


# --------------------------------------------------------------------------- #
# Argument parsing
# --------------------------------------------------------------------------- #
def build_parser():
    p = argparse.ArgumentParser(
        prog="run_ralloc.py",
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    # Global path overrides.
    g = p.add_argument_group("paths (auto-detected from this script's location)")
    g.add_argument("--build-dir", help="in-tree p4c build dir (default: <repo>/build)")
    g.add_argument("--model-build", help="standalone model build dir (default: model/build)")
    g.add_argument("--p4c", help="path to p4c-barefoot binary")
    g.add_argument("--solve", help="path to ralloc-solve binary")
    g.add_argument("--p4include", help="P4 include dir (default: <build>/p4include)")
    p.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4, help="parallel build jobs")

    sub = p.add_subparsers(dest="command", required=True)

    def add_trace(sp):
        sp.add_argument("-T", "--trace", type=int, default=1,
                        help="ralloc_model_pass trace level (1 or 2)")

    # build
    sp = sub.add_parser("build", help="configure + build compiler and ralloc-solve")
    sp.add_argument("--ortools-prefix",
                    help="CMAKE_PREFIX_PATH for OR-Tools (default: `brew --prefix`)")
    sp.add_argument("--model-only", action="store_true",
                    help="build only the standalone model core + ralloc-solve")
    sp.set_defaults(func=cmd_build)

    # test
    sp = sub.add_parser("test", help="run standalone model unit tests (ctest)")
    sp.set_defaults(func=cmd_test)

    # run (in-process)
    sp = sub.add_parser("run", help="in-process compile with --use-ralloc")
    sp.add_argument("src", help="P4 source file")
    sp.add_argument("-o", "--out", help="output dir (default: <repo>/ralloc_run_out)")
    add_trace(sp)
    sp.set_defaults(func=cmd_run)

    # emit / solve / resume / flow share an io dir
    def add_io(sp):
        sp.add_argument("--io", default=str(REPO_ROOT / "ralloc_io"),
                        help="handoff dir for the 3 JSON files (default: <repo>/ralloc_io)")

    sp = sub.add_parser("emit", help="phase 1: write model_input.json + ir_middle.json, then stop")
    sp.add_argument("src", help="P4 source file")
    add_io(sp)
    add_trace(sp)
    sp.set_defaults(func=cmd_emit)

    sp = sub.add_parser("solve", help="phase 2: ralloc-solve model_input.json -> model_out.json")
    add_io(sp)
    sp.add_argument("--time-limit", type=float, default=120.0, help="solver time budget (s)")
    sp.add_argument("--gap", type=float, help="accepted MIP optimality gap")
    sp.add_argument("--objective", choices=["stage", "power", "phv", "feasible", "lex"],
                    help="solver objective (default: stage)")
    sp.add_argument("--seed", type=int, help="solver seed")
    sp.add_argument("--dump-dir", help="dump .lp/.cip models + solver logs")
    sp.add_argument("--verbose-solver", action="store_true", help="show the full solver log")
    sp.set_defaults(func=cmd_solve)

    sp = sub.add_parser("resume", help="phase 3: consume model_out.json + ir_middle.json, finish")
    sp.add_argument("src", help="P4 source file (same as emit)")
    add_io(sp)
    sp.add_argument("-o", "--out", help="output dir (default: <io>/resume_out)")
    add_trace(sp)
    sp.set_defaults(func=cmd_resume)

    sp = sub.add_parser("flow", help="run emit -> solve -> resume in sequence")
    sp.add_argument("src", help="P4 source file")
    add_io(sp)
    sp.add_argument("-o", "--out", help="final output dir (default: <io>/resume_out)")
    sp.add_argument("--time-limit", type=float, default=120.0, help="solver time budget (s)")
    sp.add_argument("--gap", type=float, help="accepted MIP optimality gap")
    sp.add_argument("--objective", choices=["stage", "power", "phv", "feasible", "lex"],
                    help="solver objective (default: stage)")
    sp.add_argument("--seed", type=int, help="solver seed")
    sp.add_argument("--dump-dir", help="dump .lp/.cip models + solver logs")
    sp.add_argument("--verbose-solver", action="store_true", help="show the full solver log")
    add_trace(sp)
    sp.set_defaults(func=cmd_flow)

    # verify
    sp = sub.add_parser("verify", help="compile twice (legacy vs model) and compare outputs")
    sp.add_argument("src", help="P4 source file")
    sp.add_argument("--work", default=str(REPO_ROOT / "ralloc_verify"),
                    help="working dir for the two compiles (default: <repo>/ralloc_verify)")
    sp.add_argument("--time-limit", type=float, default=120.0, help="solver time budget (s)")
    sp.add_argument("--gap", type=float, help="accepted MIP optimality gap")
    sp.add_argument("--objective", choices=["stage", "power", "phv", "feasible", "lex"],
                    help="solver objective (default: stage)")
    sp.add_argument("--seed", type=int, help="solver seed")
    sp.add_argument("--dump-dir", help="dump .lp/.cip models + solver logs")
    sp.add_argument("--verbose-solver", action="store_true", help="show the full solver log")
    add_trace(sp)
    sp.set_defaults(func=cmd_verify)

    return p


def main(argv=None):
    args = build_parser().parse_args(argv)
    default_paths(args)
    args.func(args)


if __name__ == "__main__":
    main()
