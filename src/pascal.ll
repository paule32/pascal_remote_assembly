// -----------------------------------------------------------------
// File:   Pascal.ll
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
%name PascalScanner

%define LEX_PARAM YY_PascalParser_STYPE *val, YY_PascalParser_LTYPE *loc
%define MEMBERS public: int line, column;
%define CONSTRUCTOR_INIT : line(1), column(1)
%define CLASS PascalScanner

%header{
# include <stdio.h>
# include <libintl.h>
# include <locale.h>
# include <stdlib.h>
# include <strings.h>

# include <iostream>
# include <sstream>
# include <cstring>

# include "PascalParser.h"
# include "PascalScanner.h"

extern std::istream * lexer_input;
extern void yyerror(char * err);

# undef  YY_INPUT
# define YY_INPUT(buf, result, max_size)  \
  result = 0; \
  while (1) { \
    int c = lexer_input->get(); \
    if (lexer_input->eof()) { \
      break; \
    } \
    buf[result++] = c; \
    if (result == max_size || c == '\n') { \
      break; \
    } \
  }
# define _(String) gettext(String)
%}

A [Aa]
B [Bb]
C [Cc]
D [Dd]
E [Ee]
F [Ff]
G [Gg]
H [Hh]
I [Ii]
J [Jj]
K [Kk]
L [Ll]
M [Mm]
N [Nn]
O [Oo]
P [Pp]
Q [Qq]
R [Rr]
S [Ss]
T [Tt]
U [Uu]
V [Vv]
W [Ww]
X [Xx]
Y [Yy]
Z [Zz]

%x PAS_COMMENT NEW_COMMENT
%x DEF_BLOCK
%x DEF_BLOCK_COMMENT
%x DEF_BLOCK_IFDEF
%x DEF_BLOCK_ELSE
%x DEF_BLOCK_CONDITION
%x DEF_BLOCK_CHECK_COMMENT
%x DOX DOX_FILE DOX_AUTHOR DOX_BRIEF DOX_BUG

%%

\t          { column += 8;             }
[\n|\r\n]   { column  = 1; line++;     }
[ ]         { column += strlen(yytext);             }

{B}{E}{G}{I}{N}             { column += 5; return PascalParser::TOK_BEGIN;      }
{B}{Y}{T}{E}                { column += 4; return PascalParser::TOK_BYTE;       }
{C}{H}{A}{R}                { column += 4; return PascalParser::TOK_CHAR;       }
{C}{O}{N}{S}{T}             { column += 5; return PascalParser::TOK_CONST;      }
{E}{N}{D}                   { column += 3; return PascalParser::TOK_END;        }
{F}{U}{N}{C}{T}{I}{O}{N}    { column += 8; return PascalParser::TOK_FUNCTION;   }
{I}{N}{T}{E}{G}{E}{R}       { column += 7; return PascalParser::TOK_INTEGER;    }
{P}{R}{O}{C}{E}{D}{U}{R}{E} { column += 9; return PascalParser::TOK_PROCEDURE;  }
{P}{R}{O}{G}{R}{A}{M}       { column += 7; return PascalParser::TOK_PROGRAM;    }
{S}{T}{R}{I}{N}{G}          { column += 6; return PascalParser::TOK_STRING;     }
{V}{A}{R}                   { column += 3; return PascalParser::TOK_VAR;        }

[a-zA-Z_][a-zA-Z0-9_]*  { column += strlen(yytext); val->string_val = strdup( yytext ); return PascalParser::TOK_IDENTIFIER; }
[0-9]+                  { column += strlen(yytext); val->int_val = atoi(yytext); return PascalParser::TOK_CONSTANT;   }

"//".*                  { column += strlen(yytext); }

"{$"                                                { BEGIN(DEF_BLOCK); }
<DEF_BLOCK>\}                                       { BEGIN(INITIAL);   }
<DEF_BLOCK>{D}{E}{F}{I}{N}{E}[ ]+[a-zA-Z0-9_]+      {
    column += strlen(yytext);
    BEGIN(DEF_BLOCK_COMMENT);
}
<DEF_BLOCK>{E}{L}{S}{E}               {
    column += strlen(yytext);
    BEGIN(DEF_BLOCK_COMMENT);
}
<DEF_BLOCK>{E}{N}{D}{I}{F}            {
    column += strlen(yytext);
    BEGIN(DEF_BLOCK_COMMENT);
}
<DEF_BLOCK>{I}{F}{D}{E}{F}            {
    column += strlen(yytext);
    BEGIN(DEF_BLOCK_IFDEF);
}
<DEF_BLOCK>\n           { column = 1; line += 1; }
<DEF_BLOCK>.            { }

<DEF_BLOCK_IFDEF>[ ]+[a-zA-Z0-9_]+    {
    column += strlen(yytext);
    BEGIN(DEF_BLOCK_CONDITION);
}
<DEF_BLOCK_IFDEF>\}     { BEGIN(INITIAL);           }
<DEF_BLOCK_IFDEF>\n     { column  = 1; line += 1;   }

