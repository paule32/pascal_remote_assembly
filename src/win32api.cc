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

void calledProc(HWND h, LPCTSTR t1, LPCTSTR t2, UINT m) {
    std::cout << "-------------------" << std::endl;
    ::MessageBoxA(h,t1,t2,m);
}
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
        // signature of: EntryPoint
        // -----------------------------------------
        FuncNode * mainFunc = cc->newFunc(
        FuncSignatureT<void,void >(CallConvId::kHost));
        mainFunc->frame().setPreservedFP();

        // -----------------------------------------
        // signature of: MessageBoxA
        // -----------------------------------------
        FuncNode * messageBoxA = cc->newFunc(
        FuncSignatureT<int, HWND, LPCTSTR, LPCTSTR, UINT>(CallConvId::kHost));
        messageBoxA->frame().setPreservedFP();

        {
            // -----------------------------------------
            // .text EntryPoint
            // -----------------------------------------
            cc->section(code_sec);
            cc->bind(L0);
            cc->addFunc(mainFunc);
            
            size_t i;

            x86::Mem stack = cc->newStack(8, 1, "stack");        
            
            InvokeNode * invokeNode;
            cc->invoke(& invokeNode,
                messageBoxA->label(),
                FuncSignatureT<void, HWND, LPCTSTR, LPCTSTR, UINT>(
                CallConvId::kX64Windows));

            cc->ret();
            cc->endFunc();
        }
        {
            // -----------------------------------------
            // .text MessageBoxA
            // -----------------------------------------
            cc->section(code_sec);
            cc->bind(L1);
            cc->addFunc(messageBoxA);

            //x86::Mem gpArg1 = cc->newInt64Const(ConstPoolScope::kLocal,42);
            
            x86::Gp gpArg1 = cc->newInt64("gpArg1");
            x86::Gp gpArg2 = cc->newInt64("gpArg2");
            x86::Gp gpArg3 = cc->newInt64("gpArg3");
            x86::Gp gpArg4 = cc->newInt64("gpArg4");

            // -----------------------------------------
            // call the hook win32api member ...
            // -----------------------------------------
            HWND hwnd = (HWND)0;
            LPCSTR s3 = "Hallo Welt !!!";
            LPCSTR s4 = "info";
            UINT   mt = 0;

            InvokeNode * invokeNode;
            cc->invoke(& invokeNode,
                imm((void*)calledProc),
                FuncSignatureT<void, HWND, LPCTSTR, LPCTSTR, UINT>(
                CallConvId::kX64Windows));
            invokeNode->setArg(0, hwnd);
            invokeNode->setArg(1, s3);
            invokeNode->setArg(2, s4);
            invokeNode->setArg(3, mt);

            cc->ret(gpArg4);
            cc->endFunc();
            
            // test:
            cc->section(data_sec);
            cc->bind(L2);
            
            std::string s1("Hello World !aaaa!\0");
            cc->embed(s1.c_str(), s1.length()+1);
        }

        return true;
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (std::string &e) {
        std::stringstream ss;
        ss  << _("Runtime add: ")
            << "MessageBoxA  "
            << _("fail.")      << std::endl
            << _("Error: ")
            << e               << std::endl;
        std::cout << ss.str()  << std::endl;
    }
    
    return false;
}
