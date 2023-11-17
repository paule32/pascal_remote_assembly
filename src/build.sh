#!/bin/bash
# -----------------------------------------------------------------
# File:   build.sh
# Author: (c) 2023 Jens Kallup - paule32
# All rights reserved
#
# only for education, and non-profit usage !
# -----------------------------------------------------------------
PWD=$(pwd)

# -----------------------------------------------------------------
# custom stuff ...
# -----------------------------------------------------------------
export ASMJIT_PRODUCTIVE="no"
export ASMJIT_APPNAMEENV="asmjit"

export ASMJIT_APPNAME_EXEPATH="\"${PWD}\""
export ASMJIT_APPNAME_EXEFILE="\"${ASMJIT_APPNAMEENV}.exe\""

export ASMJIT_APPNAME_HLPFILE="\"${ASMJIT_APPNAMEENV}.hlp\""

export ASMJIT_APPNAME_INIFILE="\"${ASMJIT_APPNAMEENV}.ini\""
export ASMJIT_APPNAME_LOGFILE="\"${ASMJIT_APPNAMEENV}.log\""

# -----------------------------------------------------------------
# internal stuff ...
# -----------------------------------------------------------------
SRC=$(echo "${PWD}")
TEMP="temp"
TMP=$(echo "${PWD}/${TEMP}")
FLAGS=$(echo "-std=c++20 -O2 -fPIC "        \
    "-DASMJIT_APPNAME=\"asmjit\"" \
    "-DASMJIT_APPNAME_EXEFILE=${ASMJIT_APPNAME_EXEFILE}" \
    "-DASMJIT_APPNAME_EXEPATH=${ASMJIT_APPNAME_EXEPATH}" \
    "-DASMJIT_APPNAME_HLPFILE=${ASMJIT_APPNAME_HLPFILE}" \
    "-DASMJIT_APPNAME_INIFILE=${ASMJIT_APPNAME_INIFILE}" \
    "-DASMJIT_APPNAME_LOGFILE=${ASMJIT_APPNAME_LOGFILE}" \
    "-Wno-pmf-conversions   " \
    "-Wno-deprecated        " \
    "-Wno-register          " \
    "-Wno-volatile          " \
    "-Wno-write-strings     " \
    "-Wno-invalid-offsetof  " \
    "-DASMJIT_STATIC        " \
    "-DASMJIT_BUILD_RELEASE " \
    "-DASMJIT_NO_AARCH64    " \
    "-D__FLAT__     " \
    "-U__BORLANDC__ " \
    "-I/E/msys64/mingw64/usr/include   " \
    "-I${SRC}/include                  " \
    "-I${SRC}/include/tvision          " \
    "-I${SRC}/include/tvision/compat   " \
    "-I${SRC}/include/tvision/compat/borland " \
    "-I${SRC}/include/tvision/internal " \
    "-I${SRC}/asmjit -I${TMP}")
