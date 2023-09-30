// -----------------------------------------------------------------
// @file:   win32api.cc
// @author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// @copyright only for education, and non-profit usage !
// -----------------------------------------------------------------
# include "Parser.h"
# include "windows.h"

// -----------------------------------------------------------------
// win32api -> kernel32.dll -> void ExitProcess( UINT exitcode);
// -----------------------------------------------------------------
namespace win32api
{
    namespace kernel32
    {
        void ExitProcess(UINT exitcode) {
            std::cout << "internal proc" << std::endl;
            ::ExitProcess( exitcode );
        }
    }   // kernel32 namespace
    
    namespace user32
    {
        int MessageBox(
            HWND    hwnd,
            LPCTSTR lpText,
            LPCTSTR lpCaption,
            UINT    uType) {
            std::cout << "messageBox" << std::endl;
            std::cout << lpText << std::endl;
            std::cout << lpCaption << std::endl;
            char * t1 = strdup(lpText);
            char * t2 = strdup(lpCaption);
            ::MessageBoxA(0, t1, t2, 0);
            return 0;
        }
    }   // user32   namespace
}       // win32api namespace

// -----------------------------------------------------------------
// pre-pare collected win32api member functions ...
// -----------------------------------------------------------------
void Parser::ASM_Code::init_win32api()
{
    // -----------------------------------------
    // win32api: kernel32.dll
    // -----------------------------------------
    kernel32_ExitProcess = &win32api::kernel32::ExitProcess;
    
    // -----------------------------------------
    // win32api: user32.dll
    // -----------------------------------------
    user32_MessageBox    = &win32api::user32::MessageBox;
    
    // -----------------------------------------
    // add win32api user32.dll member func code
    // -----------------------------------------
    code_user32_MessageBoxA();
}

// -----------------------------------------------------------------
// win32api: kernel32.dll hooks ...
// -----------------------------------------------------------------
win32_kernel32_ExitProcess kernel32_ExitProcess;

// -----------------------------------------------------------------
// win32api: user32.dll hooks:
// -----------------------------------------------------------------
win32_user32_MessageBox user32_MessageBox;

// -----------------------------------------------------------------
// generator member: MessageBoxA - ANSI
// -----------------------------------------------------------------
bool Parser::ASM_Code::code_user32_MessageBoxA()
{
    try {
        // -----------------------------------------
        // win32api: MessageBoxA
        // -----------------------------------------
        std::string S0("EntryPoint");
        std::string S1("MessageBoxA");
        std::string S2("Ldata_0");
        
        Label L0 = cc->newNamedLabel(S0.data(), S0.length(), LabelType::kGlobal);
        Label L1 = cc->newNamedLabel(S1.data(), S1.length(), LabelType::kGlobal);
        Label L2 = cc->newNamedLabel(S2.data(), S2.length(), LabelType::kGlobal);
        
        // -----------------------------------------
        // .text EntryPoint
        // -----------------------------------------
        cc->section(code_sec);
        cc->bind(L0);

        // -----------------------------------------
        // setup the signature of: MessageBoxA
        // -----------------------------------------
        FuncSignatureBuilder signature(CallConvId::kHost);
        signature.setRetT< void >();
        
        signature.addArgT< HWND    >();
        signature.addArgT< LPCTSTR >();
        signature.addArgT< LPCTSTR >();
        signature.addArgT< UINT    >();
        
        x86::Gp gpArg1 = cc->newInt64("gpArg1");
        x86::Gp gpArg2 = cc->newInt64("gpArg2");
        x86::Gp gpArg3 = cc->newInt64("gpArg3");
        x86::Gp gpArg4 = cc->newInt64("gpArg4");

        FuncNode* funcNode = cc->addFunc(signature);
        funcNode->frame().setPreservedFP();
        
        funcNode->setArg(0, gpArg1);
        funcNode->setArg(1, gpArg2);
        funcNode->setArg(2, gpArg3);
        funcNode->setArg(3, gpArg4);

        // -----------------------------------------
        // call the hook win32api member ...
        // -----------------------------------------
        cc->lea(gpArg2, x86::ptr(L2));
        
        InvokeNode * invokeNode;
        cc->invoke(& invokeNode,
            imm((void*)user32_MessageBox),
            signature);
        
        HWND hwnd = (HWND)0;
        LPCSTR s3 = "Hallo Welt !!!";
        LPCSTR s4 = "info";
        UINT   mt = 0;
        
        invokeNode->setArg(0, hwnd);
        invokeNode->setArg(1, gpArg2);
        invokeNode->setArg(2, s4);
        invokeNode->setArg(3, mt);

        cc->ret();
        cc->endFunc();
        
        // test:
        cc->section(data_sec);
        cc->bind(L2);
        
        std::string s1("Hello World !\0");
        cc->embed(s1.c_str(), s1.length()+1);

        return true;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (...) {
        std::stringstream ss;
        ss  << _("Runtime add: ")
            << "MessageBoxA"  << std::endl
            << _("fail.");
        std::cout << ss.str() << std::endl;
    }
    
    return false;
}
