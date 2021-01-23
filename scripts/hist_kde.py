#!/usr/bin/env python3

from sys import argv

from matplotlib.pyplot import close, savefig, subplots, tight_layout
from numpy import loadtxt, mean, median, std
from seaborn import histplot


def main():
    assert len(argv) == 3
    with open(argv[1], "r") as file:
        line = file.readline()
    if "." in line:
        xs = loadtxt(argv[1], dtype="float32", delimiter="\n")
        kwargs = {"discrete": False, "kde_kws": {"bw_adjust": 1.75}}
    else:
        xs = loadtxt(argv[1], dtype="int32", delimiter="\n")
        kwargs = {"discrete": True, "kde_kws": {"bw_adjust": 5}}
    (_, ax) = subplots()
    histplot(xs, kde=True, edgecolor="w", ax=ax, **kwargs)
    ax.set_title(
        "  mean =>{:>9.4f}\n"
        "median =>{:>9.4f}\n"
        "   std =>{:>9.4f}".format(mean(xs), median(xs), std(xs)),
        fontsize="large",
        family="monospace",
    )
    tight_layout()
    savefig(argv[2])
    close()


if __name__ == "__main__":
    main()
