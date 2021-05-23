with import <nixpkgs> {};
mkShell.override { stdenv = llvmPackages_11.stdenv; } {
    buildInputs = [
        (python38.withPackages (ps: with ps; [
            flake8
            matplotlib
            numpy
            seaborn
        ]))
        cppcheck
        feh
        linuxPackages.perf
        shellcheck
    ];
    shellHook = ''
        . .shellhook
    '';
}
