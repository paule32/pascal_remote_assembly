/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PASCAL_TAB_HH_INCLUDED
# define YY_YY_PASCAL_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    TOK_YYEOF = 0,                 /* TOK_YYEOF  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_PROGRAM = 258,             /* TOK_PROGRAM  */
    TOK_IDENTIFIER = 259,          /* TOK_IDENTIFIER  */
    TOK_CONSTANT = 260,            /* TOK_CONSTANT  */
    TOK_BEGIN = 261,               /* TOK_BEGIN  */
    TOK_END = 262,                 /* TOK_END  */
    TOK_PROCEDURE = 263,           /* TOK_PROCEDURE  */
    TOK_FUNCTION = 264,            /* TOK_FUNCTION  */
    TOK_VAR = 265,                 /* TOK_VAR  */
    TOK_CONST = 266,               /* TOK_CONST  */
    TOK_STRINGEXPR = 267,          /* TOK_STRINGEXPR  */
    TOK_STRING = 268,              /* TOK_STRING  */
    TOK_INTEGER = 269,             /* TOK_INTEGER  */
    TOK_BYTE = 270,                /* TOK_BYTE  */
    TOK_CHAR = 271,                /* TOK_CHAR  */
    SYM_DOT = 272,                 /* SYM_DOT  */
    SYM_SEMICOLON = 273,           /* SYM_SEMICOLON  */
    SYM_COLON = 274,               /* SYM_COLON  */
    SYM_COMMA = 275,               /* SYM_COMMA  */
    SYM_EQUAL = 276                /* SYM_EQUAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "pascal.yy"

    int int_val;
    char* string_val;

#line 90 "pascal.tab.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PASCAL_TAB_HH_INCLUDED  */
