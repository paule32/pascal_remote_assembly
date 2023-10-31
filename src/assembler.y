%{
// -----------------------------------------------------------------
// File:   Assembler.yy
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

# include <iostream>
# include <sstream>
# include <cstring>
# include <string>
# include <algorithm>
# include <vector>

// -----------------------------------------------------------------
// YY parser forwarder to C library ...
// -----------------------------------------------------------------
extern "C" {
    int  yylex   (void );
    int  yyparse (void );
    void yyerror (const char*);
};

// -----------------------------------------------------------------
// std c++ container:
// -----------------------------------------------------------------
std::vector< std::string > section_vector;      // section
std::stringstream          output_stream;       // code stream

%}

%union {
    int int_val;
    char* string_val;
}

%token UNKNOWN
%token TOK_ID TOK_CONSTANT
%token TOK_DOT TOK_SECTION TOK_SECT_ID
%token TOK_CALL

%token TOK_YYEOF 0

%token <string_val> TOK_LABEL
%type  <string_val> _tok_id _tok_sect_id

%start program

%%

program
    :   /* empty */
    |   program_top program
    ;

program_top
    : TOK_SECTION _tok_sect_id {
        std::stringstream ss;
        std::string str = $2;
        std::transform(str.begin(), str.end(), str.begin(),
        [](char ch)
        {
            if( std::ispunct(ch) )
            return '\0';
            return  ch ;
        });
        str = str.substr(1,str.size()-1);
        std::vector< std::string >::iterator it = std::find(
            section_vector.begin(),
            section_vector.end  (), str);
        if (section_vector.end  () == it) {
            ss << "\tSection* section_" << str << ";"
               << std::endl
               << "\terr = code.newSection(&section_" << str
               << ", \""    << str << "\""
               << ", SIZE_MAX, SectionFlags::kNone, 8);"
               << std::endl << "\tif (err)"
               << std::endl
               << "\tyyerror(gettext(\""
               << "failed to create section: " << "sect_" << str
               << "\"));"
               << std::endl
               << std::endl;
        }   else {
            ss << "a.section(" << str << ");" << std::endl;
        }
        output_stream << ss.str();
    }
    | TOK_LABEL {
        std::stringstream ss;
        std::string str = $1;
        
        if(str.empty() < 1)
           str.pop_back();
           
        ss << "\tLabel lbl_"        << str << " = a.newNamedLabel("
           << "\""                  << str << "\", SIZE_MAX);"  << std::endl
           << "\terr = a.bind(lbl_" << str << ");"              << std::endl
           << "\tif (err)"                                      << std::endl
           << "\tyyerror(gettext(\"failed bind label\"));"      << std::endl;

        output_stream << ss.str();
    }
    | TOK_CALL _tok_id {
    printf("1212121212\n");
        std::cout << "---------------------" << std::endl;
    }
    ;

_tok_id      : TOK_ID      { $$ = yylval.string_val; } ;
_tok_sect_id : TOK_SECT_ID { $$ = yylval.string_val; } ;

%%

