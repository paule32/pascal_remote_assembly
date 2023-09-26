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
extern std::function< void( UINT ) > kernel32_ExitProcess;
