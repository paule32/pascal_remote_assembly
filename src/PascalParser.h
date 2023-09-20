#ifndef YY_PascalParser_h_included
#define YY_PascalParser_h_included

#line 1 "E:\\msys64\\mingw64\\bin\\bison.h"
/* before anything */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else
#endif
#include <stdio.h>

/* #line 14 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 21 "PascalParser.h"
#define YY_PascalParser_LSP_NEEDED 
#define YY_PascalParser_ERROR_BODY  = 0
#define YY_PascalParser_LEX_BODY  = 0
#line 14 "pascal.yy"

# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <iostream>

#line 21 "pascal.yy"
typedef union {
    int int_val;
    char* string_val;
} yy_PascalParser_stype;
#define YY_PascalParser_STYPE yy_PascalParser_stype

#line 14 "E:\\msys64\\mingw64\\bin\\bison.h"
 /* %{ and %header{ and %union, during decl */
#ifndef YY_PascalParser_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_PascalParser_COMPATIBILITY 1
#else
#define  YY_PascalParser_COMPATIBILITY 0
#endif
#endif

#if YY_PascalParser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_PascalParser_LTYPE
#define YY_PascalParser_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_PascalParser_STYPE 
#define YY_PascalParser_STYPE YYSTYPE
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
/* use %define STYPE */
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_PascalParser_DEBUG
#define  YY_PascalParser_DEBUG YYDEBUG
/* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
/* use %define DEBUG */
#endif
#endif
#ifdef YY_PascalParser_STYPE
#ifndef yystype
#define yystype YY_PascalParser_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_PascalParser_USE_GOTO
#define YY_PascalParser_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_PascalParser_USE_GOTO
#define YY_PascalParser_USE_GOTO 0
#endif

#ifndef YY_PascalParser_PURE

/* #line 63 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 91 "PascalParser.h"

#line 63 "E:\\msys64\\mingw64\\bin\\bison.h"
/* YY_PascalParser_PURE */
#endif

/* #line 65 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 98 "PascalParser.h"

#line 65 "E:\\msys64\\mingw64\\bin\\bison.h"
/* prefix */
#ifndef YY_PascalParser_DEBUG

/* #line 67 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 105 "PascalParser.h"

#line 67 "E:\\msys64\\mingw64\\bin\\bison.h"
/* YY_PascalParser_DEBUG */
#endif
#ifndef YY_PascalParser_LSP_NEEDED

/* #line 70 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 113 "PascalParser.h"

#line 70 "E:\\msys64\\mingw64\\bin\\bison.h"
 /* YY_PascalParser_LSP_NEEDED*/
#endif
/* DEFAULT LTYPE*/
#ifdef YY_PascalParser_LSP_NEEDED
#ifndef YY_PascalParser_LTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YY_PascalParser_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
#ifndef YY_PascalParser_STYPE
#define YY_PascalParser_STYPE int
#endif
/* DEFAULT MISCELANEOUS */
#ifndef YY_PascalParser_PARSE
#define YY_PascalParser_PARSE yyparse
#endif
#ifndef YY_PascalParser_LEX
#define YY_PascalParser_LEX yylex
#endif
#ifndef YY_PascalParser_LVAL
#define YY_PascalParser_LVAL yylval
#endif
#ifndef YY_PascalParser_LLOC
#define YY_PascalParser_LLOC yylloc
#endif
#ifndef YY_PascalParser_CHAR
#define YY_PascalParser_CHAR yychar
#endif
#ifndef YY_PascalParser_NERRS
#define YY_PascalParser_NERRS yynerrs
#endif
#ifndef YY_PascalParser_DEBUG_FLAG
#define YY_PascalParser_DEBUG_FLAG yydebug
#endif
#ifndef YY_PascalParser_ERROR
#define YY_PascalParser_ERROR yyerror
#endif

#ifndef YY_PascalParser_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_PascalParser_PARSE_PARAM
#ifndef YY_PascalParser_PARSE_PARAM_DEF
#define YY_PascalParser_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_PascalParser_PARSE_PARAM
#define YY_PascalParser_PARSE_PARAM void
#endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

#ifndef YY_PascalParser_PURE
extern YY_PascalParser_STYPE YY_PascalParser_LVAL;
#endif


