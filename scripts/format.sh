#!/usr/bin/env bash

set -euo pipefail

for x in "$WD"/src/*.h; do
    cppcheck "$x" | sed 's/\/.*\/\(.*\) \.\.\./\1/g'
done
cppcheck \
    --enable=all \
    --suppress=missingIncludeSystem \
    "$WD/src" \
    | sed 's/\/.*\/\(.*\) \.\.\./\1/g'
clang-format -i -verbose "$WD/src"/*.c 2>&1 | sed 's/\/.*\///g'
clang-format -i -verbose "$WD/src"/*.h 2>&1 | sed 's/\/.*\///g'
