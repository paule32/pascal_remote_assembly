#define YY_PascalParser_h_included

/*  A Bison++ parser, made from pascal.yy  */

 /* with Bison++ version bison++ Version 1.21-8, adapted from GNU bison by coetmeur@icdc.fr
  */


#line 1 "E:\\msys64\\mingw64\\bin\\bison.cc"
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* HEADER SECTION */
#if defined( _MSDOS ) || defined(MSDOS) || defined(__MSDOS__) 
#define __MSDOS_AND_ALIKE
#endif
#if defined(_WINDOWS) && defined(_MSC_VER)
#define __HAVE_NO_ALLOCA
#define __MSDOS_AND_ALIKE
#endif

#ifndef alloca
#if defined( __GNUC__)
#define alloca __builtin_alloca

#elif (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)  || defined (__sgi)
#include <alloca.h>

#elif defined (__MSDOS_AND_ALIKE)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif

#elif defined(_AIX)
#include <malloc.h>
#pragma alloca

#elif defined(__hpux)
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */

#endif /* not _AIX  not MSDOS, or __TURBOC__ or _AIX, not sparc.  */
#endif /* alloca not defined.  */
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
#ifndef __STDC__
#define const
#endif
#endif
#include <stdio.h>
#define YYBISON 1  

/* #line 73 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 85 "PascalParser.cc"
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

#line 73 "E:\\msys64\\mingw64\\bin\\bison.cc"
/* %{ and %header{ and %union, during decl */
#define YY_PascalParser_BISON 1
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
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_PascalParser_STYPE 
#define YY_PascalParser_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_PascalParser_DEBUG
#define  YY_PascalParser_DEBUG YYDEBUG
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

/* #line 117 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 150 "PascalParser.cc"

#line 117 "E:\\msys64\\mingw64\\bin\\bison.cc"
/*  YY_PascalParser_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 121 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 159 "PascalParser.cc"

#line 121 "E:\\msys64\\mingw64\\bin\\bison.cc"
/* prefix */
#ifndef YY_PascalParser_DEBUG

/* #line 123 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 166 "PascalParser.cc"

#line 123 "E:\\msys64\\mingw64\\bin\\bison.cc"
/* YY_PascalParser_DEBUG */
#endif


#ifndef YY_PascalParser_LSP_NEEDED

/* #line 128 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 176 "PascalParser.cc"

#line 128 "E:\\msys64\\mingw64\\bin\\bison.cc"
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
      /* We used to use `unsigned long' as YY_PascalParser_STYPE on MSDOS,
	 but it seems better to be consistent.
	 Most programs should declare their own type anyway.  */

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
#if YY_PascalParser_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_PascalParser_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_PascalParser_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_PascalParser_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_PascalParser_PURE
#ifndef YYPURE
#define YYPURE YY_PascalParser_PURE
#endif
#endif
#ifdef YY_PascalParser_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_PascalParser_DEBUG 
#endif
#endif
#ifndef YY_PascalParser_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_PascalParser_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_PascalParser_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_PascalParser_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */

/* #line 236 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 289 "PascalParser.cc"
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


#line 236 "E:\\msys64\\mingw64\\bin\\bison.cc"
 /* #defines tokens */
#else
/* CLASS */
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
#ifndef YY_PascalParser_CONSTRUCTOR_CODE
#define YY_PascalParser_CONSTRUCTOR_CODE
#endif
#ifndef YY_PascalParser_CONSTRUCTOR_INIT
#define YY_PascalParser_CONSTRUCTOR_INIT
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

/* #line 280 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 360 "PascalParser.cc"
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


#line 280 "E:\\msys64\\mingw64\\bin\\bison.cc"
 /* decl const */
#else
enum YY_PascalParser_ENUM_TOKEN { YY_PascalParser_NULL_TOKEN=0

/* #line 283 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 390 "PascalParser.cc"
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


#line 283 "E:\\msys64\\mingw64\\bin\\bison.cc"
 /* enum token */
     }; /* end of enum declaration */
#endif
public:
 int YY_PascalParser_PARSE (YY_PascalParser_PARSE_PARAM);
 virtual void YY_PascalParser_ERROR(char *msg) YY_PascalParser_ERROR_BODY;
