#!/usr/bin/env bash

set -eu

"$WD/scripts/build.sh" "$1"
"$WD/bin/$1" "$WD/out/$1.txt"
"$WD/scripts/hist.py" "$WD/out/$1.txt" "$WD/out/$1.png"
feh "$WD/out/$1.png"
