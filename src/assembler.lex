%{
// -----------------------------------------------------------------
// File:   Assembler.ll
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <windows.h>

# include <stdio.h>
# include <libintl.h>
# include <locale.h>
# include <stdlib.h>
# include <strings.h>

# include <iostream>
# include <sstream>
# include <cstring>
# include <string>
# include <algorithm>

# include "Parser.h"

extern "C" {
    # include "AssemblerParser.hh"
    int  line=1,column=1;

    int  yylex   (void );

    int  yywrap  (void     ) { return 1; }
    void yyerror (const char * msg) {
        std::cerr << "error: " << line << ": " << msg << std::endl;
        exit(1);
    }
};

# define _(String) gettext(String)

extern std::stringstream output_stream;

%}

ident       [a-zA-Z_][a-zA-Z0-9_]*
hexdigit    (0[xX])?[a-fA-F0-9]*
decdigit    [0..9]*

%x NEW_COMMENT

%%

"adc"       { return TOK_ADC;       }
"add"       { return TOK_ADD;       }
"and"       { return TOK_AND;       }

"call"      { return TOK_CALL;      }
"cmp"       { return TOK_CMP;       }

"je"        { return TOK_JE;        }
"jmp"       { return TOK_JMP;       }
"jnz"       { return TOK_JNZ;       }
"jz"        { return TOK_JZ;        }

"mov"       { return TOK_MOV;       }
"nop"       { return TOK_NOP;       }
"pop"       { return TOK_POP;       }
"push"      { return TOK_PUSH;      }
"ret"       { return TOK_RET;       }
"sub"       { return TOK_SUB;       }

"ptr"       { return TOK_PTR;       }
"byte"      { return TOK_BYTE;      }
"word"      { return TOK_WORD;      }
"dword"     { return TOK_DWORD;     }
"qword"     { return TOK_QWORD;     }

"r0b"       { return TOK_R0B;       }
"r1b"       { return TOK_R1B;       }
"r2b"       { return TOK_R2B;       }
"r3b"       { return TOK_R3B;       }
"r4b"       { return TOK_R4B;       }
"r5b"       { return TOK_R5B;       }
"r6b"       { return TOK_R6B;       }
"r7b"       { return TOK_R7B;       }
"r8b"       { return TOK_R8B;       }
"r9b"       { return TOK_R9B;       }
"r10b"      { return TOK_R10B;      }
"r11b"      { return TOK_R11B;      }
"r12b"      { return TOK_R12B;      }
"r13b"      { return TOK_R13B;      }
"r14b"      { return TOK_R14B;      }
"r15b"      { return TOK_R15B;      }

"r0"        { return TOK_R0;        }
"r1"        { return TOK_R1;        }
"r2"        { return TOK_R2;        }
"r3"        { return TOK_R3;        }
"r4"        { return TOK_R4;        }
"r5"        { return TOK_R5;        }
"r6"        { return TOK_R6;        }
"r7"        { return TOK_R7;        }
"r8"        { return TOK_R8;        }
"r9"        { return TOK_R9;        }
"r10"       { return TOK_R10;       }
"r11"       { return TOK_R11;       }
"r12"       { return TOK_R12;       }
"r13"       { return TOK_R13;       }
"r14"       { return TOK_R14;       }
"r15"       { return TOK_R15;       }

"r0d"       { return TOK_R0D;       }
"r1d"       { return TOK_R1D;       }
"r2d"       { return TOK_R2D;       }
"r3d"       { return TOK_R3D;       }
"r4d"       { return TOK_R4D;       }
"r5d"       { return TOK_R5D;       }
"r6d"       { return TOK_R6D;       }
"r7d"       { return TOK_R7D;       }
"r8d"       { return TOK_R8D;       }
"r9d"       { return TOK_R9D;       }
"r10d"      { return TOK_R10D;      }
"r11d"      { return TOK_R11D;      }
"r12d"      { return TOK_R12D;      }
"r13d"      { return TOK_R13D;      }
"r14d"      { return TOK_R14D;      }
"r15d"      { return TOK_R15D;      }