#ifdef YY_PascalParser_PURE
#ifdef YY_PascalParser_LSP_NEEDED
 virtual int  YY_PascalParser_LEX (YY_PascalParser_STYPE *YY_PascalParser_LVAL,YY_PascalParser_LTYPE *YY_PascalParser_LLOC) YY_PascalParser_LEX_BODY;
#else
 virtual int  YY_PascalParser_LEX (YY_PascalParser_STYPE *YY_PascalParser_LVAL) YY_PascalParser_LEX_BODY;
#endif
#else
 virtual int YY_PascalParser_LEX() YY_PascalParser_LEX_BODY;
 YY_PascalParser_STYPE YY_PascalParser_LVAL;
#ifdef YY_PascalParser_LSP_NEEDED
 YY_PascalParser_LTYPE YY_PascalParser_LLOC;
#endif
 int   YY_PascalParser_NERRS;
 int    YY_PascalParser_CHAR;
#endif
#if YY_PascalParser_DEBUG != 0
 int YY_PascalParser_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
 YY_PascalParser_CLASS(YY_PascalParser_CONSTRUCTOR_PARAM);
public:
 YY_PascalParser_MEMBERS 
};
/* other declare folow */
#if YY_PascalParser_USE_CONST_TOKEN != 0

/* #line 314 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 448 "PascalParser.cc"
const int YY_PascalParser_CLASS::UNKNOWN=258;
const int YY_PascalParser_CLASS::TOK_PROGRAM=259;
const int YY_PascalParser_CLASS::TOK_IDENTIFIER=260;
const int YY_PascalParser_CLASS::TOK_CONSTANT=261;
const int YY_PascalParser_CLASS::TOK_BEGIN=262;
const int YY_PascalParser_CLASS::TOK_END=263;
const int YY_PascalParser_CLASS::TOK_PROCEDURE=264;
const int YY_PascalParser_CLASS::TOK_FUNCTION=265;
const int YY_PascalParser_CLASS::TOK_VAR=266;
const int YY_PascalParser_CLASS::TOK_CONST=267;
const int YY_PascalParser_CLASS::TOK_STRINGEXPR=268;
const int YY_PascalParser_CLASS::TOK_STRING=269;
const int YY_PascalParser_CLASS::TOK_INTEGER=270;
const int YY_PascalParser_CLASS::TOK_BYTE=271;
const int YY_PascalParser_CLASS::TOK_CHAR=272;
const int YY_PascalParser_CLASS::SYM_DOT=273;
const int YY_PascalParser_CLASS::SYM_SEMICOLON=274;
const int YY_PascalParser_CLASS::SYM_COLON=275;
const int YY_PascalParser_CLASS::SYM_COMMA=276;
const int YY_PascalParser_CLASS::SYM_EQUAL=277;
const int YY_PascalParser_CLASS::TOK_YYEOF=278;


#line 314 "E:\\msys64\\mingw64\\bin\\bison.cc"
 /* const YY_PascalParser_CLASS::token */
#endif
/*apres const  */
YY_PascalParser_CLASS::YY_PascalParser_CLASS(YY_PascalParser_CONSTRUCTOR_PARAM) YY_PascalParser_CONSTRUCTOR_INIT
{
#if YY_PascalParser_DEBUG != 0
YY_PascalParser_DEBUG_FLAG=0;
#endif
YY_PascalParser_CONSTRUCTOR_CODE;
};
#endif

