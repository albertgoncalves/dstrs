#!/usr/bin/env python3

from sys import argv

from matplotlib.pyplot import close, savefig, subplots, tight_layout
from numpy import loadtxt
from seaborn import histplot


def main():
    assert len(argv) == 3
    with open(argv[1], "r") as file:
        if "." in file.readline():
            dtype = "float32"
            discrete = False
            kde_kws = {
                "bw_adjust": 1.75,
            }
        else:
            dtype = "int32"
            discrete = True
            kde_kws = {
                "bw_adjust": 5,
            }
    (_, ax) = subplots()
    histplot(
        loadtxt(argv[1], dtype=dtype, delimiter="\n"),
        discrete=discrete,
        kde=True,
        kde_kws=kde_kws,
        edgecolor="w",
        ax=ax,
    )
    tight_layout()
    savefig(argv[2])
    close()


if __name__ == "__main__":
    main()
