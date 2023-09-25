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

// -----------------------------------------------------------------
// c++ header prototype's/signature's:
// -----------------------------------------------------------------
# include <iostream>
# include <fstream>
# include <exception>

// -----------------------------------------------------------------
// global per file used variables/declarations:
// -----------------------------------------------------------------
# include "global.h"
# include "Exception.h"

# include "PascalParser.h"
# include "PascalScanner.h"

# include "x86.h"

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
    // ctor
    Parser( char *filename );
    Parser();

    virtual void yyerror(char * msg);
    virtual int yylex();
    
    std::ifstream * parser_file;
    
    // dtor
    ~Parser();
    
    void initialize();
    void finalize();
    
    // -------------------------------------------------------------
    // remote assembly ...
    // -------------------------------------------------------------
    JitRuntime        rt;  // Runtime specialized for JIT code excution
    Environment      env;
    CpuFeatures Features;
    
    CodeHolder      code;  // Holds the code and relocation information
    StringLogger  logger;  // Logger should always survice CodeHolder
    
    FormatFlags formatFlags;
    x86::Compiler     cc;
    Error            err;
};
// -----------------------------------------------------------------
extern Parser *parser;