/* #line 325 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 486 "PascalParser.cc"


#define	YYFINAL		73
#define	YYFLAG		32768
#define	YYNTBASE	24

#define YYTRANSLATE(x) ((unsigned)(x) <= 278 ? yytranslate[x] : 35)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23
};

#if YY_PascalParser_DEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,    11,    14,    15,    24,    33,    34,    39,
    47,    55,    63,    64,    68,    71,    72,    78,    83,    87,
    91,    93,    97,    99,   101,   103,   105
};

static const short yyrhs[] = {    -1,
    25,    24,     0,     4,     5,    19,    26,    34,    18,     0,
    27,     7,     0,     0,     9,     5,    19,    28,    27,     7,
     8,    19,     0,    10,     5,    19,    28,    27,     7,     8,
    19,     0,     0,    12,    31,    19,    28,     0,    12,     5,
    22,    13,    21,    29,    28,     0,    11,    32,    20,    33,
    19,    30,    28,     0,    11,     5,    20,    33,    19,    30,
    28,     0,     0,    31,    19,    29,     0,    31,    19,     0,
     0,    32,    20,    33,    19,    30,     0,    32,    20,    33,
    19,     0,     5,    22,    13,     0,    31,    21,    31,     0,
     5,     0,    32,    21,    32,     0,    14,     0,    15,     0,
    16,     0,    17,     0,     8,     0
};

#endif

#if YY_PascalParser_DEBUG != 0
static const short yyrline[] = { 0,
    41,    42,    46,    50,    54,    55,    56,    60,    61,    62,
    63,    64,    67,    68,    69,    72,    73,    74,    77,    78,
    81,    82,    86,    87,    88,    89,    93
};

static const char * const yytname[] = {   "$","error","$illegal.","UNKNOWN",
"TOK_PROGRAM","TOK_IDENTIFIER","TOK_CONSTANT","TOK_BEGIN","TOK_END","TOK_PROCEDURE",
"TOK_FUNCTION","TOK_VAR","TOK_CONST","TOK_STRINGEXPR","TOK_STRING","TOK_INTEGER",
"TOK_BYTE","TOK_CHAR","SYM_DOT","SYM_SEMICOLON","SYM_COLON","SYM_COMMA","SYM_EQUAL",
"TOK_YYEOF","program","program_heading","block_start","block_start_proc_func",
"block_const_var","block_const_chain","block_var_chain","block_const_idents",
"block_var_idents","block_var_type","block_ending",""
};
#endif

static const short yyr1[] = {     0,
    24,    24,    25,    26,    27,    27,    27,    28,    28,    28,
    28,    28,    29,    29,    29,    30,    30,    30,    31,    31,
    32,    32,    33,    33,    33,    33,    34
};

static const short yyr2[] = {     0,
     0,     2,     6,     2,     0,     8,     8,     0,     4,     7,
     7,     7,     0,     3,     2,     0,     5,     4,     3,     3,
     1,     3,     1,     1,     1,     1,     1
};

static const short yydefact[] = {     1,
     0,     1,     0,     2,     5,     0,     0,     0,     0,     0,
     0,    27,     0,     4,     8,     8,     3,     0,     0,     5,
     5,    21,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     8,     0,     0,     0,    23,    24,    25,    26,     0,
     0,    21,    22,    19,     9,     0,    20,     0,     0,    16,
    16,    13,     0,     6,     7,     8,     0,     8,     8,     0,
    19,    12,     0,    11,    10,    13,     0,    14,    16,    17,
     0,     0,     0
};

static const short yydefgoto[] = {     4,
     2,     8,     9,    20,    59,    56,    60,    57,    40,    13
};

static const short yypact[] = {    -1,
     9,    -1,     0,-32768,    12,    18,    27,     3,    26,    15,
    17,-32768,    19,-32768,    13,    13,-32768,    33,    34,    12,
    12,    21,     6,    22,    -9,    38,    39,    -8,    -8,    42,
    35,    13,    44,    43,    45,-32768,-32768,-32768,-32768,    31,
    36,-32768,    37,    40,-32768,    30,    41,    46,    47,    42,
    42,    44,    50,-32768,-32768,    13,     8,    13,    13,    -6,
-32768,-32768,    -8,-32768,-32768,    44,    48,-32768,    42,-32768,
    54,    56,-32768
};

static const short yypgoto[] = {    57,
-32768,-32768,    10,   -16,    -7,   -49,   -15,   -13,   -28,-32768
};


#define	YYLAST		67


static const short yytable[] = {    21,
    41,    58,     1,    25,    23,    36,    37,    38,    39,    32,
    12,    33,    66,     3,    33,    45,    43,    47,     5,    70,
     6,     7,    10,    18,    19,    29,    30,    63,    30,    26,
    27,    11,    14,    15,    67,    16,    17,    22,    24,    62,
    28,    64,    65,    31,    34,    35,    42,    44,    46,    50,
    48,    53,    49,    72,    51,    73,    71,    30,    68,     0,
    52,    33,    61,     0,    54,    55,    69
};

static const short yycheck[] = {    16,
    29,    51,     4,    19,    18,    14,    15,    16,    17,    19,
     8,    21,    19,     5,    21,    32,    30,    33,    19,    69,
     9,    10,     5,    11,    12,    20,    21,    20,    21,    20,
    21,     5,     7,    19,    63,    19,    18,     5,     5,    56,
    20,    58,    59,    22,     7,     7,     5,    13,     5,    19,
     8,    22,     8,     0,    19,     0,     0,    21,    66,    -1,
    21,    21,    13,    -1,    19,    19,    19
};

#line 325 "E:\\msys64\\mingw64\\bin\\bison.cc"
 /* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: dollar marks section change
   the next  is replaced by the list of actions, each action
   as one case of the switch.  */ 

