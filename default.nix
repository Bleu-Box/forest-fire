with (import <nixpkgs> {});

stdenv.mkDerivation rec {
   name = "forest-fire";
   buildInputs = [
     gcc
     gnumake
     SDL2
   ];
}
