// -----------------------------------------------------------------
// File:   Parser.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
#ifndef PARSER__H_
#define PARSER__H_

#pragma once

// -----------------------------------------------------------------
// we support only GNU-C/C++ compilers ...
// -----------------------------------------------------------------
#if !defined(__GNUC__)
#error only GNU-C/C++ Compiler supported.
#endif

// -----------------------------------------------------------------
// the minimum requirements is a GNU C++ compiler ...
// -----------------------------------------------------------------
#if !defined(__cplusplus)
#error C++ Compiler required.
#endif

// -----------------------------------------------------------------
// a msys2 development environment is needed for this Application.
// MSYS2 is a set of tool chain for Microsot Windows OS.
// -----------------------------------------------------------------
#if !defined(__MINGW32__) || !defined(__MINGW64__)
#error This Applications was created under Microsoft-Windows...
#else

// -----------------------------------------------------------------
// standard header stuff ...
// -----------------------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <libintl.h>
# include <locale.h>
# include <sys/stat.h>

// -----------------------------------------------------------------
// c++ header prototype's/signature's:
// -----------------------------------------------------------------
# include <iostream>        // std c++ signatures
# include <string>
# include <fstream>
# include <cstdio>
# include <cstdlib>
# include <vector>
# include <unordered_map>
# include <map>
# include <any>
# include <memory>
# include <functional>
# include <locale>
# include <iomanip>
# include <exception>       // exception handler's

// -----------------------------------------------------------------
// global per file used variables/declarations:
// -----------------------------------------------------------------
# include "global.h"
# include "Exception.h"

# include "PascalParser.h"
# include "PascalScanner.h"

# include "x86.h"

// -----------------------------------------------------------------
// platform speciefic stuff ...
// -----------------------------------------------------------------
#if defined(_WIN32) || defined(_WIN64)
extern "C" {
# include <windows.h>
extern HINSTANCE win32_hInstance;
};
#else
extern uint32_t  win32_hInstance;
#endif

// -----------------------------------------------------------------
// code helper, and shortner ...
// -----------------------------------------------------------------
# define _(String) gettext(String)

// -----------------------------------------------------------------
// used global namespaces ...
// -----------------------------------------------------------------
using namespace asmjit;

// -----------------------------------------------------------------
// parser class for our Pascal parser ...
// -----------------------------------------------------------------
class Parser: public PascalParser
{
private:
    PascalScanner scanner;
public:
    // -------------------------------------------------------------
    // ctor: initialize, and allocate memory; depend on a file name.
    // -------------------------------------------------------------
    Parser( char *filename );
    Parser();

    virtual void yyerror(char * msg);
    virtual int yylex();
    
    std::ifstream * parser_file;
    
    // -------------------------------------------------------------
    // dtor: try to clean, and free allocated memory.
    // -------------------------------------------------------------
    ~Parser();
    
    void initialize();
    void finalize();

    // -------------------------------------------------------------
    // remote assembly ...
    // -------------------------------------------------------------
    class ASM_Code {
    public:
        class MyErrorHandler : public ErrorHandler {
        public:
            void handleError(Error err, const char*, BaseEmitter*) override;
            //MyErrorHandler();
        };

        JitRuntime             rt;  // Runtime specialized for JIT code excution
        Environment           env;
        CpuFeatures      features;

        Section        * code_sec;  // code section
        Section        * data_sec;  // data section
        
        CodeHolder     *     code;  // Holds the code and relocation information
        StringLogger   *   logger;  // Logger should always survice CodeHolder
        FILE           *  logFile;  // todo: assembly output
    
        FormatFlags   formatFlags;
        x86::Compiler  *       cc;
        Error                 err;
        
        MyErrorHandler * myErrorHandler;

        std::stringstream FuncTableStream;  // experimental
        
        std::map< std::string, FuncNode* > FuncNodeMap;
        
        // -----------------------------------------------
        // this map is used to hold the source code small-
        // there, we hold a list of asmjit callables...
        // -----------------------------------------------
        std::unordered_map< std::string,
        std::unordered_map< std::string, std::any > > FuncArgs;
        
        void mapArgumentsList( );
        void mapArguments    (
             std::unordered_map< std::string,
             std::unordered_map< std::string, std::any > > &p );

    public:
        ASM_Code();
       ~ASM_Code();

        // -------------------------------------------------------------
        // Windows 32-Bit API ...
        // -------------------------------------------------------------
        void init_win32api();

        void code_end   ();
        void code_exec  ();
        void code_write ();
        
        bool user32_MessageBox();
    };
    
    class ASM_Code * asm_code = nullptr;
};
// -----------------------------------------------------------------
extern Parser * parser;
extern char   * locale_utf8;

extern void parser_cleanup();

#endif   // __MINGW32__ || __MINGW64__
#endif   // PARSER__H_
