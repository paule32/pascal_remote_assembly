// -----------------------------------------------------------------
// File:   TurboDBASE.cc
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
# include "TurboDBASEoutputWindow.h"

# define HELP_FILENAME "dbase.hlp"

extern ushort doEditDialog( int dialog, ... );
extern ushort execDialog( TDialog *d, void *data );

class TdBaseEditorWindow: public TDialog {
public:
    class MyEditorChild: public TSyntaxFileEditor {
    public:
        MyEditorChild(
            TdBaseEditorWindow * parent,
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
        TdBaseEditorWindow * owner;
    };
    
    ~TdBaseEditorWindow() {
    }
    TdBaseEditorWindow(const TRect& bounds):
        TWindowInit(&TdBaseEditorWindow::initFrame),
        TDialog(bounds, "Command Window") {
        palette = dpBlueDialog;
    
        insert(hScrollBar_1 = new TScrollBar( TRect( 19, 9, size.x - 1, 10 ) ));
        insert(vScrollBar_1 = new TScrollBar( TRect( size.x - 2, 1, size.x - 1, 9 ) ));
        insert(indicator_1  = new TIndicator( TRect( 2, 9, 18, 10) ));
        insert(summary = new MyEditorChild(this,
            TRect(2, 1, size.x - 3, 9),
            hScrollBar_1,
            vScrollBar_1,
            indicator_1,
            "history.log"));
        insert(summary);
        
        insert(hScrollBar_2 = new TScrollBar( TRect( 19, size.y - 1, size.x - 1, size.y ) ));
        insert(vScrollBar_2 = new TScrollBar( TRect( size.x - 2, 10, size.x - 1, size.y - 1 ) ));
        insert(indicator_2  = new TIndicator( TRect( 2, size.y - 1, 13, size.y) ));
        insert(editor = new MyEditorChild(this,
            TRect(2, 10, size.x - 3, size.y - 1),
            hScrollBar_2,
            vScrollBar_2,
            indicator_2,
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
    MyEditorChild * editor;
    MyEditorChild * summary;
    
    TIndicator    * indicator_1, * indicator_2;

    TScrollBar    * vScrollBar_1, * vScrollBar_2;
    TScrollBar    * hScrollBar_1, * hScrollBar_2;
};

class TdBaseFormApp : public TApplication
{
public:

    TdBaseFormApp();

    void handleEvent( TEvent& Event);
    static TMenuBar *initMenuBar( TRect r);
    static TStatusLine *initStatusLine( TRect r);

    virtual void getEvent(TEvent& event);
    
    void dBaseCommandEditor(void);
    
    TdBaseEditorWindow * dBaseEditor;
    TdBaseOutputWindow * dBaseOutputWindow;
};

// TdBaseFormApp
void TdBaseFormApp::dBaseCommandEditor(void)
{
    dBaseOutputWindow = (TdBaseOutputWindow *) validView(
    new TdBaseOutputWindow(TRect(2, 0, 84, 27)));
    if (dBaseOutputWindow != nullptr) {
        dBaseOutputWindow->helpCtx = 5200;
        deskTop->insert( dBaseOutputWindow );
    }

    dBaseEditor = (TdBaseEditorWindow *) validView(
    new TdBaseEditorWindow(TRect(18, 5, 99, 25)));
    if (dBaseEditor != nullptr) {
        dBaseEditor->helpCtx = 5000;
        deskTop->insert( dBaseEditor );
    }
}
TdBaseFormApp::TdBaseFormApp() :
    TProgInit(&TdBaseFormApp::initStatusLine,
              &TdBaseFormApp::initMenuBar,
              &TdBaseFormApp::initDeskTop),
    TApplication()
{
    TEvent event;
    TEditor::editorDialog = doEditDialog;
    
    dBaseCommandEditor();

    // Display about box
    //event.what = evCommand;
    //event.message.command = cmAboutBox;
    //putEvent(event);
}

void TdBaseFormApp::handleEvent(TEvent& event)
{
    int newMode;
    char aboutMsg[80];

    TApplication::handleEvent(event);
    if (event.what == evCommand) {
        switch (event.message.command)
        {
            case cmAboutBox:
                strcpy(aboutMsg, "\x3Turbo Vision AsmJit 1.0\n\n\x3non-profit Project");
                messageBox(aboutMsg, mfInformation | mfOKButton);
                break;

            default:
                return;
        }
        clearEvent(event);
    }
}

TMenuBar *TdBaseFormApp::initMenuBar( TRect r)
{
    r.b.y = r.a.y + 1;
    return new TMenuBar(r,
        *new TSubMenu( "~\xF0~", hcNoContext ) +
            *new TMenuItem( "~V~ideo mode", cmVideoMode, kbNoKey, hcNoContext, "" ) +
                newLine() +
            *new TMenuItem( "~A~bout...", cmAboutBox, kbNoKey, hcNoContext ));
}

TStatusLine *TdBaseFormApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;
    return new TStatusLine( r,
        *new TStatusDef( 0, 0xFFFF ) +
            *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmCloseApplication ));
}

void TdBaseFormApp::getEvent(TEvent &event)
{
    TWindow *w;
    THelpFile *hFile;
    fpstream *helpStrm;
    static Boolean helpInUse = False;
    
    TApplication::getEvent(event);
    switch (event.what)
    {
        case evCommand: {
            if ((event.message.command == cmHelp) && ( helpInUse == False)) {
                helpInUse = True;
                helpStrm = new fpstream(HELP_FILENAME, ios::in|ios::binary);
                hFile = new THelpFile(*helpStrm);
                if (!helpStrm) {
                    messageBox(gettext("Could not open help file"), mfError | mfOKButton);
                    delete hFile;
                }   else {
                    w = new THelpWindow(hFile, getHelpCtx());
                    if (validView(w) != 0) {
                        execView(w);
                        destroy( w );
                    }
                    clearEvent(event);
                }
                helpInUse = False;
            }   else
            if (event.message.command == cmCloseApplication) {
                clearEvent(event);
                // ------------------------------------------
                // if clicked result = yes/12, then close ...
                // ------------------------------------------
                int result = messageBoxRect(
                    TRect( 14,7,59,16),
                    gettext("Would you realy close the Application ?"),
                    mfYesNoCancel | mfInformation );
                    std::stringstream ss;
                if (result == 12) {
                    throw EPascalException_NoErrorExcpetion("exit");
                }
            }
        }
        break;
    }
}

int TurboDBASE(void)
{
    auto * formApp = new TdBaseFormApp;
    formApp->run();
    
    TObject::destroy(formApp);
    return EXIT_SUCCESS;
}
