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

%token TOK_ID TOK_CONSTANT
%token TOK_DOT TOK_SECTION TOK_SECT_ID
%token TOK_HEX TOK_DEC

%token TOK_ADC TOK_ADCX
%token TOK_ADD TOK_ADDPD TOK_ADDPS TOK_ADDSS TOK_ADDSUBPD TOK_ADDSUBPS 
%token TOK_ADOX

%token TOK_AESDEC TOK_AESDECLAST
%token TOK_AESENC TOK_AESENCLAST

%token TOK_AND TOK_ANDNPD TOK_ANDPS TOK_ANDPD

%token TOK_CALL
%token TOK_CMP

%token TOK_MOV
%token TOK_NOP
%token TOK_POP
%token TOK_PUSH

%token TOK_QWORD TOK_DWORD TOK_WORD TOK_BYTE TOK_PTR

%token TOK_RAX TOK_RBX TOK_RCX TOK_RDX TOK_RDI TOK_RSI TOK_RSP TOK_RBP
%token TOK_EAX TOK_EBX TOK_ECX TOK_EDX TOK_EDI TOK_ESI TOK_ESP TOK_EBP
%token TOK_AX  TOK_BX  TOK_CX  TOK_DX  TOK_DI  TOK_SI  TOK_SP  TOK_BP
%token TOK_AH  TOK_BH  TOK_CH  TOK_DH
%token TOK_AL  TOK_BL  TOK_CL  TOK_DL

%token TOK_R0  TOK_R1  TOK_R2  TOK_R3  TOK_R4  TOK_R5  TOK_R6  TOK_R7  TOK_R8  TOK_R9  TOK_R10  TOK_R11  TOK_R12  TOK_R13  TOK_R14  TOK_R15 
%token TOK_R0D TOK_R1D TOK_R2D TOK_R3D TOK_R4D TOK_R5D TOK_R6D TOK_R7D TOK_R8D TOK_R9D TOK_R10D TOK_R11D TOK_R12D TOK_R13D TOK_R14D TOK_R15D
%token TOK_R0W TOK_R1W TOK_R2W TOK_R3W TOK_R4W TOK_R5W TOK_R6W TOK_R7W TOK_R8W TOK_R9W TOK_R10W TOK_R11W TOK_R12W TOK_R13W TOK_R14W TOK_R15W
%token TOK_R0B TOK_R1B TOK_R2B TOK_R3B TOK_R4B TOK_R5B TOK_R6B TOK_R7B TOK_R8B TOK_R9B TOK_R10B TOK_R11B TOK_R12B TOK_R13B TOK_R14B TOK_R15B

%token TOK_RET
%token TOK_SUB

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
    | TOK_MOV reg ',' reg
    | TOK_MOV mem ',' reg
    | TOK_MOV reg ',' mem
    | TOK_MOV reg ',' imm32
    | TOK_MOV reg ',' TOK_BYTE  TOK_PTR '[' TOK_RSP '+' ']'
    | TOK_MOV reg ',' TOK_WORD  TOK_PTR '[' TOK_RSP '+' ']'
    | TOK_MOV reg ',' TOK_DWORD TOK_PTR '[' TOK_RSP '+' ']'
    | TOK_MOV reg ',' TOK_QWORD TOK_PTR '[' TOK_RSP '+' ']'
    | TOK_MOV TOK_BYTE  mem ',' imm32
    | TOK_MOV TOK_WORD  mem ',' imm32
    | TOK_MOV TOK_DWORD mem ',' imm32
    | TOK_MOV TOK_QWORD mem ',' imm32
    | TOK_CALL _tok_id {
    printf("1212121212\n");
        std::cout << "---------------------" << std::endl;
    }
    ;

reg
    : reg64   | reg32   | reg16   | reg8    ;
reg64
    : TOK_RAX | TOK_RBX | TOK_TCX | TOK_RDX | TOK_RSI | TOK_RDI | TOK_RBP | TOK_RSP
    | TOK_R0  | TOK_R1  | TOK_R2  | TOK_R3  | TOK_R4  | TOK_R5  | TOK_R6  | TOK_R7
    ;
reg32
    : TOK_EAX | TOK_EBX | TOK_ECX | TOK_EDX | TOK_ESI | TOK_EDI | TOK_EBP | TOK_ESP
    | TOK_R0D | TOK_R1D | TOK_R2D | TOK_R3D | TOK_R4D | TOK_R5D | TOK_R6D | TOK_R7D
    ;
reg16
    : TOK_AX  | TOK_BX  | TOK_CX  | TOK_DX  | TOK_SI  | TOK_DI  | TOK_BP  | TOK_SP
    | TOK_R0W | TOK_R1W | TOK_R2W | TOK_R3W | TOK_R4W | TOK_R5W | TOK_R6W | TOK_R7W
    ;
reg8
    ; TOK_AH  | TOK_BH  | TOK_CH  | TOK_DH
    | TOK_AL  | TOK_BL  | TOK_CL  | TOK_DL
    | TOK_R0B | TOK_R1B | TOK_R2B | TOK_R3B
    ;

mem
    : TOK_ID
    ;
imm32
    : TOK_ID
    ;

_tok_id      : TOK_ID      { $$ = yylval.string_val; } ;
_tok_sect_id : TOK_SECT_ID { $$ = yylval.string_val; } ;

_tok_num     : TOK_HEX | TOK_DEC ;

%%
