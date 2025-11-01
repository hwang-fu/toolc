#!/usr/bin/env bash
set -euo pipefail

# make globs like *.a expand to empty array instead of literal pattern
shopt -s nullglob

# Destination directories (relative to where you run this)
DEST_INCLUDE="./include"
DEST_LIB="./lib"
mkdir -p "$DEST_INCLUDE" "$DEST_LIB"

# Colors
bold=$'\e[1m'; reset=$'\e[0m'
cyan=$'\e[36m'; green=$'\e[32m'
yellow=$'\e[33m'; magenta=$'\e[35m'
red=$'\e[31m'

# Loop over first-level subdirectories of ./src (bash-friendly)
for dir in ./src/*/; do
  # -------------------- Headers --------------------
  # .h files directly inside this subdir (no recursion)
  while IFS= read -r -d '' hdr; do
    base=${hdr##*/}                 # filename only (bash)
    target="$DEST_INCLUDE/$base"
    cp -a -- "$hdr" "$target"
    printf '%b\n' "${bold}${yellow}Copied:${reset} ${cyan}${hdr}${reset} ${bold}→${reset} ${green}${target}${reset}"
  done < <(find "$dir" -maxdepth 1 -type f -name '*.h' -print0)
done

printf '\n\n'

for dir in ./src/*/; do
  # -------------------- Build + Libs --------------------
  if [[ -f "$dir/Makefile" || -f "$dir/makefile" ]]; then
    printf '%b\n' "${bold}${magenta}Building in:${reset} ${cyan}${dir}${reset}"

    # Build inside the subdir
    ( cd -- "$dir" && make )

    # Look for any lib*.a inside <subdir>/lib
    if [[ -d "$dir/lib" ]]; then
      libs=("$dir"/lib/lib*.a)      # nullglob makes this empty if none
      if (( ${#libs[@]} )); then
        for lib in "${libs[@]}"; do
          base=${lib##*/}           # filename only
          cp -a -- "$lib" "$DEST_LIB/$base"
          printf '%b\n' "${bold}${yellow}Archived:${reset} ${cyan}${lib}${reset} ${bold}→${reset} ${green}${DEST_LIB}/${base}${reset}"
        done
      else
        printf '%b\n' "${red}No static libraries found in ${cyan}$dir/lib${reset}"
      fi
    else
      printf '%b\n' "${red}No lib directory found in ${cyan}$dir${reset}"
    fi

    # Clean after copying
    ( cd -- "$dir" && make clean )
  else
    printf '%b\n' "${bold}No Makefile:${reset} ${cyan}${dir}${reset} — skipping build."
  fi
done

