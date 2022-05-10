#!/bin/bash

set -e


cmake_command="cmake"
options="-A $(uname -i)"

case $1 in

"rm")  rm -rf _build
;;

"clean")  $cmake_command --build _build --target clean
;;

*)
    $cmake_command -S . -B _build
    $cmake_command --build _build
;;

esac