"r0w"       { return TOK_R0W;       }
"r1w"       { return TOK_R1W;       }
"r2w"       { return TOK_R2W;       }
"r3w"       { return TOK_R3W;       }
"r4w"       { return TOK_R4W;       }
"r5w"       { return TOK_R5W;       }
"r6w"       { return TOK_R6W;       }
"r7w"       { return TOK_R7W;       }
"r8w"       { return TOK_R8W;       }
"r9w"       { return TOK_R9W;       }
"r10w"      { return TOK_R10W;      }
"r11w"      { return TOK_R11W;      }
"r12w"      { return TOK_R12W;      }
"r13w"      { return TOK_R13W;      }
"r14w"      { return TOK_R14W;      }
"r15w"      { return TOK_R15W;      }

"rax"       { return TOK_RAX;       }
"rbx"       { return TOK_RBX;       }
"rcx"       { return TOK_RCX;       }
"rdx"       { return TOK_RDX;       }
"rdi"       { return TOK_RDI;       }
"rsi"       { return TOK_RSI;       }
"rsp"       { return TOK_RSP;       }
"rbp"       { return TOK_RBP;       }

"eax"       { return TOK_EAX;       }
"ebx"       { return TOK_EBX;       }
"ecx"       { return TOK_ECX;       }
"edx"       { return TOK_EDX;       }
"edi"       { return TOK_EDI;       }
"esi"       { return TOK_ESI;       }
"esp"       { return TOK_ESP;       }
"ebp"       { return TOK_EBP;       }

"ax"        { return TOK_AX;        }
"bx"        { return TOK_BX;        }
"cx"        { return TOK_CX;        }
"dx"        { return TOK_DX;        }
"di"        { return TOK_DI;        }
"si"        { return TOK_SI;        }
"sp"        { return TOK_SP;        }
"bp"        { return TOK_BP;        }

"ah"        { return TOK_AH;        }
"bh"        { return TOK_BH;        }
"ch"        { return TOK_CH;        }
"dh"        { return TOK_DH;        }

"al"        { return TOK_AL;        }
"bl"        { return TOK_BL;        }
"cl"        { return TOK_CL;        }
"dl"        { return TOK_DL;        }


"section"   { return TOK_SECTION;   }
".section"  { return TOK_SECTION;   }

"."{ident}  {
    yylval.string_val = strdup(yytext);
    return TOK_SECT_ID;
}

{decdigit}  { return TOK_DEC;       }
{hexdigit}  { return TOK_HEX;       }

{ident}":"  {
    yylval.string_val = strdup(yytext);
    return TOK_LABEL;
}
{ident}     { return TOK_ID;      }

\{                      { column += strlen(yytext); BEGIN(NEW_COMMENT);       }
<NEW_COMMENT>\}         { column += strlen(yytext); BEGIN(INITIAL);           }
<NEW_COMMENT>\n         { column += strlen(yytext); line++; }
<NEW_COMMENT>.          { column += strlen(yytext); }

";".*                   { }

\[          { return '['; }
\]          { return ']'; }
\+          { return '+'; }
\-          { return '-'; }
\*          { return '*'; }
\,          { return ','; }

[ \t]                   { column += 1; }
(\n|\r\n)               { column  = 1; line++; }

.   {
    column += 1;
    std::stringstream ss;
    ss << _("Invalide character: ") << yytext[0];
    yyerror(ss.str().c_str());
}

