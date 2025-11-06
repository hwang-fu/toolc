#!/usr/bin/env bash
set -euo pipefail

# Resolve script dir so paths work no matter where you run it from
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
TEST_SRC="$SCRIPT_DIR/../test/test.c"
OUT_BIN="$SCRIPT_DIR/../test/a.out"

# Optional: custom include/lib dirs via env (LIBDIR/INCDIR), otherwise skipped
INCDIR="$SCRIPT_DIR/.."
LIBDIR="$SCRIPT_DIR/../hwangfu"

clang "$TEST_SRC" \
    ${INCDIR:+-I"$INCDIR"} \
    ${LIBDIR:+-L"$LIBDIR"} \
    -Wall -Wextra -O2 \
    -lassertion -ldequeue -lresult -lmemory -lcrayon \
    -Wl,-rpath,'$ORIGIN' \
    -o "$OUT_BIN"

"$OUT_BIN"
rm -f "$OUT_BIN"
