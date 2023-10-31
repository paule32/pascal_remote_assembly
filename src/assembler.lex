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

"section"   { return TOK_SECTION; }
"."{ident}  {
    yylval.string_val = strdup(yytext);
    return TOK_SECT_ID;
}

"call"      { return TOK_CALL;    }
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
