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
%token TOK_YYEOF 0

%token TOK_ID TOK_STRING
%token TOK_DOT TOK_SECTION TOK_SECT_ID
%token TOK_HEX TOK_DEC

%token TOK_DB TOK_DW TOK_DD TOK_DQ

%token TOK_ADC
%token TOK_ADD

%token TOK_AND

%token TOK_CALL
%token TOK_CMP

%token TOK_JE
%token TOK_JMP
%token TOK_JNZ
%token TOK_JZ

%token TOK_MOV
%token TOK_NOP
%token TOK_POP
%token TOK_PUSH

%token TOK_RET
%token TOK_SUB


%token TOK_QWORD TOK_DWORD TOK_WORD TOK_BYTE TOK_PTR

%token TOK_RAX TOK_RBX TOK_RCX TOK_RDX TOK_RDI TOK_RSI TOK_RSP TOK_RBP
%token TOK_EAX TOK_EBX TOK_ECX TOK_EDX TOK_EDI TOK_ESI TOK_ESP TOK_EBP
%token TOK_AX  TOK_BX  TOK_CX  TOK_DX  TOK_DI  TOK_SI  TOK_SP  TOK_BP
%token TOK_AH  TOK_BH  TOK_CH  TOK_DH
%token TOK_AL  TOK_BL  TOK_CL  TOK_DL

%token TOK_R0  TOK_R1  TOK_R2   TOK_R3   TOK_R4   TOK_R5   TOK_R6   TOK_R7
%token TOK_R8  TOK_R9  TOK_R10  TOK_R11  TOK_R12  TOK_R13  TOK_R14  TOK_R15


%token TOK_R0B8  TOK_R1B8  TOK_R2B8   TOK_R3B8

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
    | _tok_ddata
    | TOK_ADC {
    }
    | TOK_ADD {
    }
    | TOK_MOV   reg ',' reg
    | TOK_MOV   mem ',' reg
    | TOK_MOV   reg ',' mem
    | TOK_MOV   reg ',' imm32
    | TOK_MOV   reg ',' _tok_id {
    }
    | TOK_POP   reg
    | TOK_PUSH  reg
    | TOK_RET
    | TOK_SUB   reg ',' _tok_num
    | TOK_CALL _tok_id {
    }
    ;
    
reg
    : reg64
    | reg32
    | reg16
    | reg8h | reg8l
    ;
    
reg64 : TOK_RAX | TOK_RBX | TOK_RCX | TOK_RDX | TOK_RSI | TOK_RDI | TOK_RBP | TOK_RSP | _reg64 ;
reg32 : TOK_EAX | TOK_EBX | TOK_ECX | TOK_EDX | TOK_ESI | TOK_EDI | TOK_EBP | TOK_ESP | _reg64 ;
reg16 : TOK_AX  | TOK_BX  | TOK_CX  | TOK_DX  | TOK_SI  | TOK_DI  | TOK_BP  | TOK_SP  | _reg64 ;
reg8h : TOK_AH  | TOK_BH  | TOK_CH  | TOK_DH                                          | _reg64 ;
reg8l : TOK_AL  | TOK_BL  | TOK_CL  | TOK_DL                                          | _reg64 ;
    
_reg64
    : TOK_R0  | TOK_R1  | TOK_R2  | TOK_R3  | TOK_R4  | TOK_R5  | TOK_R6  | TOK_R7
    | TOK_R8  | TOK_R9  | TOK_R10 | TOK_R11 | TOK_R12 | TOK_R13 | TOK_R14 | TOK_R15
    ;
mem
    :  _mem_ptr
    | __mem_ptr
    ;
_mem_ptr
    : _mem_ptr_byte  __mem_ptr
    | _mem_ptr_word  __mem_ptr
    | _mem_ptr_dword __mem_ptr
    | _mem_ptr_qword __mem_ptr
    ;

_mem_ptr_byte  : TOK_BYTE  TOK_PTR | TOK_BYTE  ;
_mem_ptr_word  : TOK_WORD  TOK_PTR | TOK_WORD  ;
_mem_ptr_dword : TOK_DWORD TOK_PTR | TOK_DWORD ;
_mem_ptr_qword : TOK_QWORD TOK_PTR | TOK_QWORD ;

__mem_ptr
    : '[' reg '+' _tok_num ']'
    ;

imm32
    : _tok_num
    ;

_tok_id      : TOK_ID      { $$ = yylval.string_val; } ;
_tok_sect_id : TOK_SECT_ID { $$ = yylval.string_val; } ;

_tok_num     : TOK_HEX | TOK_DEC ;

_tok_ddata
    : TOK_DB _tok_vardata
    | TOK_DW _tok_vardata
    | TOK_DD _tok_vardata
    | TOK_DQ _tok_vardata
    ;
_tok_vardata
    : _tok_sdata
    | _tok_ndata
    ;
_tok_sdata
    : TOK_STRING ',' _tok_ndata
    | TOK_STRING
    ;
_tok_ndata
    : _tok_num
    | _tok_ndata ',' _tok_ndata
    ;
%%
