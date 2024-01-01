:: -----------------------------------------------------------------
:: File:   doxygen.dos.bat
:: Author: (c) 2024-01-01 Jens Kallup - paule32
:: All rights reserved
::
:: only for education, and non-profit usage !
::
:: This is the Windows 10 64-Bit Pro Command Line Batch File script
:: file to create the documentation.
:: -----------------------------------------------------------------
@echo off

:: Windows Volume E: must be exists !
::
:: DOXYGENPATH = E:\doxygen\bin  -  the path to the doxygen Version 1.10.0
:: DOXYGEN     = doxygen.exe     -  the executable file of doxygen
::
set DOXYGENPATH=E:\doxygen\bin
set DOXYGEN=%DOXYGENPATH%\doxygen.exe

:: set source directory - E:\temp\src
set SRC=E:\temp\src

:: switch to Windows Volume
E:
cd \

:: create directories
md E:\temp
md E:\temp\src

:: enter TEMP directory
cd E:\temp\src

:: make sub directories
mmkdir temp
md  dox
md  dox\deu
md  dox\deu\dark
md  dox\deu\dark\html

:: 1.10.0
echo %DOXYGEN$

:: try to create create the CHM documentation
%DOXYGEN% %SRC%\Doxyfile.Server.chm.DEU.dark.ini
