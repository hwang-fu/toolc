#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

TEST_SRC="$SCRIPT_DIR/../test/test.c"
OUT_BIN="$SCRIPT_DIR/../test/a.out"

trap 'rm -f "$OUT_BIN"' EXIT

clang "$TEST_SRC"                                       \
    ${INCDIR:+-I"$INCDIR"}                              \
    ${LIBDIR:+-L"$LIBDIR"}                              \
    -std=c23                                            \
    -Wall                                               \
    -Wextra                                             \
    -O2                                                 \
    -Wl,--start-group                                   \
    -lcrayon                                            \
    -lassertion                                         \
    -lmemory                                            \
    -lresult                                            \
    -ldequeue                                           \
    -lcstr                                              \
    -Wl,--end-group                                     \
    -Wl,-rpath,'$ORIGIN'                                \
    -o "$OUT_BIN"

# Capture stdout and exit code
"$OUT_BIN"
exit $?
