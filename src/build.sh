#!/bin/bash
# -----------------------------------------------------------------
# File:   build.sh
# Author: (c) 2023 Jens Kallup - paule32
# All rights reserved
#
# only for education, and non-profit usage !
# -----------------------------------------------------------------
cd po && ./build.sh && cd ..

bison++ -d -hPascalParser.h  -oPascalParser.cc  pascal.yy
flex++     -hPascalScanner.h -oPascalScanner.cc pascal.ll

FLAGS=$(echo "-std=c++17 -O2 " \
    "-Wno-register      "      \
    "-Wno-write-strings "      \
    "-DASMJIT_STATIC -DASMJIT_BUILD_RELEASE -DASMJIT_NO_AARCH64 " \
    "-I/E/msys64/mingw64/usr/include -I../asmjit")

mkdir temp

g++ $FLAGS -o temp/PascalParser.o  -c PascalParser.cc
g++ $FLAGS -o temp/PascalScanner.o -c PascalScanner.cc
g++ $FLAGS -o temp/x86Code.o       -c x86Code.cc
g++ $FLAGS -o temp/parser.o        -c parser.cc
g++ $FLAGS -o temp/start.o         -c start.cc
g++ $FLAGS -o temp/win32api.o      -c win32api.cc

g++ -o start.exe \
    start.o parser.o x86code.o PascalScanner.o PascalParser.o \
    -L./ -lasmjit -lintl

strip start.exe
cp start.exe ../exec/start.exe
