%{
// -----------------------------------------------------------------
// File:   dBase.y
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <libintl.h>
# include <locale.h>

# undef __FLAT__
# include <strings.h>

# include <iostream>
# include <sstream>
# include <cstring>
# include <string>
# include <algorithm>
# include <vector>
# include <map>

// -----------------------------------------------------------------
// YY parser forwarder to C library ...
// -----------------------------------------------------------------
extern "C" {
    int  DBASElex   (void );
    int  DBASEparse (void );
    void DBASEerror (const char*);
};

# define PREFIX "DB_"
# define YYSTYPE_PREFIX "DB_"

%}

%union {
    struct {
        int int_val;
        char* string_val;
    }   db_token_struct;
}

%token DB_TOK_HEX DB_TOK_DEC

%token DB_TOK_STRING
%token DB_TOK_CLEAR

%start program

%%

program
    :   /* empty */
    |   program_top program
    ;

program_top
    :   DB_TOK_CLEAR
    ;
%%
