// -----------------------------------------------------------------
// File:   ErrorHandler.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include "Parser.h"

using namespace asmjit;
using namespace asmjit::x86;

void MyErrorHandler::handleError(
    Error err,
    const char* message,
    BaseEmitter* origin) {
    std::cerr << _("AsmJit error: ") << message << std::endl;
}
