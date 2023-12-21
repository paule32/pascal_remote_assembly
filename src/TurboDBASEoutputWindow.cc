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
    "\x75\x75\x75\x73\x74\x75\x76\x77\x75\x74\x7a\x7b\x74\x75\x12\x6f"\
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"

TdBaseOutputWindow::~TdBaseOutputWindow() { }
TdBaseOutputWindow::TdBaseOutputWindow(const TRect& bounds):
    TWindowInit(&TdBaseOutputWindow::initFrame),
    TDialog(bounds, "Output Window") {
    
    std::string textBuffer = "\x1FText in blau.\x1E\n\x1AText in rot.\x1E\n\x19Text in grün.\x1E";
    createDrawBuffer(textBuffer);
}

// --------------------------------
// fill background: black on white
// --------------------------------
void TdBaseOutputWindow::draw()
{
    TDialog::draw();
    writeLine( 1, 1, size.x-1, size.y-1, drawBuffer);
    
}

void TdBaseOutputWindow::createDrawBuffer(const std::string &text)
{
    int x = 0, y = 0;
    for (char ch : text) {
        if (ch == '\n') {
            x = 0;
            y++;
        } else {
            drawBuffer.moveChar(x, y, ch, getColor(ch));
            x++;
        }
    }
}

ushort TdBaseOutputWindow::getColor(char ch)
{
    switch (ch)
    {
        case '\x1F': return 0x0001;  // Blau
        case '\x1A': return 0x0004;  // Rot
        case '\x1E': return 0x0002;  // Grün
        default: return 0x000F;      // Weiß (Standardfarbe)
    }
}

void TdBaseOutputWindow::handleEvent(TEvent & event )
{
    TDialog::handleEvent( event );
    if (event.what == evKeyDown) {
        drawView();
    }   else
    if (event.what == evCommand) {
        switch (event.message.command) {
            case cmClose:
                close();
                clearEvent(event);
            break;
        }
    }
}

// --------------------------------------------------
// set the "green" style, depend on the palette items
// --------------------------------------------------
TPalette& TdBaseOutputWindow::getPalette() const {
    static TPalette palette( cpGreenDialog, sizeof(cpGreenDialog)-1 );
    return palette;
}
