#!/usr/bin/env python3

from sys import argv

from matplotlib.pyplot import close, rcParams, savefig, subplots, tight_layout
from numpy import loadtxt, mean, median
from seaborn import histplot


def main():
    assert len(argv) == 3
    with open(argv[1], "r") as file:
        line = file.readline()
    if "." in line:
        x = loadtxt(argv[1], dtype="float32", delimiter="\n")
        kwargs = {"discrete": False}
    else:
        x = loadtxt(argv[1], dtype="int32", delimiter="\n")
        kwargs = {"discrete": True}
    rcParams.update({"font.family": "monospace"})
    (_, ax) = subplots(figsize=(9, 6))
    histplot(x, kde=False, color="darkgray", ec="w", ax=ax, **kwargs)
    ax.set_ylabel(None)
    kwargs = {
        "lw": 3,
        "ls": "--",
        "alpha": 0.625,
    }
    m = mean(x)
    ax.axvline(m, label=f"mean   => {m:.2f}", c="blue", **kwargs)
    m = median(x)
    ax.axvline(m, label=f"median => {m:.2f}", c="red", **kwargs)
    ax.legend()
    tight_layout()
    savefig(argv[2])
    close()


if __name__ == "__main__":
    main()
