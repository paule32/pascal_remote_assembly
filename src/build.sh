#!/bin/bash
# -----------------------------------------------------------------
# File:   build.sh
# Author: (c) 2023 Jens Kallup - paule32
# All rights reserved
#
# only for education, and non-profit usage !
# -----------------------------------------------------------------
PWD=$(pwd)
SRC=$(echo "${PWD}")
TEMP="temp"
TMP=$(echo "${PWD}/${TEMP}")
FLAGS=$(echo "-std=c++17 -O2 -fPIC " \
    "-Wno-register      "      \
    "-Wno-write-strings "      \
    "-DASMJIT_STATIC    "      \
    "-DASMJIT_BUILD_RELEASE "  \
    "-DASMJIT_NO_AARCH64 " \
    "-I/E/msys64/mingw64/usr/include -I${SRC}/asmjit -I${TMP}")
# -----------------------------------------------------------------
ST1="s/\\\"Last\\-Translator\\: .*\\n\\\"/\\\"Last-Translator\\:"
ST2="Jens Kallup \\<paule32\\.jk\\@gmail\\.com\\>\\n\\\"/g"
# -----------------------------------------------------------------
ATXT="| awk '{print \$3}' | cut -d '=' -f 2"
# -----------------------------------------------------------------
# prepare compilation tasks ...
# -----------------------------------------------------------------
obj_array=("PascalParser" "PascalScanner" "x86Code" "parser" \
"start" "win32api")
# -----------------------------------------------------------------
WMKD=$(which mkdir)
WGCC=$(which gcc)
WGXX=$(which g++)
XLTP=$(which xsltproc)
MKD=$(echo "${WMKD}")
GCC=$(echo "${WGCC}")
GXX=$(echo "${WGXX}")
XLT=$(echo "${XLTP}")
# -----------------------------------------------------------------
# localization strings for this script ...
# -----------------------------------------------------------------
msg_de_DE_0000="Fehler: "
msg_en_US_0000="Error: "
# -----------------------------------------------------------------
arrloc=( \
'de_DE=("${msg_de_DE_0000}" "v2" "v3")' \
'en_US=(e1 e2 e3)' )
# -----------------------------------------------------------------
function run_build_prepare () {
    loc=$(locale | grep LC_CTYPE | cut -d= -f2 | cut -d. -f1 | sed 's/"//g')
    printf "[= Install Language: "
    case "$loc" in
        de_DE) printf "Deutsch" ;;
        en_US) printf "English" ;;
        *)     printf "English as alternative"
    esac
    echo " =]"
    for elt in "${arrloc[@]}";do eval $elt;done
    echo "${de_DE[0]}"
    exit 1

    printf "[= check storage structure: "

    [[ -z "${WMKD}" ]] && { echo "Error: mkdir not found. =]";    exit 1; }
    [[ -z "${WGCC}" ]] && { echo "Error: gcc not found. =]";      exit 1; }
    [[ -z "${WGXX}" ]] && { echo "Error: g++ not found. =]";      exit 1; }
    [[ -z "${XLTP}" ]] && { echo "Error: xsltproc not found. =]"; exit 1; }

    [[ -z "${TMP}" ]] && mkdir -p ${TMP}
    echo " ok. =]"
}
# -----------------------------------------------------------------
# check last command return value. if it > 0 then error message ...
# -----------------------------------------------------------------
function run_check () {
    if [[ ! $1 -eq 0 ]]; then
        echo "Error: ($2) exec failed. =]"
        echo "aborted."
        exit $1
    fi
}
# -----------------------------------------------------------------
# check, if file exists. no? then exit ...
# -----------------------------------------------------------------
function check_file () {
    NAME="$(basename $1 $2)"
    if [[ ! -f "$1" ]]; then
        echo "Error: (${NAME}$2) does not exists. =]"
        echo "aborted."
        exit 1
    fi
}
# -----------------------------------------------------------------
# write the final localization file "*.mo" ...
# -----------------------------------------------------------------
function runiconv () {
    ret="iconv --from-code=$1 --to-code=UTF-8 $2.text > $2_utf8.pot"
    res=$(eval "$ret")
    run_check $? "iconv $2"

    msginit --locale $2       \
    --output-file $2_utf8.po  \
    --input       $2_utf8.pot 2> /dev/null
    run_check $?   "msginit $2"

    perl -pi -e "${ST1} ${ST2}" $2_utf8.po
    run_check $? "perl $2}"

    msgfmt --check --output-file $2_utf8.mo $2_utf8.po
    run_check $? "msgfmt $2"
    
    gzip -9 -c $2_utf8.mo > $3/$2_utf8.mo.gz
    run_check $? "gzip $2"
}
# -----------------------------------------------------------------
# build asmjit.dll
# -----------------------------------------------------------------
function run_build_asmjit () {
    printf "[= create asmjit.dll: "
    mkdir -p ${TMP}/asmjit
    cd ${TMP}/asmjit
    rm *.* 2> /dev/nill

    cd ${SRC}/asmjit/core && ${GXX} $FLAGS -c *.cpp && mv *.o ${TMP}/asmjit
    cd ${SRC}/asmjit/x86  && ${GXX} $FLAGS -c *.cpp && mv *.o ${TMP}/asmjit
    cd ${TMP}/asmjit
    # -----------------------------------------------------------------
    ${GXX} -shared -O2 -o ${TMP}/asmjit/asmjit.dll ${TMP}/asmjit/*.o \
    -Wl,--subsystem,windows,--out-implib,libasmjit.a
    run_check $? "make"

    rm ${TMP}/asmjit/*.o
    strip ${TMP}/asmjit/asmjit.dll
    echo " ok. =]"
}
# -----------------------------------------------------------------
# create localization files ...
# -----------------------------------------------------------------
function run_build_locales () {
    printf "[= create localization files: "
    cd ${SRC}/po
    # -----------------------------------------------------------------
    # get encoding from original "*.text" file
    # -----------------------------------------------------------------
    loc_array=("de_DE" "en_US")
    
    for i in ${!loc_array[@]}; do
        DAT="${loc_array[$i]}"
        DIR="${TMP}/locales/${DAT}/LC_MESSAGES"
        CHK="${SRC}/po/${DAT}.text"
        ENC="file -i ${CHK} ${ATXT}"

        check_file ${CHK} ".text"
        ${MKD}  -p ${DIR}
        ret=$(eval "$ENC")

        runiconv ${ret} ${DAT} ${DIR}
    done
    
    rm ${SRC}/po/*.po && rm ${SRC}/po/*.pot
    rm ${SRC}/po/*.mo
    
    echo "ok. =]"
}
# -----------------------------------------------------------------
# create parser ...
# -----------------------------------------------------------------
function run_build_parser () {
    printf "[= create parser: "
    bison++ -d -h${TMP}/PascalParser.h  -o${TMP}/PascalParser.cc  \
    ${SRC}/pascal.yy 2> /dev/null && run_check $? "pascal.yy"
    
    flex++     -h${TMP}/PascalScanner.h -o${TMP}/PascalScanner.cc \
    ${SRC}/pascal.ll 2> /dev/null && run_check $? "pascal.ll"
    echo "ok. =]"
}
# -----------------------------------------------------------------
# create objects from .cc files ...
# -----------------------------------------------------------------
function run_build_object_files () {
    printf "[= create object files: "
    for i in ${!obj_array[@]}; do
        DAT="${obj_array[$i]}"
        
        ${GXX} ${FLAGS} -o ${TMP}/${DAT}.o \
        -c ${SRC}/${DAT}.cc
        
        run_check $? "${DAT}.o"
    done

    ${GCC} -O2 -o ${TMP}/CommandLineToArgvA.o -c \
    ${SRC}/CommandLineToArgvA.c

    run_check $? "CommandLineToArgvA.o"
    echo "ok. =]"
}
# -----------------------------------------------------------------
# combine all together to windows application ...
# -----------------------------------------------------------------
function run_build_exec () {
    printf "[= create executable: "
    DAT=""

    for i in ${!obj_array[@]}; do
        DAT="${DAT} ${TMP}/${obj_array[$i]}.o"
    done
    DAT="${DAT} ${TMP}/CommandLineToArgvA.o"
    ${GXX} -o ${TMP}/pc.exe ${DAT} \
        -L${TMP}/asmjit -lasmjit   \
        -lintl -lgmpxx
    run_check $? "pc.exe"

    # -----------------------------------------------------------------
    # strip debug informations, and copy file to exec directory ...
    # -----------------------------------------------------------------
    strip ${TMP}/pc.exe
    run_check $? "pc.exe"
    
    #rm ${TMP}/*.o && rm ${TMP}/*.cc && rm ${TMP}/*.h
    echo "ok. =]"
}
# -----------------------------------------------------------------
# switch to exec directory, and perform the tasks to assemble the
# generated asmjit code with nasm.
# nasm.exe is the netwide assembler that can generated a wide range
# of different binary object file formats.
# -----------------------------------------------------------------
function run_build_nasm_source () {
    printf "[= create nasm source: "
    sed -i 's/\.section \.text {\#.*/section \.text/g' test.asm
    sed -i 's/\.section \.data {\#.*/section \.data/g' test.asm
    sed -i 's/\.db/db/g' test.asm

    nasm -f win64 -o test.o test.asm
    run_check $? "nasm test.asm"
    
    echo "ok. =]"
}
# -----------------------------------------------------------------
# create the documentation to this project/package:
# DEU = German
# ENU = English
# -----------------------------------------------------------------
function build_doc_xml () {
echo $1
}
# -----------------------------------------------------------------
# switch back to developer source path ...
# -----------------------------------------------------------------
run_build_prepare

run_build_doc_xml deu
run_build_doc_xml enu

run_build_locales
run_build_parser
run_build_object_files
run_build_exec

cd ${TMP} && printf "done.\n\n"

# -----------------------------------------------------------------
# when all is done, then start a test ...
# -----------------------------------------------------------------
printf "[= start test: "
LD_LIBRARY_PATH=./asmjit;./pc.exe ${SRC}/test.pas
run_check $? "pc.exe"
echo "ok. =]

cd ${SRC}
