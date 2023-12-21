// -----------------------------------------------------------------
// File:   TurboDBASEoutputWindow.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# define Uses_TKeys
# define Uses_TApplication
# define Uses_TWindow
# define Uses_TEvent
# define Uses_TRect
# define Uses_TDialog
# define Uses_TStaticText
# define Uses_TButton
# define Uses_TMenuBar
# define Uses_TSubMenu
# define Uses_TMenuItem
# define Uses_TStatusLine
# define Uses_TStatusItem
# define Uses_TStatusDef
# define Uses_TDeskTop
# define Uses_TChDirDialog
# define Uses_TFileDialog
# define Uses_MsgBox
# define Uses_TDisplay
# define Uses_TScreen
# define Uses_TEditor
# define Uses_TEditWindow
# define Uses_TMemo
# define Uses_TStreamableClass

#ifdef  __FLAT__
# undef __FLAT__
#endif

# include <tvision/tv.h>
# include <tvision/help.h>

# include <string.h>
# include <stdlib.h>
# include <libintl.h>
# include <locale.h>

# include <iostream>
# include <sstream>

# include "Exception.h"
# include "formcmds.h"
# include "tvcmds.h"
# include "demohelp.h"

# include "TSyntaxFileEditor.h"

# define HELP_FILENAME "dbase.hlp"

extern ushort doEditDialog( int dialog, ... );
extern ushort execDialog( TDialog *d, void *data );

class TdBaseOutputWindow: public TDialog {
public:
    class MyOutputChild: public TSyntaxFileEditor {
    public:
        MyOutputChild(
            TdBaseOutputWindow * parent,
            const TRect& bounds,
            TScrollBar * hScrollBar,
            TScrollBar * vScrollBar,
            TIndicator * indicator,
            TStringView  filename):
            TSyntaxFileEditor( bounds,hScrollBar,vScrollBar,indicator,filename),
            owner(parent) {
            
            EditorTextColor    = 0x17;
            EditorCommentColor = 0x40;
        }
        // -------------------------------
        // event handler ...
        // -------------------------------
        void handleEvent( TEvent &event )
        {
            TSyntaxFileEditor::handleEvent( event );
            if (event.what == evKeyDown) {
                if (event.keyDown.charScan.charCode == kbEsc)     // #27 - Escape
                {
                    owner->close();
                    clearEvent(event);
                    return;
                }   else
                if (event.keyDown.keyCode == kbF1)  // F1
                {
                    clearEvent(event);
                    messageBox("getkey F1",mfInformation|mfOKButton);
                    return;
                }   else
                if (event.keyDown.keyCode == kbF2)  // F2
                {
                    clearEvent(event);
                    messageBox("getkey F2",mfInformation|mfOKButton);
                    return;
                }
            }   else
            if (event.what == evCommand) {
                if (event.message.command == 9)      // F1  - Function key
                {
                    clearEvent(event);
                    messageBox("getkey Help",mfInformation|mfOKButton);
                    return;
                }
            }
        }

    private:
        TdBaseOutputWindow * owner;
    };
    
    ~TdBaseOutputWindow() {
    }
    TdBaseOutputWindow(const TRect& bounds):
        TWindowInit(&TdBaseOutputWindow::initFrame),
        TDialog(bounds, "Output Window") {
        palette = dpGreenDialog;
    
        insert(hScrollBar_2 = new TScrollBar( TRect( 19, size.y - 1, size.x - 1, size.y ) ));
        insert(vScrollBar_2 = new TScrollBar( TRect( size.x - 2, size.y - 1, size.x - 1, size.y) ));
        insert(indicator_2  = new TIndicator( TRect( 2, size.y - 1, 13, size.y) ));
        insert(editor = new MyOutputChild(this,
            TRect(2, 10, size.x - 3, size.y - 1),
            hScrollBar_1,
            vScrollBar_1,
            indicator_1,
            "www.txt"));
        insert(editor);
    }
    
    void handleEvent(TEvent & event ){
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
private:
    MyOutputChild * editor;
    
    TIndicator    * indicator_1, * indicator_2;

    TScrollBar    * vScrollBar_1, * vScrollBar_2;
    TScrollBar    * hScrollBar_1, * hScrollBar_2;
};
