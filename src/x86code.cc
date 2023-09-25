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
    Features = CpuInfo::host().features();
    uint64_t baseAddress = uint64_t(0x1974);
    
    code.init(env,Features,baseAddress);
    code.setLogger(&logger);

    formatFlags =
    FormatFlags::kHexImms    |
    FormatFlags::kHexOffsets |
    FormatFlags::kExplainImms;
    
    logger.setFlags(formatFlags);
    
    FormatIndentationGroup indent;
    logger.setIndentation( indent, 4 );
}

// -----------------------------------------------------------------
// finish-up the output code creation ...
// -----------------------------------------------------------------
void Parser::finalize()
{
    cc.ret();
    cc.endFunc();
    
    cc.finalize();
    
    String content = move(logger.content());
    cout << content.data() << endl;
    
    void *__func = nullptr;
    rt.add(&__func, &code);
}
