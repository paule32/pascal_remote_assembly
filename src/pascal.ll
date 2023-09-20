// -----------------------------------------------------------------
// File:   Pascall.ll
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
%define IN yyin
%define OUT yyout
%define IFILE FILE
%define OFILE FILE

%header{
# include <iostream>
# include <sstream>

# include "PascalParser.h"
# include "PascalScanner.h"

extern std::istream * lexer_input;

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
%}

%%

[ \t]*      { /* empty */ }
[\n|\r\n]   { line++;   }

"program"   { return PascalParser::TOK_PROGRAM;    }
"procedure" { return PascalParser::TOK_PROCEDURE;  }
"function"  { return PascalParser::TOK_FUNCTION;   }
"begin"     { return PascalParser::TOK_BEGIN;      }
"end"       { return PascalParser::TOK_END;        }
"const"     { return PascalParser::TOK_CONST;      }
"var"       { return PascalParser::TOK_VAR;        }
"string"    { return PascalParser::TOK_STRING;     }
"integer"   { return PascalParser::TOK_INTEGER;    }
"byte"      { return PascalParser::TOK_BYTE;       }
"char"      { return PascalParser::TOK_CHAR;       }

"="         { return PascalParser::SYM_EQUAL;      }
";"         { return PascalParser::SYM_SEMICOLON;  }
":"         { return PascalParser::SYM_COLON;      }
","         { return PascalParser::SYM_COMMA;      }
\.          { return PascalParser::SYM_DOT;        }

'[^']*'                 { val->string_val = strdup( yytext ); return PascalParser::TOK_STRINGEXPR; }
[a-zA-Z_][a-zA-Z0-9_]*  { val->string_val = strdup( yytext ); return PascalParser::TOK_IDENTIFIER; }

[0-9]+                  { val->int_val = atoi(yytext); return PascalParser::TOK_CONSTANT;   }

"{"[^}]*"}"             ;

"//".*                  ;

"(*"[^"*)"]*"*)"        ;

.                       {
    std::stringstream ss;
    ss << "Ungültiges Zeichen: " << yytext[0];
    val->string_val = strdup( ss.str().c_str() );
    
    return PascalParser::UNKNOWN;
}

<<EOF>>                 { yyterminate(); }
%%
