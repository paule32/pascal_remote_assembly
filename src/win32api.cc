// -----------------------------------------------------------------
// @file:   win32api.cc
// @author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// @copyright only for education, and non-profit usage !
// -----------------------------------------------------------------

// -----------------------------------------------------------------
// win32api -> kernel32.dll -> void ExitProcess( UINT exitcode);
// -----------------------------------------------------------------
std::function< void( UINT ) > kernel32_ExitProcess;
