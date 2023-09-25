// -----------------------------------------------------------------
// File:   Parser.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
#pragma once

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
# include <locale>
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
# include <windows.h>

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
    JitRuntime        rt;  // Runtime specialized for JIT code excution
    Environment      env;
    CpuFeatures features;
    
    CodeHolder      code;  // Holds the code and relocation information
    StringLogger  logger;  // Logger should always survice CodeHolder
    
    FormatFlags formatFlags;
    x86::Compiler     cc;
    Error            err;
};
// -----------------------------------------------------------------
extern Parser * parser;
extern char   * locale_utf8;

extern void parser_cleanup();
