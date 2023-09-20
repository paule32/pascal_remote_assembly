// -----------------------------------------------------------------
// File:   Parser.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <iostream>
# include <sstream>
# include <istream>
# include <fstream>
# include "Parser.h"
using namespace std;

std::istream * lexer_input;

// -----------------------------------------------------------------
// default ctor
// -----------------------------------------------------------------
Parser::Parser()
{
}

Parser::Parser( char *filename )
{
    // --------------------------------------------------------
    // try to open input file.
    // --------------------------------------------------------
    parser_file = new std::ifstream(filename);
    std::stringstream buffer;
    buffer << parser_file->rdbuf();
    lexer_input = new std::istringstream(buffer.str());
}

// -----------------------------------------------------------------
// standard ctor
// -----------------------------------------------------------------
Parser::~Parser()
{
    parser_file->close();
    delete parser_file;
}

// -----------------------------------------------------------------
// handle parser/scanning error's ...
// -----------------------------------------------------------------
void Parser::yyerror(char * msg)
{
    cerr << yylloc.first_line
         << ":"    << yylloc.first_column
         << ": "  << msg
         << " : <" << yylloc.text
         << ">"    << endl;
}

// -----------------------------------------------------------------
// get token from scanner text:
// -----------------------------------------------------------------
int Parser::yylex()
{
    yylloc.first_line   = scanner.line;
    yylloc.first_column = scanner.column;

    int token = scanner.yylex(&yylval, &yylloc);

    yylloc.last_line    = scanner.line;
    yylloc.last_column  = scanner.column;

    yylloc.text = (char *)scanner.yytext;

    return token;
}
