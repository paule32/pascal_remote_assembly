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

# include <iostream>
# include <fstream>

# include "x86.h"

using namespace asmjit;
using namespace x86;
using namespace std;

void create_output()
{
    JitRuntime       rt;  // Runtime specialized for JIT code excution
    CodeHolder     code;  // Holds the code and relocation information
    StringLogger logger;
    
    Error err = kErrorOk;
    
    code.init(rt.environment());
        
    code.setLogger(&logger);
    
    FormatFlags formatFlags =
    FormatFlags::kHexImms    |
    FormatFlags::kHexOffsets |
    FormatFlags::kExplainImms;
    
    logger.setFlags(formatFlags);
    
    FormatIndentationGroup indent;
    logger.setIndentation( indent, 4 );

    x86::Compiler cc(&code);
    
    cc.ret();
    cc.endFunc();
    
    cc.finalize();
    
    String content = move(logger.content());
    cout << content.data() << endl;
    
    void *__func = nullptr;
    rt.add(&__func, &code);

}