#if YY_PascalParser_USE_GOTO != 0
/* 
 SUPRESSION OF GOTO : on some C++ compiler (sun c++)
  the goto is strictly forbidden if any constructor/destructor
  is used in the whole function (very stupid isn't it ?)
 so goto are to be replaced with a 'while/switch/case construct'
 here are the macro to keep some apparent compatibility
*/
#define YYGOTO(lb) {yy_gotostate=lb;continue;}
#define YYBEGINGOTO  enum yy_labels yy_gotostate=yygotostart; \
                     for(;;) switch(yy_gotostate) { case yygotostart: {
#define YYLABEL(lb) } case lb: {
#define YYENDGOTO } } 
#define YYBEGINDECLARELABEL enum yy_labels {yygotostart
#define YYDECLARELABEL(lb) ,lb
#define YYENDDECLARELABEL  };
#else
/* macro to keep goto */
#define YYGOTO(lb) goto lb
#define YYBEGINGOTO 
#define YYLABEL(lb) lb:
#define YYENDGOTO
#define YYBEGINDECLARELABEL 
#define YYDECLARELABEL(lb)
#define YYENDDECLARELABEL 
#endif
/* LABEL DECLARATION */
YYBEGINDECLARELABEL
  YYDECLARELABEL(yynewstate)
  YYDECLARELABEL(yybackup)
/* YYDECLARELABEL(yyresume) */
  YYDECLARELABEL(yydefault)
  YYDECLARELABEL(yyreduce)
  YYDECLARELABEL(yyerrlab)   /* here on detecting error */
  YYDECLARELABEL(yyerrlab1)   /* here on error raised explicitly by an action */
  YYDECLARELABEL(yyerrdefault)  /* current state does not do anything special for the error token. */
  YYDECLARELABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */
  YYDECLARELABEL(yyerrhandle)  
YYENDDECLARELABEL
/* ALLOCA SIMULATION */
/* __HAVE_NO_ALLOCA */
#ifdef __HAVE_NO_ALLOCA
int __alloca_free_ptr(char *ptr,char *ref)
{if(ptr!=ref) free(ptr);
 return 0;}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_PascalParser_LSP_NEEDED
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		    __ALLOCA_free(yyls,yylsa)+\
		   (num))
#else
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		   (num))
#endif
#else
#define __ALLOCA_return(num) return(num)
#define __ALLOCA_alloca(size) alloca(size)
#define __ALLOCA_free(ptr,ref) 
#endif

/* ENDALLOCA SIMULATION */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_PascalParser_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        __ALLOCA_return(0)
#define YYABORT         __ALLOCA_return(1)
#define YYERROR         YYGOTO(yyerrlab1)
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          YYGOTO(yyerrlab)
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_PascalParser_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_PascalParser_CHAR = (token), YY_PascalParser_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_PascalParser_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_PascalParser_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_PascalParser_PURE
/* UNPURE */
#define YYLEX           YY_PascalParser_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_PascalParser_CHAR;                      /*  the lookahead symbol        */
YY_PascalParser_STYPE      YY_PascalParser_LVAL;              /*  the semantic value of the */
				/*  lookahead symbol    */
