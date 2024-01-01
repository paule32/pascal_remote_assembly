#!/bin/bash
# -----------------------------------------------------------------
# File:   build.sh
# Author: (c) 2024-01-01 Jens Kallup - paule32
# All rights reserved
#
# only for education, and non-profit usage !
#
# This is the MSYS2 Windows 10 64-Bit Pro MinGW-64 script file to
# create the documentation.
# It will work under MSYS2.
# -----------------------------------------------------------------
PWD=$(pwd)
SRC=$(echo "${PWD}")

TEMP="temp"
TMP=$(echo "${PWD}/${TEMP}")

# 1.10.0
DOXYGEN="/E/doxygen/bin/doxygen.exe"

rm -rf ${SRC}/dox
rm -rf ${TMP}/*.tmp

mkdir -p ${SRC}/dox/deu/dark

${DOXYGEN} ${SRC}/Doxyfile.Server.chm.DEU.dark.ini
cp ${SRC}/dox/deu/dark/html/server.dark.deu.chm ${SRC}/dox/server.dark.deu.chm

#rm -rf ${SRC}/dox/deu
#rm -rf ${TMP}/*.tmp