/* #line 143 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 191 "PascalParser.h"
#define	UNKNOWN	258
#define	TOK_PROGRAM	259
#define	TOK_IDENTIFIER	260
#define	TOK_CONSTANT	261
#define	TOK_BEGIN	262
#define	TOK_END	263
#define	TOK_PROCEDURE	264
#define	TOK_FUNCTION	265
#define	TOK_VAR	266
#define	TOK_CONST	267
#define	TOK_STRINGEXPR	268
#define	TOK_STRING	269
#define	TOK_INTEGER	270
#define	TOK_BYTE	271
#define	TOK_CHAR	272
#define	SYM_DOT	273
#define	SYM_SEMICOLON	274
#define	SYM_COLON	275
#define	SYM_COMMA	276
#define	SYM_EQUAL	277
#define	TOK_YYEOF	278


#line 143 "E:\\msys64\\mingw64\\bin\\bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
#ifndef YY_PascalParser_CLASS
#define YY_PascalParser_CLASS PascalParser
#endif

#ifndef YY_PascalParser_INHERIT
#define YY_PascalParser_INHERIT
#endif
#ifndef YY_PascalParser_MEMBERS
#define YY_PascalParser_MEMBERS 
#endif
#ifndef YY_PascalParser_LEX_BODY
#define YY_PascalParser_LEX_BODY  
#endif
#ifndef YY_PascalParser_ERROR_BODY
#define YY_PascalParser_ERROR_BODY  
#endif
#ifndef YY_PascalParser_CONSTRUCTOR_PARAM
#define YY_PascalParser_CONSTRUCTOR_PARAM
#endif
/* choose between enum and const */
#ifndef YY_PascalParser_USE_CONST_TOKEN
#define YY_PascalParser_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */ 
#endif
#if YY_PascalParser_USE_CONST_TOKEN != 0
#ifndef YY_PascalParser_ENUM_TOKEN
#define YY_PascalParser_ENUM_TOKEN yy_PascalParser_enum_token
#endif
#endif

class YY_PascalParser_CLASS YY_PascalParser_INHERIT
{
public: 
#if YY_PascalParser_USE_CONST_TOKEN != 0
/* static const int token ... */

/* #line 182 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 257 "PascalParser.h"
static const int UNKNOWN;
static const int TOK_PROGRAM;
static const int TOK_IDENTIFIER;
static const int TOK_CONSTANT;
static const int TOK_BEGIN;
static const int TOK_END;
static const int TOK_PROCEDURE;
static const int TOK_FUNCTION;
static const int TOK_VAR;
static const int TOK_CONST;
static const int TOK_STRINGEXPR;
static const int TOK_STRING;
static const int TOK_INTEGER;
static const int TOK_BYTE;
static const int TOK_CHAR;
static const int SYM_DOT;
static const int SYM_SEMICOLON;
static const int SYM_COLON;
static const int SYM_COMMA;
static const int SYM_EQUAL;
static const int TOK_YYEOF;


#line 182 "E:\\msys64\\mingw64\\bin\\bison.h"
 /* decl const */
#else
enum YY_PascalParser_ENUM_TOKEN { YY_PascalParser_NULL_TOKEN=0

/* #line 185 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 287 "PascalParser.h"
	,UNKNOWN=258
	,TOK_PROGRAM=259
	,TOK_IDENTIFIER=260
	,TOK_CONSTANT=261
	,TOK_BEGIN=262
	,TOK_END=263
	,TOK_PROCEDURE=264
	,TOK_FUNCTION=265
	,TOK_VAR=266
	,TOK_CONST=267
	,TOK_STRINGEXPR=268
	,TOK_STRING=269
	,TOK_INTEGER=270
	,TOK_BYTE=271
	,TOK_CHAR=272
	,SYM_DOT=273
	,SYM_SEMICOLON=274
	,SYM_COLON=275
	,SYM_COMMA=276
	,SYM_EQUAL=277
	,TOK_YYEOF=278


#line 185 "E:\\msys64\\mingw64\\bin\\bison.h"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_PascalParser_PARSE(YY_PascalParser_PARSE_PARAM);
 virtual void YY_PascalParser_ERROR(char *msg) YY_PascalParser_ERROR_BODY;
#ifdef YY_PascalParser_PURE
#ifdef YY_PascalParser_LSP_NEEDED
 virtual int  YY_PascalParser_LEX(YY_PascalParser_STYPE *YY_PascalParser_LVAL,YY_PascalParser_LTYPE *YY_PascalParser_LLOC) YY_PascalParser_LEX_BODY;
#else
 virtual int  YY_PascalParser_LEX(YY_PascalParser_STYPE *YY_PascalParser_LVAL) YY_PascalParser_LEX_BODY;
#endif
#else
 virtual int YY_PascalParser_LEX() YY_PascalParser_LEX_BODY;
 YY_PascalParser_STYPE YY_PascalParser_LVAL;
#ifdef YY_PascalParser_LSP_NEEDED
 YY_PascalParser_LTYPE YY_PascalParser_LLOC;
#endif
 int YY_PascalParser_NERRS;
 int YY_PascalParser_CHAR;
#endif
#if YY_PascalParser_DEBUG != 0
public:
 int YY_PascalParser_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
#endif
public:
 YY_PascalParser_CLASS(YY_PascalParser_CONSTRUCTOR_PARAM);
public:
 YY_PascalParser_MEMBERS 
};
/* other declare folow */
#endif


#if YY_PascalParser_COMPATIBILITY != 0
/* backward compatibility */
#ifndef YYSTYPE
#define YYSTYPE YY_PascalParser_STYPE
#endif

#ifndef YYLTYPE
#define YYLTYPE YY_PascalParser_LTYPE
#endif
#ifndef YYDEBUG
#ifdef YY_PascalParser_DEBUG 
#define YYDEBUG YY_PascalParser_DEBUG
#endif
#endif

#endif
/* END */

/* #line 236 "E:\\msys64\\mingw64\\bin\\bison.h" */
#line 365 "PascalParser.h"
#endif
