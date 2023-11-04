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
# include <libintl.h>
# include <locale.h>

# include <iostream>
# include <sstream>
# include <cstring>
# include <string>
# include <algorithm>
# include <vector>
# include <map>

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
std::vector< std::string      > section_vector;   // section
std::map   < std::string, int > address_map;      // map string to address

std::stringstream  output_stream;         // code
std::stringstream  output_stream_labels;  // label's

std::stringstream  ts2,ts3;
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

%token TOK_R0Q  TOK_R1Q  TOK_R2Q   TOK_R3Q   TOK_R4Q   TOK_R5Q   TOK_R6Q   TOK_R7Q
%token TOK_R8Q  TOK_R9Q  TOK_R10Q  TOK_R11Q  TOK_R12Q  TOK_R13Q  TOK_R14Q  TOK_R15Q

%token TOK_R0D TOK_R1D TOK_R2D  TOK_R3D  TOK_R4D  TOK_R5D  TOK_R6D  TOK_R7D
%token TOK_R8D TOK_R9D TOK_R10D TOK_R11D TOK_R12D TOK_R13D TOK_R14D TOK_R15D

%token TOK_R0W TOK_R1W TOK_R2W  TOK_R3W  TOK_R4W  TOK_R5W  TOK_R6W  TOK_R7W
%token TOK_R8W TOK_R9W TOK_R10W TOK_R11W TOK_R12W TOK_R13W TOK_R14W TOK_R15W

%token TOK_R0B TOK_R1B TOK_R2B  TOK_R3B  TOK_R4B  TOK_R5B  TOK_R6B  TOK_R7B
%token TOK_R8B TOK_R9B TOK_R10B TOK_R11B TOK_R12B TOK_R13B TOK_R14B TOK_R15B


%token TOK_R0B8  TOK_R1B8  TOK_R2B8   TOK_R3B8

%token <string_val> TOK_LABEL
%type  <string_val> _tok_id  _tok_sect_id
%type  <string_val> _tok_num _tok_reg _tok_mem

%type  <string_val> _tok_reg64 _tok_reg32 _tok_reg16 _tok_reg8h _tok_reg8l

%type  <string_val> _reg64 _reg32 _reg16 _reg8h _reg8l

%type  <string_val> _tok_imm32
%type  <string_val> _mem_ptr       __mem_ptr

%type  <string_val> _mem_ptr_byte
%type  <string_val> _mem_ptr_word
%type  <string_val> _mem_ptr_dword
%type  <string_val> _mem_ptr_qword

