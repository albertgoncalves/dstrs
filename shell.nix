with import <nixpkgs> {};
pkgsMusl.mkShell {
    buildInputs = [
        (python38.withPackages(ps: with ps; [
            flake8
            matplotlib
            numpy
            seaborn
        ]))
        clang_10
        cppcheck
        feh
        shellcheck
    ];
    shellHook = ''
        . .shellhook
    '';
}
