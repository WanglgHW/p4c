#!/usr/bin/env python3
"""
Uses the XLS interpreter to verify all generated DSLX files.

Usage:
    python3 verify_dslx.py [--file FILE] [--all] [--verbose]
"""

import os
import sys
import subprocess
import argparse
from pathlib import Path
from typing import List, Tuple, Optional
import time

# XLS Tools Configuration (matching tools_qwen.py)
XLSYNTH_TOOLS_DIR = "/Users/georgewang/xls"
DSLX_INTERPRETER_MAIN = os.path.join(XLSYNTH_TOOLS_DIR, 'interpreter_main')
DSLX_STDLIB_PATH = os.path.join(XLSYNTH_TOOLS_DIR, 'xls', 'dslx', 'stdlib')

# Verify paths exist
def check_xls_tools() -> bool:
    """Check if XLS tools are available."""
    if not os.path.isfile(DSLX_INTERPRETER_MAIN):
        print(f"ERROR: DSLX interpreter not found at: {DSLX_INTERPRETER_MAIN}")
        return False
    if not os.path.isdir(DSLX_STDLIB_PATH):
        print(f"ERROR: DSLX stdlib not found at: {DSLX_STDLIB_PATH}")
        return False
    return True


def run_dslx_interpreter(
    x_path: str,
    extra_flags: Optional[List[str]] = None,
    compare_jit: bool = True,
    verbose: bool = False
) -> Tuple[bool, int, str, str]:
    """
    Run the DSLX interpreter on a file.

    Args:
        x_path: Path to the DSLX file
        extra_flags: Additional flags to pass to the interpreter
        compare_jit: Whether to use --compare=jit flag
        verbose: Print command before execution

    Returns:
        Tuple of (success, return_code, stdout, stderr)
    """
    cmd = [
        DSLX_INTERPRETER_MAIN,
        x_path,
        '--dslx_stdlib_path',
        DSLX_STDLIB_PATH,
    ]

    if extra_flags:
        cmd.extend(extra_flags)

    if compare_jit:
        cmd.append('--compare=jit')

    # Disable warnings as errors (P4 naming conventions differ from DSLX)
    cmd.append('--warnings_as_errors=false')

    if verbose:
        print(f"Running: {subprocess.list2cmdline(cmd)}")

    result = subprocess.run(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )

    success = result.returncode == 0
    return success, result.returncode, result.stdout, result.stderr


def extract_test_summary(stderr: str) -> str:
    """Extract test summary from stderr output."""
    lines = stderr.strip().split('\n')
    summary_lines = []

    for line in lines:
        if 'PASSED' in line or 'FAILED' in line or 'RUN' in line:
            summary_lines.append(line)

    # Get the final summary line
    for line in reversed(lines):
        if line.strip():
            summary_lines.append(line)
            break

    return '\n'.join(summary_lines[-5:]) if summary_lines else stderr[-500:]


def verify_single_file(
    file_path: Path,
    verbose: bool = False,
    show_output: bool = False
) -> Tuple[bool, str]:
    """
    Verify a single DSLX file.

    Returns:
        Tuple of (success, message)
    """
    if not file_path.exists():
        return False, f"File not found: {file_path}"

    if not file_path.suffix == '.x':
        return False, f"Not a DSLX file: {file_path}"

    start_time = time.time()
    success, retcode, stdout, stderr = run_dslx_interpreter(
        str(file_path),
        verbose=verbose
    )
    elapsed = time.time() - start_time

    if success:
        message = f"PASS ({elapsed:.2f}s)"
        if show_output and stderr:
            message += f"\n{extract_test_summary(stderr)}"
    else:
        message = f"FAIL (retcode={retcode}, {elapsed:.2f}s)"
        if stderr:
            # Show relevant error information
            error_lines = []
            for line in stderr.split('\n'):
                if 'error' in line.lower() or 'failed' in line.lower():
                    error_lines.append(line)
            if error_lines:
                message += "\n  " + "\n  ".join(error_lines[:10])
            else:
                message += f"\n  {stderr[:500]}"

    return success, message


def verify_all_files(
    directory: Path,
    verbose: bool = False,
    show_output: bool = False
) -> Tuple[int, int, List[Tuple[str, bool, str]]]:
    """
    Verify all DSLX files in a directory.

    Returns:
        Tuple of (passed_count, failed_count, results_list)
    """
    dslx_files = sorted(directory.glob("*.x"))

    if not dslx_files:
        print(f"No DSLX files found in {directory}")
        return 0, 0, []

    results = []
    passed = 0
    failed = 0

    print(f"Found {len(dslx_files)} DSLX files to verify\n")
    print("=" * 70)

    for file_path in dslx_files:
        print(f"Verifying: {file_path.name}...", end=" ", flush=True)
        success, message = verify_single_file(file_path, verbose, show_output)

        if success:
            passed += 1
            status = "✅"
        else:
            failed += 1
            status = "❌"

        print(f"{status} {message}")
        results.append((file_path.name, success, message))

    print("=" * 70)

    return passed, failed, results


def main():
    parser = argparse.ArgumentParser(
        description="Verify DSLX files using XLS interpreter"
    )
    parser.add_argument(
        '--file', '-f',
        type=str,
        help='Verify a specific DSLX file'
    )
    parser.add_argument(
        '--all', '-a',
        action='store_true',
        help='Verify all DSLX files in the current directory'
    )
    parser.add_argument(
        '--dir', '-d',
        type=str,
        default='.',
        help='Directory containing DSLX files (default: current directory)'
    )
    parser.add_argument(
        '--verbose', '-v',
        action='store_true',
        help='Show command being executed'
    )
    parser.add_argument(
        '--output', '-o',
        action='store_true',
        help='Show test output summary'
    )

    args = parser.parse_args()

    # Check XLS tools first
    if not check_xls_tools():
        print("\nPlease ensure XLS tools are installed correctly.")
        print(f"Expected interpreter at: {DSLX_INTERPRETER_MAIN}")
        print(f"Expected stdlib at: {DSLX_STDLIB_PATH}")
        sys.exit(1)

    print("XLS Tools Configuration:")
    print(f"  Interpreter: {DSLX_INTERPRETER_MAIN}")
    print(f"  Stdlib: {DSLX_STDLIB_PATH}")
    print()

    if args.file:
        # Verify single file
        file_path = Path(args.file)
        print(f"Verifying: {file_path}")
        success, message = verify_single_file(file_path, args.verbose, args.output)
        print(f"Result: {message}")
        sys.exit(0 if success else 1)

    elif args.all or True:  # Default to verifying all if no specific file
        # Verify all files in directory
        directory = Path(args.dir)
        if not directory.is_dir():
            print(f"ERROR: Not a directory: {directory}")
            sys.exit(1)

        passed, failed, results = verify_all_files(
            directory,
            args.verbose,
            args.output
        )

        print(f"\nSummary: {passed} passed, {failed} failed")

        if failed > 0:
            print("\nFailed files:")
            for name, success, message in results:
                if not success:
                    print(f"  - {name}")
            sys.exit(1)
        else:
            print("\n✅ All DSLX files verified successfully!")
            sys.exit(0)


if __name__ == "__main__":
    main()