%type  <string_val> TOK_QWORD TOK_DWORD TOK_WORD TOK_BYTE

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
           
        ss << "\tLabel lbl_"  << str << " = a.newNamedLabel("
           << "\""            << str << "\", SIZE_MAX);"
           << std::endl
           << "\tif (err) yyerror(err_lbl.c_str());"
           << std::endl;
        output_stream_labels << ss.str();
        
        // ---------------------------------------
        // check, if label is data or funcall ...
        // ---------------------------------------
        std::stringstream fun;
        fun << "Fc_" << str;
        ss  << std::endl;
        
        if (address_map.find( fun.str() ) != address_map.end()) {
            address_map[ fun.str() ] = 0;
            // -----------------------------------
            // if found, then bind ...
            // -----------------------------------
            ss.str(std::string(""));
            ss << "\terr = a.bind(lbl_" << str << ");"
               << std::endl << "\tif (err) yyerror(err_lbl.c_str());"
               << std::endl;
        }   else {
            // -----------------------------------
            // else, add it ...
            // -----------------------------------
            ss.str(std::string(""));
            std::stringstream s2;
            
            s2  << std::endl << "\terr = a.bind(lbl_" << str << ");"
                << std::endl << "\tif (err) yyerror(err_lbl.c_str());"
                << std::endl ;
                
            output_stream << s2.str();
        }   output_stream << ss.str();
    }
    | _tok_ddata
    | TOK_ADC {
    }
    | TOK_ADD {
    }
    | TOK_MOV   _tok_reg ',' _tok_reg  {
        std::stringstream ss;
        std::string str = $4;
        
        ss << "\tx86::mov("
           << $2 << ','
           << str
           << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_MOV   _tok_mem ',' _tok_reg  {
        std::stringstream ss;
        std::string str = $4;
        
        ss << "\tx86::mov("
           << $2 << ','
           << str
           << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_MOV   _tok_reg ',' _tok_mem  {
        std::stringstream ss;
        std::string str = $4;
        
        ss << "\tx86::mov("
           << $2 << ','
           << str
           << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_MOV   _tok_reg ',' _tok_imm32   {
        std::stringstream ss;
        std::string str = $4;
        std::cout << "// imm32: " << str << std::endl;
        ss << "\tx86::mov("
           << $2 << ','
           << str
           << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_MOV   _tok_reg ',' _tok_id {
        std::stringstream ss;
        std::string str = $4;
        
        if (str.empty())
        yyerror(gettext("string is empty"));
           
        ss << "\tx86::mov("
           << $2 << ','
           << str
           << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_POP   _tok_reg {
        std::stringstream ss;
        std::string str = $2;
        
        ss << "\tx86::pop("
           << str
           << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_PUSH  _tok_reg {
        std::stringstream ss;
        ss << "\tx86::push(" << $2 << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_RET {
        std::stringstream ss;
        ss << "\tx86::ret();" << std::endl;
        output_stream << ss.str();
    }
    | TOK_SUB   _tok_reg ',' _tok_num {
        std::stringstream ss;
        ss << "\tx86::sub(" << $2 << "," << $4 << ");"
           << std::endl;
        output_stream << ss.str();
    }
    | TOK_CALL  _tok_id {
        std::stringstream ss;
        std::string str = $2;
        
        if (str.empty())
        yyerror(gettext("string is empty"));
        
        ss << "\tx86::call("
           << str
           << ");"
           << std::endl;
        output_stream << ss.str();
    }
    ;
    
_tok_reg
    : _tok_reg64 { $$ = $1; }
    | _tok_reg32 { $$ = $1; }
    | _tok_reg16 { $$ = $1; }
    | _tok_reg8h { $$ = $1; }
    | _tok_reg8l { $$ = $1; }
    ;
    
_tok_reg64
    : TOK_RAX  { $$ = strdup("x86::rax"); }
    | TOK_RBX  { $$ = strdup("x86::rbx"); }
    | TOK_RCX  { $$ = strdup("x86::rcx"); }
    | TOK_RDX  { $$ = strdup("x86::rdx"); }
    | TOK_RSI  { $$ = strdup("x86::rsi"); }
    | TOK_RDI  { $$ = strdup("x86::rdi"); }
    | TOK_RBP  { $$ = strdup("x86::rbp"); }
    | TOK_RSP  { $$ = strdup("x86::rsp"); } | _reg64 { $$ = $1; }
    ;

_tok_reg32
    : TOK_EAX  { $$ = strdup("x86::eax"); }
    | TOK_EBX  { $$ = strdup("x86::ebx"); }
    | TOK_ECX  { $$ = strdup("x86::ecx"); }
    | TOK_EDX  { $$ = strdup("x86::edx"); }
    | TOK_ESI  { $$ = strdup("x86::esi"); }
    | TOK_EDI  { $$ = strdup("x86::edi"); }
    | TOK_EBP  { $$ = strdup("x86::ebp"); }
    | TOK_ESP  { $$ = strdup("x86::esp"); } | _reg32 { $$ = $1; }
    ;

_tok_reg16
    : TOK_AX   { $$ = strdup("x86::ax");  }
    | TOK_BX   { $$ = strdup("x86::bx");  }
    | TOK_CX   { $$ = strdup("x86::cx");  }
    | TOK_DX   { $$ = strdup("x86::dx");  }
    | TOK_SI   { $$ = strdup("x86::si");  }
    | TOK_DI   { $$ = strdup("x86::di");  }
    | TOK_BP   { $$ = strdup("x86::bp");  }
    | TOK_SP   { $$ = strdup("x86::sp");  } | _reg16 { $$ = $1; }
    ;

_tok_reg8h
    : TOK_AH   { $$ = strdup("x86::ah"); } 
    | TOK_BH   { $$ = strdup("x86::bh"); } 
    | TOK_CH   { $$ = strdup("x86::ch"); } 
    | TOK_DH   { $$ = strdup("x86::dh"); } | _reg8h { $$ = $1; }
    ;

_tok_reg8l
    : TOK_AL   { $$ = strdup("x86::al"); } 
    | TOK_BL   { $$ = strdup("x86::bl"); } 
    | TOK_CL   { $$ = strdup("x86::cl"); } 
    | TOK_DL   { $$ = strdup("x86::dl"); } | _reg8l { $$ = $1; }
    ;
    
_reg64
    : TOK_R0   { $$ = strdup("x86::r0" ); }
    | TOK_R1   { $$ = strdup("x86::r1" ); }
    | TOK_R2   { $$ = strdup("x86::r2" ); }
    | TOK_R3   { $$ = strdup("x86::r3" ); }
    | TOK_R4   { $$ = strdup("x86::r4" ); }
    | TOK_R5   { $$ = strdup("x86::r5" ); }
    | TOK_R6   { $$ = strdup("x86::r6" ); }
    | TOK_R7   { $$ = strdup("x86::r7" ); }
    | TOK_R8   { $$ = strdup("x86::r8" ); }
    | TOK_R9   { $$ = strdup("x86::r9" ); }
    | TOK_R10  { $$ = strdup("x86::r10"); }
    | TOK_R11  { $$ = strdup("x86::r11"); }
    | TOK_R12  { $$ = strdup("x86::r12"); }
    | TOK_R13  { $$ = strdup("x86::r13"); }
    | TOK_R14  { $$ = strdup("x86::r14"); }
    | TOK_R15  { $$ = strdup("x86::r15"); } | _reg32 | _reg16 | _reg8h | _reg8l
    ;

_reg32
    : TOK_R0D  { $$ = strdup("x86::r0" ); }
    | TOK_R1D  { $$ = strdup("x86::r1" ); }
    | TOK_R2D  { $$ = strdup("x86::r2" ); }
    | TOK_R3D  { $$ = strdup("x86::r3" ); }
    | TOK_R4D  { $$ = strdup("x86::r4" ); }
    | TOK_R5D  { $$ = strdup("x86::r5" ); }
    | TOK_R6D  { $$ = strdup("x86::r6" ); }
    | TOK_R7D  { $$ = strdup("x86::r7" ); }
    | TOK_R8D  { $$ = strdup("x86::r8" ); }
    | TOK_R9D  { $$ = strdup("x86::r9" ); }
    | TOK_R10D { $$ = strdup("x86::r10"); }
    | TOK_R11D { $$ = strdup("x86::r11"); }
    | TOK_R12D { $$ = strdup("x86::r12"); }
    | TOK_R13D { $$ = strdup("x86::r13"); }
    | TOK_R14D { $$ = strdup("x86::r14"); }
    | TOK_R15D { $$ = strdup("x86::r15"); } | _reg16 | _reg8h | _reg8l
    ;
_reg16
    : TOK_R0W  { $$ = strdup("x86::r0" ); }
    | TOK_R1W  { $$ = strdup("x86::r1" ); }
    | TOK_R2W  { $$ = strdup("x86::r2" ); }
    | TOK_R3W  { $$ = strdup("x86::r3" ); }
    | TOK_R4W  { $$ = strdup("x86::r4" ); }
    | TOK_R5W  { $$ = strdup("x86::r5" ); }
    | TOK_R6W  { $$ = strdup("x86::r6" ); }
    | TOK_R7W  { $$ = strdup("x86::r7" ); }
    | TOK_R8W  { $$ = strdup("x86::r8" ); }
    | TOK_R9W  { $$ = strdup("x86::r9" ); }
    | TOK_R10W { $$ = strdup("x86::r10"); }
    | TOK_R11W { $$ = strdup("x86::r11"); }
    | TOK_R12W { $$ = strdup("x86::r12"); }
    | TOK_R13W { $$ = strdup("x86::r13"); }
    | TOK_R14W { $$ = strdup("x86::r14"); }
    | TOK_R15W { $$ = strdup("x86::r15"); } | _reg8h | _reg8l
    ;
_reg8h
    : TOK_R0B { $$ = strdup("x86::r0b" ); }
    | TOK_R1B { $$ = strdup("x86::r1b" ); }
    | TOK_R2B { $$ = strdup("x86::r2b" ); }
    | TOK_R3B { $$ = strdup("x86::r3b" ); } | _reg8l
    ;
_reg8l
    : TOK_R0B { $$ = strdup("x86::r0b" ); }
    | TOK_R1B { $$ = strdup("x86::r1b" ); }
    | TOK_R2B { $$ = strdup("x86::r2b" ); }
    | TOK_R3B { $$ = strdup("x86::r3b" ); }
    ;
    
_tok_mem
    :  _mem_ptr { $$ = $1; }
    ;

_mem_ptr
    : _mem_ptr_byte  { $$ = $1; }
    | _mem_ptr_word  { $$ = $1; }
    | _mem_ptr_dword { $$ = $1; }
    | _mem_ptr_qword { $$ = $1; }
    ;

_mem_ptr_byte
    : TOK_BYTE __mem_ptr {
        std::stringstream ss;
        ss << "x86::byte_ptr" << $2;
        $$ = strdup( ss.str().c_str());
    }
    ;
_mem_ptr_word
    : TOK_WORD __mem_ptr {
        std::stringstream ss;
        ss << "x86::word_ptr" << $2;
        $$ = strdup( ss.str().c_str());
    }
    ;

_mem_ptr_dword
    : TOK_DWORD  __mem_ptr {
        std::stringstream ss;
        ss << "x86::dword_ptr" << $2;
        $$ = strdup( ss.str().c_str());
    }
    ;
    
_mem_ptr_qword
    : TOK_QWORD __mem_ptr {
        std::stringstream ss;
        ss << "x86::qword_ptr" << $2;
        $$ = strdup( ss.str().c_str());
    }
    ;

__mem_ptr
    : '[' _tok_reg '+' _tok_num ']' {
        std::stringstream ss;
        ss << "("      << $2 << ", "
           << std::hex << $4
           << std::dec << ")";
        $$ = strdup(ss.str().c_str());
    }
    ;

_tok_imm32
    : _tok_num { $$ = $1; }
    ;

_tok_id      : TOK_ID      { $$ = yylval.string_val; } ;
_tok_sect_id : TOK_SECT_ID { $$ = yylval.string_val; } ;

_tok_num
    : TOK_HEX { $$ = yylval.string_val; }
    | TOK_DEC { $$ = yylval.string_val; }
    ;

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
