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

// -----------------------------------------------------------------
// prepare/init entry point function ...
// -----------------------------------------------------------------
void Parser::initialize()
{
    env      = Environment::host();
    features = CpuInfo::host().features();
    uint64_t baseAddress = uint64_t(0x1974);
    
    code   = new CodeHolder();
    logger = new StringLogger();
    
    code->init(env, features, baseAddress);
    code->setLogger(logger);
    
    cc = new x86::Compiler(code);

    formatFlags =
    FormatFlags::kHexImms    |
    FormatFlags::kHexOffsets |
    FormatFlags::kExplainImms;
    
    logger->setFlags(formatFlags);
    
    FormatIndentationGroup indent;
    logger->setIndentation( indent, 4 );
    
    // -------------------------------------------------------------
    // Windows 32-Bit API ...
    // -------------------------------------------------------------
    init_win32api();
}

// -----------------------------------------------------------------
// finish-up the output code creation ...
// -----------------------------------------------------------------
void Parser::finalize()
{
    {
        cc->addFunc(FuncSignatureT<int,
            HWND    ,
            LPCTSTR ,
            LPCTSTR ,
            UINT    >());
        
        x86::Gp hwnd      = cc->newIntPtr("hwnd");
        x86::Gp lpText    = cc->newIntPtr("lpText");
        x86::Gp lpCaption = cc->newIntPtr("lpCaption");
        x86::Gp uType     = cc->newIntPtr("uType");
        
        cc->push(uType);
        cc->push(lpCaption);
        cc->push(lpText);
        cc->push(hwnd);
        
        cc->call(user32_MessageBox);
        
        cc->ret();
        cc->endFunc();
        cc->finalize();

        String content = move(logger->content());
        cout << content.data() << endl;
        
        typedef int (*Func)(
            HWND    ,
            LPCTSTR ,
            LPCTSTR ,
            UINT    );
        Func fn;
        Error err = rt.add(&fn, code);
        
        if (err)
        std::cout << _("asmjit add function fail.") << std::endl;
    
        fn(0,"tutu","tatata",0);
        rt.release(fn);
    }
    
    {
        cc->addFunc(FuncSignatureT<int>());
        cc->call(kernel32_ExitProcess);
        cc->ret();
        cc->endFunc();
        cc->finalize();
        
        String content = move(logger->content());
        cout << "contents: " << endl << content.data() << endl;
        
        typedef void (*Func)(void);
        Func fn;
        Error err = rt.add(&fn, code);
        if (err) std::cout << "error111" << std::endl;
        fn();
    }

    {
        Label L_Enter = cc->newLabel();
        Label L_Exit  = cc->newLabel();

        cc->addFunc(FuncSignatureT<void, uint32_t>());
        
        x86::Gp addr  = cc->newInt32("addr");
        
        cc->test(addr,addr);
        cc->jz(L_Exit);
        
        cc->bind(L_Enter);
        
        x86::Gp  tmp = cc->newInt32("tmp");
        cc->mov (tmp, x86::dword_ptr(addr)); 
        cc->call(tmp);
        
        cc->bind(L_Exit);
    }
    cc->endFunc();
    
    cc->finalize();
    
    String content = move(logger->content());
    cout << "contents: " << endl << content.data() << endl;

    std::cout << "exec:" << std::endl;

    typedef void (*Func)(void);
    Func fn;
    err = rt.add(&fn, code);
    if (err) std::cout << "error" << std::endl;
    fn();
    
    std::cout << "done." << std::endl;
}
