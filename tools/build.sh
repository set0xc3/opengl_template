#!/bin/bash

root=$PWD

files="
$root/third-party/glad/src/glad.c

$root/code/main.cpp
"

includes="
-I/usr/local/include/

-I$root/third-party/glad/include/
"

GL="
-lGL
`pkg-config --static --libs glfw3`
`pkg-config --cflags glfw3`
"

libs="
-L/usr/local/lib
-lm
-lX11
$GL
"

binary=$root/build/sandbox
flags="-O0 -g3"

mkdir -p $root/build/
clang $files $includes $flags $libs -o $binary