int YY_PascalParser_NERRS;                 /*  number of parse errors so far */
#ifdef YY_PascalParser_LSP_NEEDED
YY_PascalParser_LTYPE YY_PascalParser_LLOC;   /*  location data for the lookahead     */
			/*  symbol                              */
#endif
#endif


#else
/* PURE */
#ifdef YY_PascalParser_LSP_NEEDED
#define YYLEX           YY_PascalParser_LEX(&YY_PascalParser_LVAL, &YY_PascalParser_LLOC)
#else
#define YYLEX           YY_PascalParser_LEX(&YY_PascalParser_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_PascalParser_DEBUG != 0
int YY_PascalParser_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif
#endif



/*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif


#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)       __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */

#ifdef __cplusplus
static void __yy_bcopy (char *from, char *to, int count)
#else
#ifdef __STDC__
static void __yy_bcopy (char *from, char *to, int count)
#else
static void __yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
#endif
#endif
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}
#endif

int
#ifdef YY_USE_CLASS
 YY_PascalParser_CLASS::
#endif
     YY_PascalParser_PARSE(YY_PascalParser_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_PascalParser_PARSE_PARAM_DEF
#endif
#endif
#endif
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YY_PascalParser_STYPE *yyvsp;
  int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
  int yychar1=0;          /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH];     /*  the state stack                     */
  YY_PascalParser_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

  short *yyss = yyssa;          /*  refer to the stacks thru separate pointers */
  YY_PascalParser_STYPE *yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_PascalParser_LSP_NEEDED
  YY_PascalParser_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
  YY_PascalParser_LTYPE *yyls = yylsa;
  YY_PascalParser_LTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YY_PascalParser_PURE
  int YY_PascalParser_CHAR;
  YY_PascalParser_STYPE YY_PascalParser_LVAL;
  int YY_PascalParser_NERRS;
#ifdef YY_PascalParser_LSP_NEEDED
  YY_PascalParser_LTYPE YY_PascalParser_LLOC;
#endif
#endif

  YY_PascalParser_STYPE yyval;             /*  the variable used to return         */
				/*  semantic values from the action     */
				/*  routines                            */

  int yylen;
/* start loop, in which YYGOTO may be used. */
YYBEGINGOTO

#if YY_PascalParser_DEBUG != 0
  if (YY_PascalParser_DEBUG_FLAG)
    fprintf(stderr, "Starting parse\n");
#endif
  yystate = 0;
  yyerrstatus = 0;
  YY_PascalParser_NERRS = 0;
  YY_PascalParser_CHAR = YYEMPTY;          /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YY_PascalParser_LSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
