#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
TEST_SRC="$SCRIPT_DIR/../test/test.c"
OUT_BIN="$SCRIPT_DIR/../test/a.out"
INCDIR="$SCRIPT_DIR/.."
LIBDIR="$SCRIPT_DIR/../hwangfu"

trap 'rm -f "$OUT_BIN"' EXIT

clang "$TEST_SRC" \
  ${INCDIR:+-I"$INCDIR"} \
  ${LIBDIR:+-L"$LIBDIR"} \
  -Wall -Wextra -O2 \
  -lassertion -ldequeue -lresult -lmemory -lcrayon \
  -Wl,-rpath,'$ORIGIN' \
  -o "$OUT_BIN"

# Capture stdout and exit code
"$OUT_BIN"
exit $?
