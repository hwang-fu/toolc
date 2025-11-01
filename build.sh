#!/usr/bin/env bash

# The script stops safely as soon as something goes wrong.
set -euo pipefail

# Destination directory (relative to the folder you run this from)
DEST_INCLUDE="./include"
DEST_LIB="./lib"

# Define colors (using ANSI escape codes)
bold=$'\e[1m'
reset=$'\e[0m'
cyan=$'\e[36m'
green=$'\e[32m'
yellow=$'\e[33m'
magenta=$'\e[35m'

# Loop over first-level subdirectories only
for dir in ./src/*(/); do
    # -------------------- Headers --------------------
    # Find .h files directly inside this subdir (no recursion)
    find "$dir" -maxdepth 1 -type f -name '*.h' -print0 | while IFS= read -r -d '' hdr; do
        base="${hdr:t}"     # filename only
        target="$DEST_INCLUDE/$base"
        cp -a -- "$hdr" "$target"
        print "${bold}${yellow}Copied:${reset} ${cyan}${hdr}${reset} ${bold}→${reset} ${green}${target}${reset}"
    done
done

echo
echo

for dir in ./src/*(/); do
  # -------------------- Build + Libs --------------------
  if [[ -f "$dir/Makefile" || -f "$dir/makefile" ]]; then
    print "${bold}${magenta}Building in:${reset} ${cyan}${dir}${reset}"

    # Build inside the subdir
    ( cd -- "$dir" && make )

    # Look for any lib*.a inside <subdir>/lib
    if [[ -d "$dir/lib" ]]; then
      libs=("$dir"/lib/lib*.a(N))
      if (( ${#libs} )); then
        for lib in "${libs[@]}"; do
          base="${lib:t}"
          cp -a -- "$lib" "$DEST_LIB/$base"
          print "${bold}${yellow}Archived:${reset} ${cyan}${lib}${reset} ${bold}→${reset} ${green}${DEST_LIB}/${base}${reset}"
        done
      else
        print "${red}No static libraries found in ${cyan}$dir/lib${reset}"
      fi
    else
      print "${red}No lib directory found in ${cyan}$dir${reset}"
    fi

    # Clean after copying
    ( cd -- "$dir" && make clean )
  else
    print "${bold}No Makefile:${reset} ${cyan}${dir}${reset} — skipping build."
  fi
done
