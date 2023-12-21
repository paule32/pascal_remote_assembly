// -----------------------------------------------------------------
// File:   TurboDBASEoutputWindow.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------

# include "TurboDBASEoutputChild.h"
# include "TurboDBASEoutputWindow.h"

TdBaseOutputWindow::~TdBaseOutputWindow() { }
TdBaseOutputWindow::TdBaseOutputWindow(const TRect& bounds):
    TWindowInit(&TdBaseOutputWindow::initFrame),
    TDialog(bounds, "Output Window") {
    //palette = dpGreenDialog;

    insert(hScrollBar_2 = new TScrollBar( TRect( 19, size.y - 1, size.x - 1, size.y ) ));
    insert(vScrollBar_2 = new TScrollBar( TRect( size.x - 2, size.y - 1, size.x - 1, size.y) ));
    insert(indicator_2  = new TIndicator( TRect( 2, size.y - 1, 13, size.y) ));
    insert(editor = new TdBaseOutputWindowChild(this,
        TRect(2, 10, size.x - 3, size.y - 1),
        hScrollBar_1,
        vScrollBar_1,
        indicator_1,
        "www.txt"));
    insert(editor);
}
    
void TdBaseOutputWindow::handleEvent(TEvent & event )
{
    TWindow::handleEvent( event );
    if (event.what == evCommand) {
        switch (event.message.command) {
            case cmClose:
                close();
                clearEvent(event);
                break;
        }
    }
}
