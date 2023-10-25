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
    "-Wno-pmf-conversions   " \
    "-Wno-register          " \
    "-Wno-write-strings     " \
    "-DASMJIT_STATIC        " \
    "-DASMJIT_BUILD_RELEASE " \
    "-DASMJIT_NO_AARCH64    " \
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
XLTP=$(which libxslt 2&> /dev/null)
TDLG=$(which dialog)
# -----------------------------------------------------------------
MKD=$(echo "${WMKD}")   # mkdir
GCC=$(echo "${WGCC}")   # gcc
GXX=$(echo "${WGXX}")   # g++
XLT=$(echo "${XLTP}")   # xsltproc
DLG=$(echo "${TDLG}")   # dialog
# -----------------------------------------------------------------
# localization strings for this script ...
# -----------------------------------------------------------------
msg_de_DE_0000="Deutsch"
msg_de_DE_0001="bereite Setup vor..."
msg_de_DE_0002="benötigt: "
msg_de_DE_0003="Fehler:"
msg_de_DE_0004="Warnung: "
msg_de_DE_0005="Hinweis: "
msg_de_DE_0006="Debug: "
msg_de_DE_0007="nicht gefunden, nok"
msg_de_DE_0008="abbgebrochen."
msg_de_DE_0009="Bitte lesen Sie die Lizenz"
msg_de_DE_0010="Bitte warten..."
msg_de_DE_0011="Das Setup sammelt Informationen.\nDies kann einen "
msg_de_DE_0011+="Moment dauern."
msg_de_DE_0012="Datei nicht gefunden"
msg_de_DE_0013="\nSetup kann eine benötigte Datei, die für die Erstellung "
msg_de_DE_0013+="des Projects notwendig ist, nicht finden.\n"
msg_de_DE_0013+="Es wird versucht, die Datei/Package zu installieren..."
msg_de_DE_0014="Pimp Assembler-Code"
msg_de_DE_0015="\nDer generierte Assembler-Code wird aufbereitet."
msg_de_DE_0016="Erstellen der Anwendung"
msg_de_DE_0017="\nBinde binäre Daten zur Anwendung."
msg_de_DE_0018="Erstellen der Objekt-Dateien"
msg_de_DE_0019="\nDie binären Objekt-Dateien werden erstellt.\n"
msg_de_DE_0019+="Dies kann einen Moment dauern, Bitte haben Sie Geduld..."
msg_de_DE_0020="Dokumentation"
msg_de_DE_0021="\nDokumentation wird aufbereitet/erstellt.\n"
msg_de_DE_0021+="Dies kann etwas dauern..."
msg_de_DE_0022="Übersetzung abgeschloßen"
msg_de_DE_0023="\nDas Programm/Package wurde erfolgreich erstellt."
msg_de_DE_0024="Erfolgreich"
msg_de_DE_0025="\nAlle Aufgaben wurden erfolgreich ausgeführt."
# -----------------------------------------------------------------
msg_en_US_0000="English"
msg_en_US_0001="gattering setup data..."
msg_en_US_0002="requiere: "
msg_en_US_0003="Error:"
msg_en_US_0004="Warning: "
msg_en_US_0005="Info: "
msg_en_US_0006="Debug: "
msg_en_US_0007="not found, nok"
msg_en_US_0008="aborted."
msg_en_US_0009="Please read the LICENSE"
msg_en_US_0010="Please wait..."
msg_en_US_0011="Setup is gattering Informations.\nThis can take a while."
msg_en_US_0012="Missing file"
msg_en_US_0013="\nSetup missing a file, that is need for building this "
msg_en_US_0013+="Project.\nThe installer try to install the File/Package."
msg_en_US_0014="Pimp Assembler-Code"
msg_en_US_0015="\nThe generated assembler code will be re-write."
msg_en_US_0016="Create executable..."
msg_en_US_0017="\nLink object files to executable."
msg_en_US_0018="Create object files"
msg_en_US_0019="\ncreate the binary project object files.\n"
msg_en_US_0019+="This can take a while..."
msg_en_US_0020="Create documentation"
msg_en_US_0021="\nSetup create the documentation.\n"
msg_en_US_0021+="This can take a while..."
msg_en_US_0022="Compiler done"
msg_en_US_0023="\nThe Compiler return successfully.\n"
msg_en_US_0023+="Application/Package was built."
msg_en_US_0024="Successfull"
msg_en_US_0025="\nAll task's was built successfully."
# -----------------------------------------------------------------
xlen=$(tput cols)
ylen=$(tput lines)
bx=10
by=4
padbottom=2
# -----------------------------------------------------------------
# centered on width
dwidth=$(($xlen - $(($bx * 2))))
# -----------------------------------------------------------------
# leave some padding at the bottom
dheight=$(($ylen - $(($by + $padbottom))))
lic=$(cat ../LICENSE)
bgtitle="Pascal Doxy version 0.0.1 (c) 2923 by paule32"
cols="92"
rows="$(stty size | cut -d ' ' -f 1)"
dlgs="${DLG} --backtitle '$bgtitle'"
# -----------------------------------------------------------------
# place holder to provide a global common abort function:
# -----------------------------------------------------------------
errloc=()
function run_abort () {
    echo "${!errloc[8]}"
    exit 1
}
# -----------------------------------------------------------------
# default build locale is: en_US
# -----------------------------------------------------------------
function run_build_prepare () {
    loc=$(locale | grep LC_CTYPE | cut -d= -f2 | cut -d. -f1 | sed 's/"//g')
    build_locale="en_US"
    printf "[= Install Language: "
    case "$loc" in
        de_DE)  printf "Deutsch"
                build_locale="de_DE" ;;
        en_US)  printf "English"
                build_locale="en_US" ;;
        *)      build_locale="en_US"
    esac
    echo " =]"
    
    # --------------------------------------
    # first run, need the followed steps...
    # --------------------------------------
    number=$(printf "%04d" 1)
    eval "Z=msg_${build_locale}_\$number"
    errloc+=("${Z}")
    printf "[=--- ${!errloc[0]} "

    # --------------------------------------
    # fill the localization array with text:
    # --------------------------------------
    for cnt in {0..27}; do
        number=$(printf "%04d" $cnt)
        eval "Z=msg_${build_locale}_\$number"
        errloc+=("${Z}")
    done
    echo " ok. =]"

    if [[ -z "${DLG}" ]]; then
        printf "[= ${!errloc[3]}"
    else
        printf '\033[8;%d;%dt' $rows $cols
        dlg="$dlgs --title \"${!errloc[10]}\" "
        dlg+="--msgbox \"\$lic\" 20 84"
        eval "$dlg"
    fi

    # ---------------------
    # system tool: mkdir
    # ---------------------
    if [[ -z "${WMKD}" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            dlg="$dlgs --title \"${!errloc[11]}\" "
            dlg+="--gauge \"${!errloc[12]}\" 10 79 9"
            eval "$dlg"
            # todo
        else
            echo "${!errloc[3]} mkdir: ${!errloc[7]} =]"
            run_abort
        fi
    fi

    # ---------------------
    # gnu c compiler
    # ---------------------
    if [[ -z "${WGCC}" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            dlg="$dlgs --title \"${!errloc[13]}\" "
            dlg+="--gauge \"${!errloc[14]}\" 10 79 10"
            eval "$dlg"
            # todo
        else
            echo "${!errloc[3]} gcc: ${!errloc[7]} =]"
            run_abort
        fi
    fi
    
    # ---------------------
    # gnu c++ compiler
    # ---------------------
    if [[ -z "${WGXX}" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            dlg="$dlgs --title \"${!errloc[13]}\" "
            dlg+="--gauge \"${!errloc[14]}\" 10 79 11"
            eval "$dlg"
            exit 1
            # todo
        else
            echo "${!errloc[3]} g++: ${!errloc[7]} =]"
            run_abort
        fi
    fi

    # ---------------------
    # terminal dialog's
    # ---------------------
    [[ -z "${TDLG}" ]] && {
        yes | pacman -Sy dialog 2&> /dev/null
        TDLG=$(which dialog)
        [[ -z "${TDLG}" ]] && {
            echo "${!errloc[3]} dialog: ${!errloc[7]} =]"
            run_abort
        }
    }
    
    # ---------------------
    # xml processor:
    # ---------------------
    if [[ -z "${XLTP}" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            dlg="(exit 1) | $dlgs --title \"${!errloc[13]}\" "
            dlg+="--gauge \"${!errloc[14]}\" 10 79 11"
            eval "$dlg"
            yes | pacman -Sy libxslt 2&> /dev/null
        else
            XLTP=$(which xsltproc)
            if [[ -z "${XLTP}" ]]; then
                echo "${!errloc[3]} xsltproc: ${!errloc[7]} =]"
                run_abort
            fi
        fi
    fi

    # ---------------------
    # create temporary dir:
    # ---------------------
    if [[ -z "${TMP}" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            dlg="(exit 1) | $dlgs --title \"${!errloc[13]}\" \
            --gauge \"${!errloc[14]}\" 10 79 13"
            eval "$dlg"
        fi
        mkdir -p ${TMP}
    fi
    if [[ -z "${DLG}" ]]; then
        echo " ok. =]"
    fi
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
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[17]}\" \
        --gauge \"${!errloc[18]}\" 10 79 15"
        eval "$dlg"
    else
        printf "[= create asmjit.dll: "
    fi
    mkdir -p ${TMP}/asmjit
    cd ${TMP}/asmjit
    rm *.* 2&> /dev/nill

    cd ${SRC}/asmjit/core && ${GXX} $FLAGS -c *.cpp && mv *.o ${TMP}/asmjit
    cd ${SRC}/asmjit/x86  && ${GXX} $FLAGS -c *.cpp && mv *.o ${TMP}/asmjit
    cd ${TMP}/asmjit
    # -----------------------------------------------------------------
    ${GXX} -shared -O2 -o ${TMP}/asmjit/asmjit.dll ${TMP}/asmjit/*.o \
    -Wl,--subsystem,windows,--out-implib,libasmjit.a
    run_check $? "make"

    rm ${TMP}/asmjit/*.o
    strip ${TMP}/asmjit/asmjit.dll
    
    if [[ -n "${DLG}" ]]; then
        echo " ok. =]"
    fi
}
# -----------------------------------------------------------------
# create localization files ...
# -----------------------------------------------------------------
function run_build_locales () {
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[17]}\" \
        --gauge \"${!errloc[18]}\" 10 79 $1"
        eval "$dlg"
    else
        printf "[= create localization files: "
    fi
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
    
    if [[ -z "${DLG}" ]]; then
        echo "ok. =]"
    fi
}
# -----------------------------------------------------------------
# create parser ...
# -----------------------------------------------------------------
function run_build_parser () {
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[17]}\" \
        --gauge \"${!errloc[18]}\" 10 79 $1"
        eval "$dlg"
    else
        printf "[= create parser: "
    fi

    bison++ -d -h${TMP}/PascalParser.h  -o${TMP}/PascalParser.cc  \
    ${SRC}/pascal.yy 2&> /dev/null && run_check $? "pascal.yy"
    
    flex++     -h${TMP}/PascalScanner.h -o${TMP}/PascalScanner.cc \
    ${SRC}/pascal.ll 2&> /dev/null && run_check $? "pascal.ll"

    if [[ -z "${DLG}" ]]; then
        echo "ok. =]"
    fi
}
# -----------------------------------------------------------------
# create objects from .cc files ...
# -----------------------------------------------------------------
function run_build_object_files () {
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[17]}\" \
        --gauge \"${!errloc[18]}\" 10 79 $1"
        eval "$dlg"
    else
        printf "[= create object files: "
    fi
    for i in ${!obj_array[@]}; do
        DAT="${obj_array[$i]}"
        
        ${GXX} ${FLAGS} -o ${TMP}/${DAT}.o \
        -c ${SRC}/${DAT}.cc
        
        run_check $? "${DAT}.o"
    done

    ${GCC} -O2 -o ${TMP}/CommandLineToArgvA.o -c \
    ${SRC}/CommandLineToArgvA.c

    run_check $? "CommandLineToArgvA.o"
    if [[ -z "${DLG}" ]]; then
        echo "ok. =]"
    fi
}
# -----------------------------------------------------------------
# combine all together to windows application ...
# -----------------------------------------------------------------
function run_build_exec () {
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[19]}\" \
        --gauge \"${!errloc[20]}\" 10 79 $1"
        eval "$dlg"
    else
        printf "[= create executable: "
    fi
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
    # strip debug informations, and copy file to exec directory: ...
    # -----------------------------------------------------------------
    strip ${TMP}/pc.exe
    run_check $? "pc.exe"
    
    #rm ${TMP}/*.o && rm ${TMP}/*.cc && rm ${TMP}/*.h
    if [[ -z "${DLG}" ]]; then
        echo "ok. =]"
    fi
}
# -----------------------------------------------------------------
# switch to exec directory, and perform the tasks to assemble the
# generated asmjit code with nasm.
# nasm.exe is the netwide assembler that can generated a wide range
# of different binary object file formats.
# -----------------------------------------------------------------
function run_build_nasm_source () {
    # update screen dialog
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[15]}\" \
        --gauge \"${!errloc[16]}\" 10 79 98"
        eval "$dlg"
    else
        printf "[= create nasm source: "
    fi

    sed -i 's/\.section \.text {\#.*/section \.text/g' $1.asm
    sed -i 's/\.section \.data {\#.*/section \.data/g' $1.asm
    sed -i 's/qword ptr/qword/g' $1.asm
    sed -i 's/\.db/db/g' $1.asm

    # ----------------------------------------
    # replace map list with offset values ...
    # ----------------------------------------
    maplist=$(printf "
        tmp_array=()
        tmp_array_func=()
        ")
    maplist+=$(grep "; T" $1.asm | awk '{ print $4 } ' \
        | sed -e 's/^/tmp_array_func\+\=\(\"/' \
        | sed -e 's/$/\"\)/')
    maplist+=$(printf "\n ")
    maplist+=$(grep "; T" $1.asm | awk '{ print $3 } '\
        | cut -f2 -d "x"                  \
        | cut -c 5-                       \
        | sed -e 's/^/tmp_array\+\=\(\"/' \
        | sed -e 's/$/\"\)/')
    maplist+=$(printf "\n
        arr_cols=0
        cp $1.asm test2.asm
        for el in \${tmp_array[@]}; do
            if [[ \"\$el\" == \"000000000000\" ]]; then
                ((arr_cols++))
                continue
            fi
            sedcmd=\"sed -i \'s/0x\${el^^}/\"
            sedcmd+=\"\${tmp_array_func[\$arr_cols]}/g\' \"
            sedcmd+=\"test2.asm\"
            eval "\$sedcmd"
            ((arr_cols++))
        done")
#   echo "$maplist"
    eval "$maplist"

    #asmtxt=""
    #for el in ${tmp_array_func[@]}; do
    #    asmtxt+="extern $el\n"
    #done
    #asmdat=$(cat test2.asm)
    #asmdat+="\n$asmtxt\n"
    #echo -e "$asmdat" > test3.asm
    
    nasm -f win64 -o test2.o test2.asm
    run_check $? "nasm test2.asm"
    
    if [[ -z "${DLG}" ]]; then
        echo "ok. =]"
    fi
}
# -----------------------------------------------------------------
# create the documentation to this project/package:
# DEU = German
# ENU = English
# -----------------------------------------------------------------
function run_build_doc_xml () {
    if [[ -z "${DLG}" ]]; then
        echo "$1"
    else
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[21]}\" \
        --gauge \"${!errloc[22]}\" 10 79 $2"
        eval "$dlg"
    fi
}
# -----------------------------------------------------------------
# switch back to developer source path ...
# -----------------------------------------------------------------
cd ${TMP}
run_build_prepare

run_build_doc_xml deu  20
run_build_doc_xml enu  22

run_build_locales      30
run_build_parser       32
run_build_object_files 40
run_build_exec         42

cd ${TMP}
if [[ -z "${DLG}" ]]; then
    printf "done.\n\n"
else
    printf '\033[8;%d;%dt' $rows $cols
    dlg="(exit 1) | $dlgs --title \"${!errloc[23]}\" \
    --gauge \"${!errloc[24]}\" 10 79 94"
    eval "$dlg"
fi

# -----------------------------------------------------------------
# when all is done, then start a test ...
# -----------------------------------------------------------------
if [[ -z "${DLG}" ]]; then
    clear
    printf "[= start test: "
else
    printf '\033[8;%d;%dt' $rows $cols
    dlg="(exit 1) | $dlgs --title \"${!errloc[23]}\" \
    --gauge \"${!errloc[24]}\" 10 79 96"
    eval "$dlg"
fi
LD_LIBRARY_PATH=./asmjit;./pc.exe ${SRC}/test.pas
#&> /dev/null
run_check $? "pc.exe"
if [[ -z "${DLG}" ]]; then
    echo "ok. =]"
else
    printf '\033[8;%d;%dt' $rows $cols
    dlg="(exit 1) | $dlgs --title \"${!errloc[23]}\" \
    --gauge \"${!errloc[24]}\" 10 79 98"
    eval "$dlg"
fi

run_build_nasm_source test

if [[ -n "${DLG}" ]]; then
    printf '\033[8;%d;%dt' $rows $cols
    dlg="(sleep 4 ; exit 1) | $dlgs --title \"${!errloc[25]}\" \
    --msgbox \"${!errloc[26]}\" 10 79"
    eval "$dlg"
fi
cd ${SRC}
clear
