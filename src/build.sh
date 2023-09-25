#!/bin/bash

cd po && ./build.sh && cd ..

bison++ -d -hPascalParser.h  -oPascalParser.cc  pascal.yy
flex++     -hPascalScanner.h -oPascalScanner.cc pascal.ll

FLAGS=$(echo "-std=c++17 -O2 " \
    "-Wno-register      "      \
    "-Wno-write-strings "      \
    "-DASMJIT_STATIC -DASMJIT_BUILD_RELEASE -DASMJIT_NO_AARCH64 " \
    "-I/E/msys64/mingw64/usr/include -I../asmjit")

g++ $FLAGS -c PascalParser.cc
g++ $FLAGS -c PascalScanner.cc
g++ $FLAGS -c x86code.cc
g++ $FLAGS -c parser.cc
g++ $FLAGS -c start.cc

g++ -O2 -o start.exe start.o parser.o x86code.o PascalScanner.o PascalParser.o -L./ -lasmjit -lintl

strip start.exe

cp start.exe ../exec/start.exe
