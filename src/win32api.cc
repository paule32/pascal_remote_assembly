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
void Parser::init_win32api()
{
    kernel32_ExitProcess = &win32api::kernel32::ExitProcess;
    
    user32_MessageBox    = &win32api::user32::MessageBox;
}

win32_kernel32_ExitProcess kernel32_ExitProcess;

win32_user32_MessageBox user32_MessageBox;