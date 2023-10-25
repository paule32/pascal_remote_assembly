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
// this function checks, if the application is run in console mode.
// -----------------------------------------------------------------
static bool win32_console()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    if (!GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE),
    &csbi)) {
        stringstream ss;
        ss << "GetConsoleScreenBufferInfo " << _("failed: ")
           << GetLastError();
        throw std::string( ss.str() );
        return true;
    }
    
    #if 0
    DWORD procId;
    DWORD count = GetConsoleProcessList(&procId, 1);
    if (count != 1)
    throw std::string("console mode");
    #endif
    
    // --------------------------------------------------------
    // if cursor position is (0,0) then we were launched in
    // a separate console ...
    // --------------------------------------------------------
    if ((!csbi.dwCursorPosition.X) && (!csbi.dwCursorPosition.Y)) {
        // console
        return true;
    }
    else {
        if (!GetConsoleTitle(NULL, 0) && GetLastError() == ERROR_SUCCESS) {
            // console
            return true;
        }
        else {
            // GUI
            return false;
        }
    }
    return false;
}

// -----------------------------------------------------------------
// default ctor
// -----------------------------------------------------------------
Parser::Parser()
{
    //if (win32_console())
    //std::cout << "console mode" << std::endl;
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
        asm_code    = new Parser::ASM_Code();

        initialize();
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
    finalize();
}

// -----------------------------------------------------------------
// clean up global storage ...
// -----------------------------------------------------------------
void parser_cleanup()
{
    std::cout << _("please wait...") << std::endl;

    // -------------------------------------------------------------
    // at terminating application, delete de-packed .mo file.
    // this make space for other usage, with other application's ...
    // TODO: check directory, and/or file.
    // -------------------------------------------------------------
    if (!strcmp(locale_utf8,"de")) {    // german
        std::remove("locales/de_DE/LC_MESSAGES/de_DE_utf8.mo");
    }   else
    if (!strcmp(locale_utf8,"en")) {    // english
        std::remove("locales/en_US/LC_MESSAGES/en_US_utf8.mo");
    }

    // -------------------------------------------------------------
    // now, try to free allocated memory ...
    // -------------------------------------------------------------
    if (nullptr != parser) delete parser;
    if (nullptr != ansi  ) delete ansi;
    
    // -------------------------------------------------------------
    // delete last line \r -> "please wait..." :
    // -------------------------------------------------------------
    usleep(500);
    //std::cout << "\033[A\033[2KT\r              " << std::endl;
}

// -----------------------------------------------------------------
// adjust the arguments to the "setArgT" member of asmjit ...
// -----------------------------------------------------------------
void
Parser::ASM_Code::mapArguments(
    std::unordered_map< std::string,
    std::unordered_map< std::string, std::any > > &p) {
    int i = 0;
    for (auto it1 = p.begin(); it1 != p.end(); ++it1) {
        std::cout << std::endl;
        std::cout << it1->first << " = " <<
        std::endl ;
        for (auto &[key, val] : it1->second) {
            std::cout << "   Arg: " << ++i << " = ";

            if (val.type() == typeid( int         )) std::cout << "int          : " << std::any_cast< int         >(val); else
            if (val.type() == typeid( double      )) std::cout << "double       : " << std::any_cast< double      >(val); else
            if (val.type() == typeid( float       )) std::cout << "float        : " << std::any_cast< float       >(val); else
            if (val.type() == typeid( char        )) std::cout << "char         : " << std::any_cast< char        >(val); else
            if (val.type() == typeid( char const* )) std::cout << "const char * : " << std::any_cast< char const* >(val); else
            if (val.type() == typeid( std::string )) std::cout << "std::string  : " << std::any_cast< std::string >(val); else
            if (val.type() == typeid( HWND        )) std::cout << "HWND         : " << std::any_cast< HWND        >(val); else
            if (val.type() == typeid( LPCTSTR     )) std::cout << "LPCTSTR      : " << std::any_cast< LPCTSTR     >(val); else
            if (val.type() == typeid( UINT        )) std::cout << "UINT         : " << std::any_cast< UINT        >(val); else
            if (val.type() == typeid( uint32_t    )) std::cout << "uint32_t     : " << std::any_cast< uint32_t    >(val);
            
            std::cout << std::endl;
        }
    }
}
// -----------------------------------------------------------------
// create the internal function map argument list ...
// -----------------------------------------------------------------
void Parser::ASM_Code::mapArgumentsList()
{
    FuncArgs = {
    {
        "MessageBoxA",
        {
            { "hwnd"     , "HWND"    },
            { "lpText"   , "LPCTSTR" },
            { "lpCaption", "LPCTSTR" },
            { "mbType"   , "UINT"    },
        }
    },
    {
        "ExitProcess",
        {
            { "code", "uint32_t" },
        }
    }
    };
    mapArguments(FuncArgs);
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
