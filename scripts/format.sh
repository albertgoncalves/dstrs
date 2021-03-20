#!/usr/bin/env bash

set -euo pipefail

cppcheck \
    --enable=all \
    --suppress=missingIncludeSystem \
    "$WD/src" \
    | sed 's/\/.*\/\(.*\) \.\.\./\1/g'
clang-format -i -verbose "$WD/src"/* 2>&1 | sed 's/\/.*\///g'
