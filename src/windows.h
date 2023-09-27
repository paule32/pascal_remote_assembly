// -----------------------------------------------------------------
// File:   windows.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# pragma once

# include "Parser.h"

// -----------------------------------------------------------------
// win32api kernel32.dll calls ...
// -----------------------------------------------------------------
namespace win32api
{
    namespace kernel32
    {
        void ExitProcess(UINT exitcode);
    }   // kernel32 namespace
    
    namespace user32
    {
        int MessageBox(
            HWND    hwnd,
            LPCTSTR lpText,
            LPCTSTR lpCaption,
            UINT    uType);
            
    }   // user32   namespace
}       // win32api namespace

typedef void (*win32_kernel32_ExitProcess)(
    UINT );
    extern win32_kernel32_ExitProcess kernel32_ExitProcess;
    
typedef int  (*win32_user32_MessageBox)(
    HWND,
    LPCTSTR,
    LPCTSTR,
    UINT );
    extern win32_user32_MessageBox user32_MessageBox;