<DEF_BLOCK_CONDITION>[ ]*"=="[ ]*[a-zA-Z0-9_]+ { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }
<DEF_BLOCK_CONDITION>[ ]*"!="[ ]*[a-zA-Z0-9_]+ { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }
<DEF_BLOCK_CONDITION>[ ]*"<>"[ ]*[a-zA-Z0-9_]+ { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }
<DEF_BLOCK_CONDITION>[ ]*"<="[ ]*[a-zA-Z0-9_]+ { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }
<DEF_BLOCK_CONDITION>[ ]*">="[ ]*[a-zA-Z0-9_]+ { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }
<DEF_BLOCK_CONDITION>[ ]*"=>"[ ]*[a-zA-Z0-9_]+ { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }
<DEF_BLOCK_CONDITION>[ ]*"=<"[ ]*[a-zA-Z0-9_]+ { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }

<DEF_BLOCK_CONDITION>[ ]*"<"[ ]*[a-zA-Z0-9_]+  { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }
<DEF_BLOCK_CONDITION>[ ]*">"[ ]*[a-zA-Z0-9_]+  { column += strlen(yytext); BEGIN(DEF_BLOCK_CHECK_COMMENT); }

<DEF_BLOCK_CONDITION>\}     { BEGIN(INITIAL);           }
<DEF_BLOCK_CONDITION>\n     { column  = 1; line += 1;   }
<DEF_BLOCK_CONDITION>.      {
    std::cout << _("not a valid pre-processor command.") << std::endl;
    yyterminate();
}

<DEF_BLOCK_CHECK_COMMENT>\} { BEGIN(INITIAL);  }
<DEF_BLOCK_CHECK_COMMENT>.  {
    std::cout << _("not a valid pre-processor command.") << std::endl;
    yyterminate();
}

<DEF_BLOCK_COMMENT>\}   { BEGIN(INITIAL);           }
<DEF_BLOCK_COMMENT>\n   { column  = 1; line += 1;   }
<DEF_BLOCK_COMMENT>.    { }

\{                      { BEGIN(NEW_COMMENT);       }
<NEW_COMMENT>\}         { BEGIN(INITIAL);           }
<NEW_COMMENT>\n         { column  = 1; line += 1;   }
<NEW_COMMENT>.          { }

"(**"                   { BEGIN(DOX); }

<DOX>[ \*]*"@file"[ ]+        { BEGIN(DOX_FILE);    }
<DOX>[ \*]*"@author"[ ]+      { BEGIN(DOX_AUTHOR);  }
<DOX>[ \*]*"@brief"[ ]+       { BEGIN(DOX_BRIEF);   }
<DOX>[ \*]*"@bug"[ ]+         { BEGIN(DOX_BUG);     }
<DOX>\n                 { column  = 1; line += 1;   }
<DOX>"*)"               { std::cout << "ende" << std::endl; BEGIN(INITIAL);           }

<DOX_FILE>[a-zA-Z0-9_\.\/\:\>\\\$]+     { std::cout << "file  : " << yytext << std::endl; }
<DOX_FILE>"*)"          { BEGIN(INITIAL);           }
<DOX_FILE>\n            { column  = 1; line += 1;   }

<DOX_AUTHOR>.*          { std::cout << "author: " << yytext << std::endl; }
<DOX_AUTHOR>"*)"        { BEGIN(INITIAL);           }
<DOX_AUTHOR>\n          { column  = 1; line += 1;   }

<DOX_BRIEF>.*           { std::cout << "brief : " << yytext << std::endl; }
<DOX_BRIEF>"*)"         { BEGIN(INITIAL);           }
<DOX_BRIEF>\n           { column  = 1; line += 1;   }

<DOX_BUG>.*             { std::cout << "bug   : " << yytext << std::endl; }
<DOX_BUG>"*)"           { BEGIN(INITIAL);           }
<DOX_BUG>\n             { column  = 1; line += 1;   }

"(*"                    { BEGIN(PAS_COMMENT);       }
<PAS_COMMENT>"*)"       { BEGIN(INITIAL);           }
<PAS_COMMENT>[^*\n]+    { }
<PAS_COMMENT>\*         { column += 1;              }
<PAS_COMMENT>\n         { column  = 1; line += 1;   }

"="          { column += 1; return PascalParser::SYM_EQUAL;      }

";"          { column += 1;         return PascalParser::SYM_SEMICOLON;  }
";"[\n|\r\n] { column  = 1; line++; return PascalParser::SYM_SEMICOLON;  }

":"          { column += 1; return PascalParser::SYM_COLON;      }
","          { column += 1; return PascalParser::SYM_COMMA;      }
\.           { column += 1; return PascalParser::SYM_DOT;        }

\'.*\'       {
    column += strlen(yytext);
    val->string_val = strdup( yytext );
    return PascalParser::TOK_STRINGEXPR;
}

.            { column += 1;
    std::stringstream ss;
    ss << _("Invalide character: ") << yytext[0];
    val->string_val = strdup( ss.str().c_str() );
    
    return PascalParser::UNKNOWN;
}

<<EOF>>      { yyterminate(); }
%%
