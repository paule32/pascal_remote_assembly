// -----------------------------------------------------------------
// File:   Assembler.yy
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
%name AssemblerParser

%define LSP_NEEDED
%define ERROR_BODY = 0
%define LEX_BODY = 0

%header{
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
%}

%union {
    int int_val;
    char* string_val;
}

%token UNKNOWN
%token TOK_IDENTIFIER TOK_CONSTANT
%token TOK_SECTIOM

%token TOK_YYEOF 0

%start program

%%
program
    :   /* empty */
    |   program_heading program
    ;

program_heading
    : TOK_SECTIOM
    ;
%%

