// -----------------------------------------------------------------
// File:   TurboDBASE.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# define Uses_TKeys
# define Uses_TApplication
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

# include <string.h>
# include <stdlib.h>

# include "formcmds.h"
# include "TSyntaxFileEditor.h"

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
        TDialog(bounds, "Info window") {
        
        insert(hScrollBar = new TScrollBar( TRect( 18, size.y - 1, size.x - 23, size.y ) ));
        insert(vScrollBar = new TScrollBar( TRect( size.x - 23, 1, size.x - 22, size.y - 1 ) ));
        insert(indicator  = new TIndicator( TRect( 2, size.y - 1, 16, size.y) ));
        
        insert(editor = new MyEditorChild(this,
            TRect(2, 1, size.x - 24, size.y - 1),
            hScrollBar,
            vScrollBar,
            indicator,
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
    TIndicator    * indicator;

    TScrollBar    * vScrollBar;
    TScrollBar    * hScrollBar;
};

class TdBaseFormApp : public TApplication
{
public:

    TdBaseFormApp();

    void handleEvent( TEvent& Event);
    static TMenuBar *initMenuBar( TRect r);
    static TStatusLine *initStatusLine( TRect r);
    
    void dBaseCommandEditor(void);
    
    TdBaseEditorWindow * dBaseEditor;
};

// TdBaseFormApp
void TdBaseFormApp::dBaseCommandEditor(void)
{
    dBaseEditor = (TdBaseEditorWindow *) validView(
    new TdBaseEditorWindow(TRect(0, 0, 81, 23)));

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
            *new TStatusItem( "~F2~ Save", kbF2, cmListSave ));
}

int TurboDBASE(void)
{
    auto * formApp = new TdBaseFormApp;
    formApp->run();
    
    TObject::destroy(formApp);
    return EXIT_SUCCESS;
}
