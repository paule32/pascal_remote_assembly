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
    
    FILE * yyin;
    FILE * yyout;
    
    // dtor
    ~Parser();
};
// -----------------------------------------------------------------
extern Parser *parser;

