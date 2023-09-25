// -----------------------------------------------------------------
// File:   Pascal.yy
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
%name PascalParser

%define LSP_NEEDED
%define ERROR_BODY = 0
%define LEX_BODY = 0

%header{
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <iostream>
%}

%union {
    int int_val;
    char* string_val;
}

%token UNKNOWN
%token TOK_PROGRAM TOK_IDENTIFIER TOK_CONSTANT
%token TOK_BEGIN TOK_END
%token TOK_PROCEDURE TOK_FUNCTION
%token TOK_VAR TOK_CONST TOK_STRINGEXPR
%token TOK_STRING TOK_INTEGER TOK_BYTE TOK_CHAR

%token SYM_DOT SYM_SEMICOLON SYM_COLON SYM_COMMA SYM_EQUAL

%token TOK_YYEOF 0

%start program

%%
program
    :   /* empty */
    |   program_heading program
    ;

program_heading
    :   TOK_PROGRAM TOK_IDENTIFIER SYM_SEMICOLON block_start block_ending SYM_DOT
    ;

block_start
    :   block_start_proc_func TOK_BEGIN
    ;

block_start_proc_func
    :   /* empty */
    |   TOK_PROCEDURE TOK_IDENTIFIER SYM_SEMICOLON block_const_var block_start_proc_func TOK_BEGIN TOK_END SYM_SEMICOLON
    |   TOK_FUNCTION  TOK_IDENTIFIER SYM_SEMICOLON block_const_var block_start_proc_func TOK_BEGIN TOK_END SYM_SEMICOLON
    ;

block_const_var
    :   /* empty */
    |   TOK_CONST block_const_idents SYM_SEMICOLON block_const_var
    |   TOK_CONST TOK_IDENTIFIER     SYM_EQUAL TOK_STRINGEXPR SYM_COMMA     block_const_chain block_const_var
    |   TOK_VAR   block_var_idents   SYM_COLON block_var_type SYM_SEMICOLON block_var_chain   block_const_var
    |   TOK_VAR   TOK_IDENTIFIER     SYM_COLON block_var_type SYM_SEMICOLON block_var_chain   block_const_var
    ;
block_const_chain
    :   /* empty */
    |   block_const_idents SYM_SEMICOLON block_const_chain
    |   block_const_idents SYM_SEMICOLON
    ;
block_var_chain
    :   /* empty */
    |   block_var_idents SYM_COLON block_var_type SYM_SEMICOLON block_var_chain
    |   block_var_idents SYM_COLON block_var_type SYM_SEMICOLON
    ;
block_const_idents
    :   TOK_IDENTIFIER SYM_EQUAL TOK_STRINGEXPR
    |   block_const_idents SYM_COMMA block_const_idents
    ;
block_var_idents
    :   TOK_IDENTIFIER
    |   block_var_idents SYM_COMMA block_var_idents
    ;

block_var_type
    :   TOK_STRING
    |   TOK_INTEGER
    |   TOK_BYTE
    |   TOK_CHAR
    ;
    
block_ending
    :   TOK_END
    ;

%%

