#!/bin/bash

bison++ -d -hPascalParser.h  -oPascalParser.cc  pascal.yy
flex++     -hPascalScanner.h -oPascalScanner.cc pascal.ll

#sed -i "s/yychar = yylex ();/yychar = fgetc(yyin);/g" pascal.tab.cc

FLAGS=$(echo "-std=c++17 -O2 " \
    "-Wno-register      "      \
    "-Wno-write-strings "      \
    "-I/E/msys64/mingw64/usr/include -I../asmjit")

g++ $FLAGS -c PascalParser.cc
g++ $FLAGS -c PascalScanner.cc
g++ $FLAGS -c x86code.cc
g++ $FLAGS -c parser.cc
g++ $FLAGS -c start.cc

g++ -O2 -o start start.o parser.o x86code.o PascalScanner.o PascalParser.o -L./ -lasmjit

strip start.exe
