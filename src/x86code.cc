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

void Parser::ASM_Code::MyErrorHandler::handleError(
    Error err,
    const char* message,
    BaseEmitter* origin) {
    std::cerr << _("AsmJit error: ") << message << std::endl;
}

// -----------------------------------------------------------------
// prepare/init entry point function ...
// -----------------------------------------------------------------
void Parser::initialize()
{
    // -------------------------------------------------------------
    // Windows 32-Bit API ...
    // -------------------------------------------------------------
    asm_code = new ASM_Code();
    asm_code->init_win32api();
    
    asm_code->code_end     ();
    asm_code->code_display ();
    asm_code->code_exec    ();
}

// -----------------------------------------------------------------
// finish-up the output code creation ...
// -----------------------------------------------------------------
void Parser::finalize()
{
    delete asm_code;
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
    logger = new FileLogger(logFile);
    
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
    
    // ---------------------------
    // create used sections:
    // ---------------------------
    SectionFlags flags =
    SectionFlags::kExecutable |
    SectionFlags::kReadOnly   ;
    
    Error err1 = code->newSection(&code_sec, ".text", SIZE_MAX, flags, 8);
    Error err2 = code->newSection(&data_sec, ".data", SIZE_MAX, flags, 8);
    
    if (err1) throw std::string(_("failed to create .text section."));
    if (err2) throw std::string(_("failed to create .data section."));
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
void Parser::ASM_Code::code_display()
{
    #if 0
    //String content = move(logger->content());
    //std::cout << content.data() << std::endl;
    #endif
}

// -----------------------------------------------------------------
// execute the generated assembly code ...
// -----------------------------------------------------------------
void Parser::ASM_Code::code_exec()
{
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
    rt.release(user32_MessageBox);
    fclose(logFile);
    
    if (nullptr != cc    ) delete cc;
    if (nullptr != code  ) delete code;
    if (nullptr != logger) delete logger;

    if (nullptr != myErrorHandler) delete myErrorHandler;
}

template <typename T> class Array {
public:
    T data[ T::DIM ];
    Array();
   ~Array();
   
   void addArg( const Array< T > &t1 )
   {
       std::cout << "add: object" <<
       std::endl ;
   }
};

template <typename T> Array< T >:: Array() { std::cout << "ctor" << std::endl; }
template <typename T> Array< T >::~Array() { std::cout << "dtor" << std::endl; }

struct Args {
    std::string name;
    enum {
        DIM = 10
    };
};

void temptest()
{
    cout << "..." << endl;
    
    Array< Args > valid;
    
    Array< Args > arg1;
    Array< Args > arg2;
    
    valid.addArg( arg1 );
    valid.addArg( arg2 );
    
    cout << "..." << endl;
}
