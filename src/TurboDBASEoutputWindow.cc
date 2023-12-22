// -----------------------------------------------------------------
// File:   TurboDBASEoutputWindow.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------

# include "TurboDBASEoutputChild.h"
# include "TurboDBASEoutputWindow.h"

#define cpGreenDialog \
    "\x75\x75\x75\x73\x74\x75\x76\x77\x75\x74\x7a\x7b\x74\x75\x02\x10"\
    "\x0f\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x70"

TdBaseOutputWindow::~TdBaseOutputWindow() { }
TdBaseOutputWindow::TdBaseOutputWindow(const TRect& bounds):
    TWindowInit(&TdBaseOutputWindow::initFrame),
    TDialog(bounds, "Output Window") {
    
    insert(commandView = new TdBaseOutputWindowChild(this,
    TRect(1, 1, size.x-1, size.y-1)));
}

// --------------------------------------------------
// set the "green" style, depend on the palette items
// --------------------------------------------------
TPalette& TdBaseOutputWindow::getPalette() const {
    static TPalette palette( cpGreenDialog, sizeof(cpGreenDialog)-1 );
    return palette;
}
