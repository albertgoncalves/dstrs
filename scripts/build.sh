#!/usr/bin/env bash

set -eu

flags=(
    "-fanalyzer"
    "-fshort-enums"
    "-g"
    "-march=native"
    "-O3"
    "-static"
    "-Wall"
    "-Wcast-align"
    "-Wcast-align=strict"
    "-Wcast-qual"
    "-Wconversion"
    "-Wdate-time"
    "-Wdouble-promotion"
    "-Wduplicated-branches"
    "-Wduplicated-cond"
    "-Werror"
    "-Wextra"
    "-Wfatal-errors"
    "-Wfloat-equal"
    "-Wformat-signedness"
    "-Wformat=2"
    "-Winline"
    "-Wlogical-op"
    "-Wmissing-declarations"
    "-Wmissing-include-dirs"
    "-Wno-analyzer-possible-null-argument"
    "-Wno-unused-function"
    "-Wnull-dereference"
    "-Wpacked"
    "-Wpedantic"
    "-Wpointer-arith"
    "-Wredundant-decls"
    "-Wshadow"
    "-Wstack-protector"
    "-Wswitch-enum"
    "-Wtrampolines"
    "-Wundef"
    "-Wunused"
    "-Wunused-macros"
    "-Wwrite-strings"
)

now () {
    date +%s.%N
}

(
    start=$(now)
    gcc "${flags[@]}" -o "$WD/bin/$1" "$WD/src/$1.c"
    end=$(now)
    python3 -c "print(\"Compiled! ({:.3f}s)\".format(${end} - ${start}))"
)