# -----------------------------------------------------------------
ST1="s/\\\"Last\\-Translator\\: .*\\n\\\"/\\\"Last-Translator\\:"
ST2="Jens Kallup \\<paule32\\.jk\\@gmail\\.com\\>\\n\\\"/g"
# -----------------------------------------------------------------
# prepare compilation tasks ...
# -----------------------------------------------------------------
obj_array1=("PascalParser" "PascalScanner" "x86Code" "parser" \
"start" "win32api" "ErrorHandler")
obj_array2=("interpreter" "ErrorHandler")
obj_array3=("AssemblerParser" "AssemblerScanner")
loc_array=("de_DE" "en_US")
# -----------------------------------------------------------------
WMKD=$(which mkdir)
NASM=$(which nasm)
WGCC=$(which gcc)
WGXX=$(which g++)
XLTP=$(which libxslt 2&> /dev/null)
TDLG=$(which dialog)
# -----------------------------------------------------------------
MKD=$(echo "${WMKD}")   # mkdir
ASM=$(echo "${NASM}")   # nasm
GCC=$(echo "${WGCC}")   # gcc
GXX=$(echo "${WGXX}")   # g++
XLT=$(echo "${XLTP}")   # xsltproc
DLG=$(echo "${TDLG}")   # dialog
# -----------------------------------------------------------------
BISON="/usr/bin/bison"
FLEX="/usr/bin/flex"
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
msg_de_DE_0026="Löschen der Debug-Informationen"
msg_de_DE_0027="\nverkleinere Anwendungs-Datei, um die Debug-Informationen-"
msg_de_DE_0028="Erstelle Script Dateien"
msg_de_DE_0029="Die Skript-Dateien für Lexer,und Parser werden erstellt..."
msg_de_DE_0030="Fehler aufgetretten"
msg_de_DE_0031="Es wurde ein Fehler vom Compiler zurückgegeben."
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
msg_en_US_0026="Delete Debug-Information"
msg_en_US_0027="shrink Application, delete Debug-Informations-"
msg_en_US_0028="Create Lexer/Parser"
msg_en_US_0029="Create script files for Lexer, and Parser..."
msg_en_US_0030="Error occured."
msg_en_US_0031="Error occured while compile file: "
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
cols="92"
rows="$(stty size | cut -d ' ' -f 1)"
dlgs="${DLG} --backtitle \"Pascal Doxy version 0.0.1 (c) 2923 by paule32\""
# -----------------------------------------------------------------
# place holder to provide a global common abort function:
# -----------------------------------------------------------------
errloc=()
function run_abort () {
    if [[ $1 -eq 0 ]]; then
        return
    else
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            eval "${dlgs} --title \"Error\" --msgbox \"$2\" 14 79"
            cd ${SRC}
            clear
            exit 1
        else
            echo "Error: $2"
            cd ${SRC}
            exit 1
        fi
    fi
    exit 1
}
# -----------------------------------------------------------------
# check last command return value. if it > 0 then error message ...
# -----------------------------------------------------------------
function run_check () {
    if [[ $1 -eq 0 ]]; then
        return
    fi
    if [[ -z "$2" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            eval "${dlgs} --title \"Success\" --msgbox \"no error detected\" 14 79"
            echo "ssss"
            cd ${SRC}
            #clear
            exit 1
        else
            echo "no error detected."
            cd ${SRC}
            exit 1
        fi
    else
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            eval "${dlgs} --title \"Error\" --msgbox \"$2\" 14 79"
            echo "$2"
            cd ${SRC}
            #clear
            exit 1
        else
            echo "Error: $2"
            cd ${SRC}
            exit 1
        fi
    fi
}
# --------------------------------------
# fill the localization array with text:
# --------------------------------------
function fill_locale () {
    number=$(printf "%04d" 1)
    Z=$(echo "msg_${build_locale}_$number")
    errloc+=("${Z}")
    printf "[=--- ${!errloc[0]} "
    for cnt in {0..31}; do
        number=$(printf "%04d" $cnt)
        Z=$(echo "msg_${build_locale}_$number")
        errloc+=("${Z}")
    done
    echo " ok. =]"
}
# -----------------------------------------------------------------
# default build locale is: en_US
# -----------------------------------------------------------------
function run_build_prepare () {
    # --- [ dev ] ---
    if [[ -n "${ASMJIT_PRODUCTIVE}" ]]; then
        build_locale="en_US"
        fill_locale
        return
    fi
    # --- [ end ] ---
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
    fill_locale

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
            run_abort 1 "${!errloc[3]} mkdir: ${!errloc[7]} =]"
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
            run_abort 1 "${!errloc[3]} gcc: ${!errloc[7]} =]"
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
            run_abort 1 "${!errloc[3]} g++: ${!errloc[7]} =]"
        fi
    fi

    # ---------------------
    # terminal dialog's
    # ---------------------
    [[ -z "${TDLG}" ]] && {
        yes | pacman -Sy dialog 2&> /dev/null
        TDLG=$(which dialog)
        [[ -z "${TDLG}" ]] && {
            run_abort 1 "${!errloc[3]} dialog: ${!errloc[7]} =]"
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
                run_abort 1 "${!errloc[3]} xsltproc: ${!errloc[7]} =]"
            fi
        fi
    fi
    
    # ---------------------
    # nasm assembler:
    # ---------------------
    if [[ -z "${NASM}" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            dlg="(exit 1) | $dlgs --title \"${!errloc[13]}\" "
            dlg+="--gauge \"${!errloc[14]}\" 10 79 12"
            eval "$dlg"
            yes | pacman -Sy mingw-w64-x86_64-nasm 2&> /dev/null
        else
            XLTP=$(which xsltproc)
            if [[ -z "${XLTP}" ]]; then
                run_abort 1 "${!errloc[3]} nasm: ${!errloc[7]} =]"
            fi
        fi
    fi

    # ---------------------
    # install boost lib:
    # ---------------------
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[13]}\" "
        dlg+="--gauge \"${!errloc[14]}\" 10 79 13"
        eval "$dlg"
        cmd=$(yes | pacman -S mingw-w64-x86_64-boost 2>&1 ); run_abort $? "${cmd}"
        cmd=$(yes | pacman -S mingw-w64-x86_64-zlib  2>&1 ); run_abort $? "${cmd}"
    else
        cmd=$(yes | pacman -S mingw-w64-x86_64-boost 2>&1 ); run_abort $? "${cmd}"
        cmd=$(yes | pacman -S mingw-w64-x86_64-zlib  2>&1 ); run_abort $? "${cmd}"
    fi
    
    # ---------------------
    # create temporary dir:
    # ---------------------
    if [[ -z "${TMP}" ]]; then
        if [[ -n "${DLG}" ]]; then
            printf '\033[8;%d;%dt' $rows $cols
            dlg="(exit 1) | $dlgs --title \"${!errloc[13]}\" \
            --gauge \"${!errloc[14]}\" 10 79 14"
            eval "$dlg"
        fi
        mkdir -p ${TMP}
    fi
    if [[ -z "${DLG}" ]]; then
        echo " ok. =]"
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
    res=$(iconv --from-code=$1 --to-code=UTF-8 "$4.text" > $3/$2_utf8.pot)
    res=$(eval "$ret")
    run_check $? "iconv $1 $2 $3 $4"
    
    cmd=$(msginit \
    --locale=$2   \
    --input=$3/$2_utf8.pot \
    --output-file=$3/$2_utf8.po   2>&1 ); run_check $? "${cmd}"
    cmd=$(rm -rf $3/$2_utf8.mo    2>&1 ); run_check $? "${cmd}"
    cmd=$(rm -rf $3/$2_utf8.mo.gz 2>&1 ); run_check $? "${cmd}"

    cmd=$(perl -pi -e "${ST1} ${ST2}"  $$_utf8.po       2>&1 ); run_check $? "${cmd}"
    cmd=$(msgfmt --check -o $3/$2_utf8.mo $3/$2_utf8.po 2>&1 ); run_check $? "${cmd}"
    cmd=$(gzip           -9 $3/$2_utf8.mo               2>&1 ); run_check $? "${cmd}"
    
    cmd=$(cp $3/$2_utf8.mo.gz $3/${ASMJIT_APPNAMEENV}app.mo.gz 2>&1 ); run_check $? "${cmd}"
    
    rm -rf $3/$2_utf8.pot 
    rm -rf $3/$2_utf8.po
    rm -rf $3/$2_utf8.mo
    rm -rf $3/$2_utf8.mo.gz
}
# -----------------------------------------------------------------
# build asmjit.dll
# -----------------------------------------------------------------
function run_build_asmjit () {
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[17]}\" \
        --gauge \"${!errloc[18]}\" 10 79 $1"
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
# get encoding from original "*.text" file
# -----------------------------------------------------------------
function run_build_locales_helper () {
    cd ${SRC}/po
    for i in ${!loc_array[@]}; do
        DAT="${loc_array[$i]}"
        DIR="${TMP}/locale/${DAT}.utf8/LC_MESSAGES"
        CHK="${SRC}/po/${DAT}"

        check_file "${CHK}.text" ".text"
        ${MKD}  -p ${DIR}

        cmd=$(file -i "${CHK}.text" | awk '{ print $3 }')
        eco=$(echo ${cmd:8:21})
        
        runiconv ${eco} ${DAT} ${DIR} ${CHK}
    done
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
    
    run_build_locales_helper ${build_locale}
    
    #rm ${TMP}/locale/de_DE
    
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
    for i in ${!obj_array1[@]}; do
        DAT="${obj_array1[$i]}"
        
        ${GXX} ${FLAGS} -DHAVE_PARSER_PAS -o ${TMP}/${DAT}.o \
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
    for i in ${!obj_array1[@]}; do
        DAT="${DAT} ${TMP}/${obj_array1[$i]}.o"
    done
    DAT="${DAT} ${TMP}/CommandLineToArgvA.o"
    ${GXX} -o ${TMP}/pc.exe ${DAT} \
        -L${TMP}/asmjit -lasmjit   \
        -lintl -lgmpxx
    run_check $? "link pc.exe"

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
    maplist+=$(cat $1.asm | grep "; T" $1.asm | awk '{ print $4 } ' \
        | sed -e 's/^/tmp_array_func\+\=\(\"/' \
        | sed -e 's/$/\"\)/')
    maplist+=$(printf "\n ")
    maplist+=$(cat $1.asm | grep "; T" $1.asm | awk '{ print $3 } '\
        | cut -f2 -d "x"                  \
        | cut -c 5-                       \
        | sed -e 's/^/tmp_array\+\=\(\"/' \
        | sed -e 's/$/\"\)/')
    maplist+=$(printf "\n
        arr_cols=0
        #cp $1.asm $1_nasm.asm
        for el in \${tmp_array[@]}; do
            if [[ \"\$el\" == \"000000000000\" ]]; then
                ((arr_cols++))
                continue
            fi
            sedcmd=\"sed -i \'s/0x\${el^^}/\"
            sedcmd+=\"\${tmp_array_func[\$arr_cols]}/g\' \"
            sedcmd+=\"$1.asm\"
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
    
    nasm -f win64 -o ${built_run%.*}.o ${built_run%.*}.asm
    run_check $? "nasm $1_name.asm"
    
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
# ----------------------------------------
# link diss.exe application ...
# ----------------------------------------
function run_build_application ()
{
    cmd=$(${GXX} ${FLAGS} -DHAVE_PARSER_ASM -o ${TMP}/diss.exe \
        -L${TMP}/ -L./asmjit        \
        \
        ${TMP}/ascii.o              \
        ${TMP}/calc.o               \
        ${TMP}/evntview.o           \
        ${TMP}/gadgets.o            \
        ${TMP}/puzzle.o             \
        ${TMP}/tvdemo2.o            \
        ${TMP}/backgrnd.o           \
        ${TMP}/calendar.o           \
        ${TMP}/fileview.o           \
        ${TMP}/mousedlg.o           \
        ${TMP}/tvdemo1.o            \
        ${TMP}/tvdemo3.o            \
        ${TMP}/Interpreter.o        \
        ${TMP}/AssemblerParser.o    \
        ${TMP}/AssemblerScanner.o   \
        \
        ${TMP}/dwarf.o              \
        \
        -lasmjit                    \
        -ltvision                   \
        -ldwarf64                   \
        -lz                         \
        -lintl                      \
        -lboost_program_options-mt  \
        -static-libgcc -static-libstdc++ 2>&1 ); run_check $? "${cmd}"

    if [[ -z "${DLG}" ]]; then
        echo "compile disassemler..."
    else
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[27]}\" \
        --gauge \"${!errloc[28]}\" 10 79 78"
        eval "$dlg"
    fi
    
    # ----------------------------------------
    # strip debug informations, shrink .exe
    # ----------------------------------------
    cmd=$(strip ${TMP}/diss.exe 2>&1); run_check $? "${cmd}"
}

# -----------------------------------------------------------------
# display help informations:
# -----------------------------------------------------------------
function help () {
    HELP="\nasmjit remote assembly test application.\n"
    HELP+="\nusage: # build.sh options file\n\n"
    HELP+="Options:\n"
    HELP+="--------\n"
    HELP+=" -h display this screen.\n"
    HELP+=" -l convert locale files only.\n"
    HELP+=" -a compile application.      file: test.pas\n"
    HELP+=" -i compile interpreter.      file: test.asm\n"
    HELP+=" -r run a x86::Compiler test.\n"
    HELP+=" -t run converter  test.       file: test2.asm"
    echo -e $HELP
    HELP=""
    exit 1
}
# -----------------------------------------------------------------
# switch back to developer source path ...
# -----------------------------------------------------------------
while getopts "lair:t:h" option; do
    case "${option}" in
        h)  help ;;
        a)  built_app="OPTARG";;
        i)  built_dis="OPTARG";;
        r)  built_run=${OPTARG};;
        t)  built_tst=${OPTARG};;
        l)  built_lng="OPTARG";;
        \?) echo "usage: build.sh [[-a], [-i], [-d]] file.src"
            echo "Expected -a, -r, -t or -d, or -l"
            echo "use -h for help"
            exit 1;;
    esac
done
# ----------------------------------------
# create locale file only.
# ----------------------------------------
if [[ -n "${built_lng}" ]]; then
    echo "create locale files ..."
    run_build_locales_helper ${build_locale}
    
    rm -rf ${SRC}/po/*.po
    rm -rf ${SRC}/po/*.pot
    rm -rf ${SRC}/po/*.mo
    
    if [[ -z "${DLG}" ]]; then
        echo "ok. =]"
    fi
    exit 1
fi
# ----------------------------------------
# compile application ...
# ----------------------------------------
if [[ -n "${built_app}" ]]; then
    cd ${TMP}
    run_build_prepare

    run_build_doc_xml deu  20
    run_build_doc_xml enu  22
    
    run_build_asmjit       26

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

    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[25]}\" \
        --msgbox \"${!errloc[26]}\" 10 79"
        eval "$dlg"
    fi
    cd ${SRC}
    clear
    exit 1
fi
# ----------------------------------------
# revert: disassembler ...
# ----------------------------------------
if [[ -n "${built_dis}" ]]; then
    cd ${TMP}
    run_build_prepare
    if [[ -z "${DLG}" ]]; then
        echo "compile disassemler..."
    else
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[29]}\" \
        --gauge \"${!errloc[30]}\" 10 79 70"
        eval "$dlg"
    fi
    run_build_locales 30
    
    # TODO - remove !!!
    cmd=$(${GXX} ${FLAGS} -o${TMP}/tvdemo2.o  -c ${SRC}/tvdemo2.cpp   2>&1 ); run_check $? "${cmd}"
    run_build_application

    # ----------------------------------------
    # display "done" message ...
    # ----------------------------------------
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[25]}\" \
        --msgbox \"${!errloc[26]}\" 10 79"
        eval "$dlg"
        clear
    fi
    cd ${SRC}
    exit 1

    # ----------------------------------------
    # buils parser script files ...
    # ----------------------------------------
    ${BISON} -d           \
        -Wno-conflicts-rr \
        -Wno-conflicts-sr \
        -Wno-other        \
        -o${TMP}/AssemblerParser.cc  ${SRC}/assembler.y
    ${FLEX}  -i -o${TMP}/AssemblerScanner.cc ${SRC}/assembler.lex
    
    if [[ -z "${DLG}" ]]; then
        echo "compile parser objects..."
    else
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[19]}\" \
        --gauge \"${!errloc[20]}\" 10 79 70"
        eval "$dlg"
    fi
    # ----------------------------------------
    # build parser object files ...
    # ----------------------------------------
    cmd=$(${GXX} ${FLAGS} -DHAVE_PARSER_ASM -UYY_USE_CLASS -o${TMP}/Interpreter.o      -c ${SRC}/Interpreter.cc      2>&1 ); run_check $? "${cmd}"
    cmd=$(${GXX} ${FLAGS} -DHAVE_PARSER_ASM -UYY_USE_CLASS -o${TMP}/AssemblerParser.o  -c ${TMP}/AssemblerParser.cc  2>&1 ); run_check $? "${cmd}"
    cmd=$(${GXX} ${FLAGS} -DHAVE_PARSER_ASM -UYY_USE_CLASS -o${TMP}/AssemblerScanner.o -c ${TMP}/AssemblerScanner.cc 2>&1 ); run_check $? "${cmd}"
    
    # ----------------------------------------
    # build turbo vision stuff ...
    # ----------------------------------------
    #cd ${SRC}/tv
    #${GXX} ${FLAGS} -c *.cpp
    #ar rcx libtvision.a *.o
    #mv libtvision.a ${TMP}
    #cd ${TMP}
    
    cmd=$(${GXX} ${FLAGS} -o${TMP}/tvdemo1.o  -c ${SRC}/tvdemo1.cpp   2>&1 ); run_check $? "${cmd}"
    cmd=$(${GXX} ${FLAGS} -o${TMP}/tvdemo2.o  -c ${SRC}/tvdemo2.cpp   2>&1 ); run_check $? "${cmd}"
    cmd=$(${GXX} ${FLAGS} -o${TMP}/tvdemo3.o  -c ${SRC}/tvdemo3.cpp   2>&1 ); run_check $? "${cmd}"
    
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/puzzle.o   -c ${SRC}/puzzle.cpp    2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/calendar.o -c ${SRC}/calendar.cpp  2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/calc.o     -c ${SRC}/calc.cpp      2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/backgrnd.o -c ${SRC}/backgrnd.cpp  2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/ascii.o    -c ${SRC}/ascii.cpp     2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/evntview.o -c ${SRC}/evntview.cpp  2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/fileview.o -c ${SRC}/fileview.cpp  2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/gadgets.o  -c ${SRC}/gadgets.cpp   2>&1 ); run_check $? "${cmd}"
    #cmd=$(${GXX} ${FLAGS} -o${TMP}/mousedlg.o -c ${SRC}/mousedlg.cpp  2>&1 ); run_check $? "${cmd}"

    # ----------------------------------------
    # link diss.exe application ...
    # ----------------------------------------
    run_build_application

    # ----------------------------------------
    # display "done" message ...
    # ----------------------------------------
    if [[ -n "${DLG}" ]]; then
        printf '\033[8;%d;%dt' $rows $cols
        dlg="(exit 1) | $dlgs --title \"${!errloc[25]}\" \
        --msgbox \"${!errloc[26]}\" 10 79"
        eval "$dlg"
        clear
    fi

    cd ${SRC}
    exit 1
fi
# ----------------------------------------
# dont compile, only interpret ...
# ----------------------------------------
if [[ -n "${built_tst}" ]]; then
    cd ${TMP}
    echo "running test..."
    LD_LIBRARY_PATH=./asmjit;./diss.exe ${built_tst} 2&> ${built_tst%.asm}.cc
    run_check $? "diss.exe"
    
    echo "compile new data file..."
    ${GXX} ${FLAGS} -I.. -o ${TMP}/${built_tst%.asm}.exe \
        ${TMP}/${built_tst%.asm}.cc \
    -L  ${TMP}/asmjit -lasmjit -lintl
    run_check $? "${built_tst%.asm}.exe"
    
    strip ${built_tst%.asm}.exe
    ${TMP}/${built_tst%.asm}.exe ${TMP}/${built_tst%.asm}.out
    
    cd ${SRC}
    exit 1
fi

# ----------------------------------------
# when all is done, then start a test ...
# ----------------------------------------
if [[ -n "${built_run}" ]]; then
    cd ${TMP}

    echo "create assembly file..."
    echo "${built_run%.*}.pas"
    cp ./asmjit/asmjit.dll ./asmjit.dll
    eval "LD_LIBRARY_PATH=./asmjit;./pc.exe ${built_run%.*}.pas"
    run_check $? "pc.exe translate ${built_run}"
    
    echo "convert assembly file ..."
    cp ${built_run%.*}.asm ${built_run%.*}_nasm.asm
    eval "LD_LIBRARY_PATH=./asmjit;./diss.exe ${built_run%.*}_nasm.asm"
 
    echo "compile ${built_run%.*}_nasm.asm ..."
    run_build_nasm_source ${built_run%.*}_nasm
    run_check $? "nasm.exe convert ${built_run%.*}_nasm.asm"
    
    cd ${SRC}
    exit 1
fi

# ----------------------------------------
# we should never reach this, if all done:
# ----------------------------------------
help
