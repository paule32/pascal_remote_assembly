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
            return ::MessageBoxA(hwnd,lpText,lpCaption,uType);
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
    code_end();
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
        std::string LS("MessageBoxA");
        Label L1 = cc->newNamedLabel(LS.data(), LS.length(),
        LabelType::kGlobal);

        cc->bind(L1);

        // -----------------------------------------
        // setup the signature of: MessageBoxA
        // -----------------------------------------
        FuncSignatureBuilder signature(CallConvId::kHost);
        signature.setRetT< int >();
            signature.addArgT< HWND    >();
            signature.addArgT< LPCTSTR >();
            signature.addArgT< LPCTSTR >();
            signature.addArgT< UINT    >();

        // -----------------------------------------
        // add a new member function to asmjit code
        // -----------------------------------------
        FuncNode* funcNode = cc->addFunc(signature);
        funcNode->frame().setPreservedFP();
        
        // setup stack:
        x86::Mem stack = cc->newStack(102400, 102400);

        //  HWND
        {
            x86::Gp gpArg = cc->newIntPtr("gpArg1");
            funcNode->setArg(0, gpArg);
            cc->push(gpArg);
        }
        //  LPCTSTR
        {
            x86::Gp gpArg = cc->newIntPtr("gpArg2");
            funcNode->setArg(0, gpArg);
            cc->push(gpArg);
        }
        //  LPCTSTR
        {
            x86::Gp gpArg = cc->newIntPtr("gpArg3");
            funcNode->setArg(2, gpArg);
            cc->push(gpArg);
        }
        //  UINT
        {
            x86::Gp gpArg = cc->newIntPtr("gpArg4");
            funcNode->setArg(3, gpArg);
            cc->push(gpArg);
        }
        
        // -----------------------------------------
        // call the hook win32api member ...
        // -----------------------------------------
        cc->call(user32_MessageBox);
        
        cc->ret();
        cc->endFunc();
        
        // if the line below commented, then rt.add throws - why ?
        // I think, "finalize" is the last step of code generation ?
        // or mark finalize the end of generation, and as such, I
        // can not "call" partial code ... ?
        cc->finalize();

        // -----------------------------------------
        // if any error - inform the user ...
        // -----------------------------------------
        win32_user32_MessageBox func;
        Error err = rt.add(&func, code);
        if (err != kErrorOk)
        throw std::string(_("add function fail."));

        func(0,"hallo","dudu",0);
        return true;
    }
    catch (std::string &ex) {
        std::cout << ex << std::endl;
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
