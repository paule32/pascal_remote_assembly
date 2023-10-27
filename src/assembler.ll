// -----------------------------------------------------------------
// File:   Assembler.ll
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
%name AssemblerScanner

%define LEX_PARAM YY_AssemblerParser_STYPE *val, YY_AssemblerParser_LTYPE *loc
%define MEMBERS public: int line, column;
%define CONSTRUCTOR_INIT : line(1), column(1)
%define CLASS AssemblerScanner

%header{
# include <windows.h>

# include "Parser.h"
# include <stdio.h>
# include <libintl.h>
# include <locale.h>
# include <stdlib.h>
# include <strings.h>

# include <iostream>
# include <string>
# include <sstream>
# include <cstring>

# include "AssemblerParser.h"
# include "AssemblerScanner.h"

extern std::istream * lexer_input;
extern void yyerror(char * err);

extern int line;
extern int column;

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

ident [a-zA-Z_][a-zA-Z0-9_]*
hexdigit    (0[xX])?[a-fA-F0-9]*
decdigit    [0..9]*
ws          [ \t\n| \t\r\n]*

%x NEW_COMMENT
%x SEQ_SECTION ASM_POP ASM_PUSH ASM_MOV ASM_SUB

%%

\t          { column += 8; }
[\n|\r\n]   { column  = 1; line++; }
[ ]         { column += 1; }

{C}{A}{L}{L}{ws}({ident})    { column += strlen(yytext); std::cout << "\t"  << "call  " << yytext + 5 << "  ; ok" << std::endl; BEGIN(INITIAL); }

{D}{B}{ws}({hexdigit}|{decdigit}) { column += strlen(yytext); std::cout << "\t"  << yytext << "   ; ok" << std::endl; BEGIN(INITIAL); }
{D}{W}{ws}({hexdigit}|{decdigit}) { column += strlen(yytext); std::cout << "\t"  << yytext << "   ; ok" << std::endl; BEGIN(INITIAL); }
{D}{D}{ws}({hexdigit}|{decdigit}) { column += strlen(yytext); std::cout << "\t"  << yytext << "   ; ok" << std::endl; BEGIN(INITIAL); }
{D}{Q}{ws}({hexdigit}|{decdigit}) { column += strlen(yytext); std::cout << "\t"  << yytext << "   ; ok" << std::endl; BEGIN(INITIAL); }

{M}{O}{V}{ws}                { column += strlen(yytext); std::cout << "\t"  << "mov   "; BEGIN(ASM_MOV); }
<ASM_MOV>{E}{A}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "ecx, " << yytext + 5 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{B}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "ecx, " << yytext + 5 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{C}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "ecx, " << yytext + 5 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{D}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "ecx, " << yytext + 5 << "  ; ok" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{R}{D}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "rdx, " << yytext + 5 << "  ; ok" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{R}1{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r1, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}2{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r2, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}3{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r3, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}4{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r4, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}5{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r5, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}6{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r6, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}7{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r7, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}8{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r8, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}9{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r9, " << yytext + 4 << "  ; ok" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{R}9{D}{ws}\,{ws}({hexdigit}|{decdigit})  { column += strlen(yytext); std::cout << "r9d, " << yytext + 5 << "  ; ok" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{E}{D}{X}{ws}\,{ws}{hexdigit}  { column += strlen(yytext); std::cout << "edx, 1" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{D}{X}{ws}\,{ws}{decdigit}  { column += strlen(yytext); std::cout << "edx, 2" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{E}{A}{X}{ws}\,{ws}{E}{B}{X}  { column += strlen(yytext); std::cout << "eax, ebx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{A}{X}{ws}\,{ws}{E}{C}{X}  { column += strlen(yytext); std::cout << "eax, ecx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{A}{X}{ws}\,{ws}{E}{D}{X}  { column += strlen(yytext); std::cout << "eax, edx" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{E}{A}{X}{ws}\,{ws}{E}{A}{X}  { column += strlen(yytext); std::cout << "eax, eax" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{A}{X}{ws}\,{ws}{E}{B}{X}  { column += strlen(yytext); std::cout << "eax, ebx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{A}{X}{ws}\,{ws}{E}{C}{X}  { column += strlen(yytext); std::cout << "eax, ecx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{A}{X}{ws}\,{ws}{E}{D}{X}  { column += strlen(yytext); std::cout << "eax, edx" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{E}{B}{X}{ws}\,{ws}{E}{A}{X}  { column += strlen(yytext); std::cout << "ebx, eax" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{B}{X}{ws}\,{ws}{E}{B}{X}  { column += strlen(yytext); std::cout << "ebx, ebx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{B}{X}{ws}\,{ws}{E}{C}{X}  { column += strlen(yytext); std::cout << "ebx, ecx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{B}{X}{ws}\,{ws}{E}{D}{X}  { column += strlen(yytext); std::cout << "ebx, edx" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{E}{C}{X}{ws}\,{ws}{E}{A}{X}  { column += strlen(yytext); std::cout << "ecx, eax" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{C}{X}{ws}\,{ws}{E}{B}{X}  { column += strlen(yytext); std::cout << "ecx, ebx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{C}{X}{ws}\,{ws}{E}{C}{X}  { column += strlen(yytext); std::cout << "ecx, ecx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{C}{X}{ws}\,{ws}{E}{D}{X}  { column += strlen(yytext); std::cout << "ecx, edx" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{E}{D}{X}{ws}\,{ws}{E}{A}{X}  { column += strlen(yytext); std::cout << "edx, eax" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{D}{X}{ws}\,{ws}{E}{B}{X}  { column += strlen(yytext); std::cout << "edx, ebx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{D}{X}{ws}\,{ws}{E}{C}{X}  { column += strlen(yytext); std::cout << "edx, ecx" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{E}{D}{X}{ws}\,{ws}{E}{D}{X}  { column += strlen(yytext); std::cout << "edx, edx" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{R}{B}{P}{ws}\,{ws}{R}{A}{P}  { column += strlen(yytext); std::cout << "rbp, rdp" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}{B}{P}{ws}\,{ws}{R}{B}{P}  { column += strlen(yytext); std::cout << "rbp, rbp" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}{B}{P}{ws}\,{ws}{R}{C}{P}  { column += strlen(yytext); std::cout << "rbp, rcp" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}{B}{P}{ws}\,{ws}{R}{D}{P}  { column += strlen(yytext); std::cout << "rbp, rdp" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}{B}{P}{ws}\,{ws}{R}{S}{P}  { column += strlen(yytext); std::cout << "rbp, rsp   ; ok" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{R}{A}{X}{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "rcx, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}{B}{X}{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "rcx, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}{C}{X}{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "rcx, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}{D}{X}{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "rcx, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{R}1{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r1, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}2{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r2, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}3{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r3, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}4{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r4, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}5{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r5, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}6{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r6, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}7{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r7, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}8{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r8, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }
<ASM_MOV>{R}9{ws}\,{ws}{Q}{W}{O}{R}{D}{ws}\[{ws}{R}{S}{P}{ws}\+{ws}({hexdigit}|{decdigit}){ws}\]  { column += strlen(yytext); std::cout << "r9, " << yytext + 5 << "   ; ok" << std::endl; BEGIN(INITIAL);  }

<ASM_MOV>{R}{S}{P}{ws}\,{ws}{R}{B}{P}  { column += strlen(yytext); std::cout << "rsp, rbp" << "  ; ok" << std::endl; BEGIN(INITIAL);  }

{P}{O}{P}{ws}                { column += strlen(yytext); std::cout << "\t"  << "pop   "; BEGIN(ASM_POP); }
<ASM_POP>{E}{A}{X}      { column += strlen(yytext); std::cout << "eax" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_POP>{E}{B}{X}      { column += strlen(yytext); std::cout << "ebx" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_POP>{E}{C}{X}      { column += strlen(yytext); std::cout << "ecx" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_POP>{E}{D}{X}      { column += strlen(yytext); std::cout << "edx" << "  ; ok" << std::endl; BEGIN(INITIAL); }

<ASM_POP>{R}{B}{P}      { column += strlen(yytext); std::cout << "rbp" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_POP>{R}{S}{P}      { column += strlen(yytext); std::cout << "rsp" << "  ; ok" << std::endl; BEGIN(INITIAL); }

{P}{U}{S}{H}                 { column += strlen(yytext); std::cout << "\t"  << "push  "; BEGIN(ASM_PUSH); }
<ASM_PUSH>{ws}{E}{A}{X}      { column += strlen(yytext); std::cout << "eax" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_PUSH>{ws}{E}{B}{X}      { column += strlen(yytext); std::cout << "ebx" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_PUSH>{ws}{E}{C}{X}      { column += strlen(yytext); std::cout << "ecx" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_PUSH>{ws}{E}{D}{X}      { column += strlen(yytext); std::cout << "edx" << "  ; ok" << std::endl; BEGIN(INITIAL); }
<ASM_PUSH>{ws}{R}{B}{P}      { column += strlen(yytext); std::cout << "rbp" << "  ; ok" << std::endl; BEGIN(INITIAL); }

{R}{E}{T}{ws}               { column += strlen(yytext); std::cout << "\tret   ; ok" << std::endl; BEGIN(INITIAL); }

{S}{U}{B}      { column += strlen(yytext); std::cout << "\t"  << "sub   "; BEGIN(ASM_SUB); }
<ASM_SUB>{ws}{E}{A}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { std::cout << "eAX, " << yytext + 6 << "  ; ok" <<std::endl; BEGIN(INITIAL); }
<ASM_SUB>{ws}{E}{B}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { std::cout << "eAX, " << yytext + 6 << "  ; ok" <<std::endl; BEGIN(INITIAL); }
<ASM_SUB>{ws}{E}{C}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { std::cout << "ecX, " << yytext + 6 << "  ; ok" <<std::endl; BEGIN(INITIAL); }
<ASM_SUB>{ws}{E}{D}{X}{ws}\,{ws}({hexdigit}|{decdigit})  { std::cout << "edX, " << yytext + 6 << "  ; ok" <<std::endl; BEGIN(INITIAL); }
<ASM_SUB>{ws}{R}{S}{P}{ws}\,{ws}({hexdigit}|{decdigit})  { std::cout << "RSP, " << yytext + 6 << "  ; ok" << std::endl; BEGIN(INITIAL); }

{S}{E}{C}{T}{I}{O}{N}       { column += strlen(yytext); std::cout << "section: "; BEGIN(SEQ_SECTION); }
<SEQ_SECTION>\.{T}{E}{X}{T} { column += strlen(yytext); std::cout << ".text" << yytext << "  ; ok" << std::endl; BEGIN(INITIAL); }
<SEQ_SECTION>\.{D}{A}{T}{A} { column += strlen(yytext); std::cout << ".data" << yytext << "  ; ok" << std::endl; BEGIN(INITIAL); }

{ident}*[\:|\:\n|\:\r\n]      {
    column += strlen(yytext); 
    std::cout << yytext << "  ; ok" << std::endl;
    BEGIN(INITIAL);
}

\{                      { column += strlen(yytext); BEGIN(NEW_COMMENT);       }
<NEW_COMMENT>\}         { column += strlen(yytext); BEGIN(INITIAL);           }
<NEW_COMMENT>\n         { column += strlen(yytext); line++; }
<NEW_COMMENT>.          { column += strlen(yytext); }

";".*{ws}          { }

.   {
    column += 1;
    std::stringstream ss;
    ss << _("Invalide character: ") << yytext[0];
    val->string_val = strdup( ss.str().c_str() );
    
    return AssemblerParser::UNKNOWN;
}

<<EOF>>      { yyterminate(); }
%%
