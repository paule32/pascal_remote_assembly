// -----------------------------------------------------------------
// File:   x86code.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>

// -----------------------------------------------------------------
// c++ header stuff
// -----------------------------------------------------------------
# include <iostream>
# include <fstream>

// -----------------------------------------------------------------
// x86 remote assembly header
// -----------------------------------------------------------------
# include "x86.h"

# include "Parser.h"
# include "windows.h"

// -----------------------------------------------------------------
// used global namespace's ...
// -----------------------------------------------------------------
using namespace asmjit;
using namespace x86;
using namespace std;

extern void temptest();

// -----------------------------------------------------------------
// prepare/init entry point function ...
// -----------------------------------------------------------------
void Parser::initialize()
{
    // -------------------------------------------------------------
    // Windows 32-Bit API ...
    // -------------------------------------------------------------
    asm_code->init_win32api();
    
    asm_code->code_end   ();
    asm_code->code_write ();
    asm_code->code_exec  ();
}

// -----------------------------------------------------------------
// finish-up the output code creation ...
// -----------------------------------------------------------------
void Parser::finalize()
{
    std::cout << "done." << std::endl;
}

// -----------------------------------------------------------------
// constructor for assembly code ...
// -----------------------------------------------------------------
Parser::ASM_Code::ASM_Code()
{
    env      = Environment::host();
    features = CpuInfo::host().features();
    
    uint64_t baseAddress = uint64_t(0x1974);
    
    // todo:
    if (!(logFile = fopen("test.asm","w")))
    throw std::string(_(".asm output file could not be created."));

    myErrorHandler = new MyErrorHandler();

    code   = new CodeHolder();
    logger = new StringLogger();
    
    code->init(env, features, baseAddress);
    code->setErrorHandler(myErrorHandler);
    code->setLogger(logger);
    
    cc = new x86::Compiler(code);

    formatFlags =
    FormatFlags::kHexImms    |
    FormatFlags::kHexOffsets |
    FormatFlags::kExplainImms;
    
    logger->setFlags(formatFlags);
    
    FormatIndentationGroup indent;
    logger->setIndentation( indent, 4 );
    
    code_sec  = code->textSection();
    Error err = code->newSection(&data_sec,
        ".data",                // section name
        SIZE_MAX,               // name length
        SectionFlags::kNone,    // section flags
        8,                      // alignment
        0);                     // order, default: 0

    if (err) throw std::string(_("failed to create .data section."));
}

// -----------------------------------------------------------------
// just finalize the "code" emitter.
// -----------------------------------------------------------------
void Parser::ASM_Code::code_end()
{
    cc->finalize();
}

// -----------------------------------------------------------------
// get source content, and display it ...
// -----------------------------------------------------------------
void Parser::ASM_Code::code_write()
{
    asmjit::String content = std::move( logger->content() );
    fprintf( logFile,"%s\n", content.data() );
}

// -----------------------------------------------------------------
// execute the generated assembly code ...
// -----------------------------------------------------------------
void Parser::ASM_Code::code_exec()
{
    std::cout << FuncTableStream.str() << std::endl;
    fprintf(logFile,FuncTableStream.str().c_str());
    fclose (logFile);
    
    // -----------------------------------------
    // shrink runtime ...
    // -----------------------------------------
    rt.release(user32_MessageBox);
    
    // -----------------------------------------
    // if any error - inform the user ...
    // -----------------------------------------
    typedef void (*Func)();
    Func fun;
    Error err = rt.add(&fun, code);
    
    if (err != kErrorOk)
    throw std::string(_("add function fail."));

    fun();
}

// -----------------------------------------------------------------
// destructor for assembly code ...
// -----------------------------------------------------------------
Parser::ASM_Code::~ASM_Code()
{
    if (nullptr != parser->asm_code->cc    ) delete parser->asm_code->cc;
    if (nullptr != parser->asm_code->code  ) delete parser->asm_code->code;
    if (nullptr != parser->asm_code->logger) delete parser->asm_code->logger;

    if (nullptr != parser->asm_code->myErrorHandler)
       delete      parser->asm_code->myErrorHandler;
}