<<EOF>>      {
    //std::cout << "lines: " << line << std::endl;
    yyterminate();
}
%%

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("no file given.\n");
        exit(1);
    }
    
    yyin = fopen( argv[1], "r");
    if (!yyin) {
        printf("error: file: %s could not be open.\n", argv[1]);
        exit(1);
    }

    yyparse();
    
    std::stringstream ss;
    ss << "// -------------------------------------------------------------------"                  << std::endl
       << "// AsmJIT automatically created C++ source file."                                        << std::endl
       << "// (c) 2023 kallup non-profit - Jens Kallup - paule32"                                   << std::endl
       << "// all rights reserved."                                                                 << std::endl
       << "//"                                                                                      << std::endl
       << "// only for education, and non-profit usage."                                            << std::endl
       << "// -------------------------------------------------------------------"                  << std::endl
       << "# include <stdio.h>"                                                                     << std::endl
       << "# include <stdlib.h>"                                                                    << std::endl
       << "# include <strings.h>"                                                                   << std::endl
       << "# include <libintl.h>    // localization"                                                << std::endl
                                                                                                    << std::endl
       << "# include <iostream>"                                                                    << std::endl
       << "# include <sstream>"                                                                     << std::endl
       << "# include <cstring>"                                                                     << std::endl
       << "# include <string>"                                                                      << std::endl
                                                                                                    << std::endl
       << "#include <asmjit/x86.h>"                                                                 << std::endl
       << "#include <stdio.h>"                                                                      << std::endl
                                                                                                    << std::endl
       << "using namespace asmjit;"                                                                 << std::endl
                                                                                                    << std::endl
       << "// Signature of the generated function."                                                 << std::endl
       << "typedef int (*Func)(void);"                                                              << std::endl
                                                                                                    << std::endl
       << "void yyerror(const char* msg) {"                                                         << std::endl
       << "\tstd::cout << \"error: \" << msg << std::endl;"                                         << std::endl
       << "\texit(1);"                                                                              << std::endl
       << "}"                                                                                       << std::endl
                                                                                                    << std::endl
       << "int main(int argc, char **argv)"                                                         << std::endl
       << "{"                                                                                       << std::endl
       << "\tJitRuntime rt;                     // Runtime specialized for JIT code executin."      << std::endl
       << "\tError err;"                                                                            << std::endl
                                                                                                    << std::endl
       << "\tCodeHolder code;                   // Holds code and relocation information."          << std::endl
       << "\tcode.init(rt.environment(),        // Initialize code to matchthe JIT environment."    << std::endl
       << "\t          rt.cpuFeatures());"                                                          << std::endl
                                                                                                    << std::endl
       << "\tx86::Assembler a(&code);           // Create and attach x86::Assembler to code."       << std::endl
                                                                                                    << std::endl
       << output_stream.str()
       
       << "\ta.mov(x86::eax, 2);"                                                                   << std::endl
       << "\ta.ret();"                                                                              << std::endl
       << "\t// ==== x86::Assembler is no longer needed from here, and we can destroyed ==== "      << std::endl
                                                                                                    << std::endl
       << "\tFunc fn;                           // Holds address to the generated function."        << std::endl
       << "\terr = rt.add(&fn, &code);          // Add the generated code to run"                   << std::endl
       << "\tif (err)                           // Handle a possible error returbed by asmjit."     << std::endl
       << "\tyyerror(gettext(\"failed added function\"));"                                          << std::endl
       << "\t// ==== CodeHolder is no longer needed from here, and we can destroyed ==== "          << std::endl
                                                                                                    << std::endl
       << "\tint result = fn();                 // Execute the generated code."                     << std::endl
       << "\tprintf(\"%d\\n\", result);            // Print the result."                            << std::endl
                                                                                                    << std::endl
       << "\t// All classes use RAII, all resources will be released before `main()` returns,"      << std::endl
       << "\t// the generated function can be, however, released explicitly if you intend to"       << std::endl
       << "\t// reuse or keep the runtime alive, which you should in a production-ready code."      << std::endl
       << "\trt.release(fn);"                                                                       << std::endl
                                                                                                    << std::endl
       << "\treturn EXIT_SUCCESS;"                                                                  << std::endl
       << "}"
       << std::endl;
    std::cout << ss.str();

    fclose(yyin);
}
