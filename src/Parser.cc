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
# include "AnsiColor.h"

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
    if (parser_file->is_open())
    {
        std::stringstream buffer;
        buffer << parser_file->rdbuf();
        lexer_input = new std::istringstream(buffer.str());
        
        initialize();
        
        locale_utf8 = new char[4];
    }
    else {
        if (parser_file->fail())
        throw EPascalException_FileNotOpen (_("parser file could not be open."));
        throw EPascalException_FileNotFound(_("parser file dont exists."));
    }
}

// -----------------------------------------------------------------
// standard ctor, remove temporary files, and clean-up memory ...
// -----------------------------------------------------------------
Parser::~Parser()
{
    parser_file->close();
    delete parser_file;
    
    finalize();
}

// -----------------------------------------------------------------
// clean up global storage ...
// -----------------------------------------------------------------
void parser_cleanup()
{
    std::cout << "please wait..." << std::endl;

    if (!strcmp(locale_utf8,"de")) {
        std::remove("locales/de_DE/LC_MESSAGES/de_DE_utf8.mo");
    }   else
    if (!strcmp(locale_utf8,"en")) {
        std::remove("locales/en_US/LC_MESSAGES/en_US_utf8.mo");
    }

    if (nullptr != parser) delete parser;
    if (nullptr != ansi  ) delete ansi;
    
    sleep(1);
    std::cout << "\033[A\033[2KT\r              " << std::endl;
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

void yyerror(char *err) { parser->yyerror(err); }
