#!/usr/bin/env python3

from sys import argv

from matplotlib.pyplot import close, savefig, subplots, tight_layout
from numpy import loadtxt
from seaborn import histplot


def main():
    assert len(argv) == 3
    (_, ax) = subplots()
    histplot(
        loadtxt(argv[1], dtype="float32", delimiter="\n"),
        kde=True,
        edgecolor="w",
        ax=ax,
    )
    tight_layout()
    savefig(argv[2])
    close()


if __name__ == "__main__":
    main()
