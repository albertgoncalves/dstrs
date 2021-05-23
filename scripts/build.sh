#!/usr/bin/env bash

set -eu

flags=(
    "-ferror-limit=1"
    "-fshort-enums"
    "-lm"
    "-march=native"
    "-O3"
    "-pthread"
    "-Werror"
    "-Weverything"
    "-Wno-bad-function-cast"
    "-Wno-disabled-macro-expansion"
    "-Wno-extra-semi-stmt"
    "-Wno-reserved-id-macro"
    "-Wno-unused-function"
)

now () {
    date +%s.%N
}

(
    start=$(now)
    clang "${flags[@]}" -o "$WD/bin/$1" "$WD/src/$1.c"
    end=$(now)
    python3 -c "print(\"Compiled! ({:.3f}s)\".format(${end} - ${start}))"
)