YYLABEL(yynewstate)

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YY_PascalParser_STYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YY_PascalParser_LSP_NEEDED
      YY_PascalParser_LTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YY_PascalParser_LSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YY_PascalParser_LSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  YY_PascalParser_ERROR("parser stack overflow");
	  __ALLOCA_return(2);
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) __ALLOCA_alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      __ALLOCA_free(yyss1,yyssa);
      yyvs = (YY_PascalParser_STYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
      __ALLOCA_free(yyvs1,yyvsa);
#ifdef YY_PascalParser_LSP_NEEDED
      yyls = (YY_PascalParser_LTYPE *) __ALLOCA_alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
      __ALLOCA_free(yyls1,yylsa);
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YY_PascalParser_LSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YY_PascalParser_DEBUG != 0
      if (YY_PascalParser_DEBUG_FLAG)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YY_PascalParser_DEBUG != 0
  if (YY_PascalParser_DEBUG_FLAG)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  YYGOTO(yybackup);
YYLABEL(yybackup)

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* YYLABEL(yyresume) */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yydefault);

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (YY_PascalParser_CHAR == YYEMPTY)
    {
#if YY_PascalParser_DEBUG != 0
      if (YY_PascalParser_DEBUG_FLAG)
	fprintf(stderr, "Reading a token: ");
#endif
      YY_PascalParser_CHAR = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (YY_PascalParser_CHAR <= 0)           /* This means end of input. */
    {
      yychar1 = 0;
      YY_PascalParser_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_PascalParser_DEBUG != 0
      if (YY_PascalParser_DEBUG_FLAG)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(YY_PascalParser_CHAR);

#if YY_PascalParser_DEBUG != 0
      if (YY_PascalParser_DEBUG_FLAG)
	{
	  fprintf (stderr, "Next token is %d (%s", YY_PascalParser_CHAR, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, YY_PascalParser_CHAR, YY_PascalParser_LVAL);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    YYGOTO(yydefault);

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrlab);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrlab);

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YY_PascalParser_DEBUG != 0
  if (YY_PascalParser_DEBUG_FLAG)
    fprintf(stderr, "Shifting token %d (%s), ", YY_PascalParser_CHAR, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (YY_PascalParser_CHAR != YYEOF)
    YY_PascalParser_CHAR = YYEMPTY;

  *++yyvsp = YY_PascalParser_LVAL;
#ifdef YY_PascalParser_LSP_NEEDED
  *++yylsp = YY_PascalParser_LLOC;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  YYGOTO(yynewstate);

/* Do the default action for the current state.  */
YYLABEL(yydefault)

  yyn = yydefact[yystate];
  if (yyn == 0)
    YYGOTO(yyerrlab);

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
YYLABEL(yyreduce)
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YY_PascalParser_DEBUG != 0
  if (YY_PascalParser_DEBUG_FLAG)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


/* #line 811 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 1121 "PascalParser.cc"

  switch (yyn) {

}

#line 811 "E:\\msys64\\mingw64\\bin\\bison.cc"
   /* the action file gets copied in in place of this dollarsign  */
  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YY_PascalParser_LSP_NEEDED
  yylsp -= yylen;
#endif

#if YY_PascalParser_DEBUG != 0
  if (YY_PascalParser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YY_PascalParser_LSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = YY_PascalParser_LLOC.first_line;
      yylsp->first_column = YY_PascalParser_LLOC.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  YYGOTO(yynewstate);

YYLABEL(yyerrlab)   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++YY_PascalParser_NERRS;

#ifdef YY_PascalParser_ERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      YY_PascalParser_ERROR(msg);
	      free(msg);
	    }
	  else
	    YY_PascalParser_ERROR ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YY_PascalParser_ERROR_VERBOSE */
	YY_PascalParser_ERROR("parse error");
    }

  YYGOTO(yyerrlab1);
YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (YY_PascalParser_CHAR == YYEOF)
	YYABORT;

#if YY_PascalParser_DEBUG != 0
      if (YY_PascalParser_DEBUG_FLAG)
	fprintf(stderr, "Discarding token %d (%s).\n", YY_PascalParser_CHAR, yytname[yychar1]);
#endif

      YY_PascalParser_CHAR = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;              /* Each real token shifted decrements this */

  YYGOTO(yyerrhandle);

YYLABEL(yyerrdefault)  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) YYGOTO(yydefault);
#endif

YYLABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YY_PascalParser_LSP_NEEDED
  yylsp--;
#endif

#if YY_PascalParser_DEBUG != 0
  if (YY_PascalParser_DEBUG_FLAG)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

YYLABEL(yyerrhandle)

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    YYGOTO(yyerrdefault);

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    YYGOTO(yyerrdefault);

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	YYGOTO(yyerrpop);
      yyn = -yyn;
      YYGOTO(yyreduce);
    }
  else if (yyn == 0)
    YYGOTO(yyerrpop);

  if (yyn == YYFINAL)
    YYACCEPT;

#if YY_PascalParser_DEBUG != 0
  if (YY_PascalParser_DEBUG_FLAG)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = YY_PascalParser_LVAL;
#ifdef YY_PascalParser_LSP_NEEDED
  *++yylsp = YY_PascalParser_LLOC;
#endif

  yystate = yyn;
  YYGOTO(yynewstate);
/* end loop, in which YYGOTO may be used. */
  YYENDGOTO
}

/* END */

/* #line 1010 "E:\\msys64\\mingw64\\bin\\bison.cc" */
#line 1329 "PascalParser.cc"
#line 96 "pascal.yy"


