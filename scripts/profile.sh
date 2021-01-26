#!/usr/bin/env bash

set -eu

"$WD/scripts/build.sh" "$1"
sudo sh -c "echo 1 > /proc/sys/kernel/perf_event_paranoid"
sudo sh -c "echo 0 > /proc/sys/kernel/kptr_restrict"
perf record --call-graph fp "$WD/bin/$1" "$WD/out/$1.txt"
perf report
rm perf.data*
