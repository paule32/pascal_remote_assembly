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

mkdir -p temp

# -----------------------------------------------------------------
# create objects from .cc files ...
# -----------------------------------------------------------------
g++ $FLAGS -o temp/PascalParser.o  -c PascalParser.cc
g++ $FLAGS -o temp/PascalScanner.o -c PascalScanner.cc
g++ $FLAGS -o temp/x86Code.o       -c x86Code.cc
g++ $FLAGS -o temp/parser.o        -c parser.cc
g++ $FLAGS -o temp/start.o         -c start.cc
g++ $FLAGS -o temp/win32api.o      -c win32api.cc

gcc -O2 -o temp/CommandLineToArgvA.o -c CommandLineToArgvA.c

# -----------------------------------------------------------------
# combine all together to windows application ...
# -----------------------------------------------------------------
g++ -o pc.exe            \
    temp/start.o         \
    temp/CommandLineToArgvA.o \
    temp/win32api.o      \
    temp/parser.o        \
    temp/x86code.o       \
    temp/PascalScanner.o \
    temp/PascalParser.o  \
    -L./ -lasmjit -lintl

# -----------------------------------------------------------------
# strip debug informations, and copy file to exec directory ...
# -----------------------------------------------------------------
strip pc.exe
cp    pc.exe ../exec/pc.exe

# -----------------------------------------------------------------
# switch to exec directory, and perform the tasks to assemble the
# generated asmjit code with nasm.
# nasm.exe is the netwide assembler that can generated a wide range
# of different binary object file formats.
# -----------------------------------------------------------------
cd ../exec
dir
./pc.exe test.pas

sed -i 's/\.section \.text {\#.*/section \.text/g' test.asm
sed -i 's/\.section \.data {\#.*/section \.data/g' test.asm
sed -i 's/\.db/db/g' test.asm

nasm -f win64 -o test.o test.asm

# -----------------------------------------------------------------
# switch back to developer source path ...
# -----------------------------------------------------------------
cd ../src
echo "done."
