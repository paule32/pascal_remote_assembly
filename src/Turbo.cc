// -----------------------------------------------------------------
// File:   Turbo.cc
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
# include <tvision/tv.h>

# include <string.h>
# include <stdlib.h>

#include "formcmds.h"

#define FORM_WILDCARD "*.f32"

extern TPoint shadowSize;
const int MAXSIZE = 150;

ushort execDialog( TDialog *d, void *data )
{
    TView *p = TProgram::application->validView( d );
    if( p == 0 )
        return cmCancel;
    else
        {
        if( data != 0 )
            p->setData( data );
        ushort result = TProgram::deskTop->execView( p );
        if( result != cmCancel && data != 0 )
            p->getData( data );
        TObject::destroy( p );
        return result;
        }
}

class TFormApp : public TApplication
{
public:

    TFormApp();

    void handleEvent( TEvent& Event);
    static TMenuBar *initMenuBar( TRect r);
    static TStatusLine *initStatusLine( TRect r);
    void changeDir();

    TEditWindow * openEditor( const char *fileName, Boolean visible );
    void fileNew();
    void fileOpen();
};

TEditWindow *TFormApp::openEditor( const char *fileName, Boolean visible )
{
    TRect r = deskTop->getExtent();
    TView *p = validView( new TEditWindow( r, fileName, wnNoNumber ) );
    if( !visible )
        p->hide();
    deskTop->insert( p );
    return (TEditWindow *)p;
}

void TFormApp::fileOpen()
{
    char fileName[MAXPATH];
    strcpy( fileName, "*.*" );

    if( execDialog( new TFileDialog( "*.*", "Open file",
            "~N~ame", fdOpenButton, 100 ), fileName) != cmCancel )
        openEditor( fileName, True );
}

void TFormApp::fileNew()
{
    openEditor( 0, True );
}

// TFormApp
TFormApp::TFormApp() :
    TProgInit(&TFormApp::initStatusLine,
              &TFormApp::initMenuBar,
              &TFormApp::initDeskTop),
    TApplication()
{
    TEvent event;

    // Display about box
    event.what = evCommand;
    event.message.command = cmAboutBox;
    putEvent(event);
}

void TFormApp::changeDir()
{
    TView *d = validView( new TChDirDialog( 0, hlChangeDir ) );

    if( d != 0 ) {
        deskTop->execView( d );
        destroy(d);
    }
}

void TFormApp::handleEvent(TEvent& event)
{
    int newMode;
    char aboutMsg[80];

    TApplication::handleEvent(event);
    if (event.what == evCommand)
        {
        switch (event.message.command)
        {
            case cmListOpen:
                fileOpen();
                break;
            case cmChgDir:
                changeDir();
                break;
            case cmAboutBox:
                strcpy(aboutMsg, "\x3Turbo Vision AsmJit 1.0\n\n\x3non-profit Project");
                messageBox(aboutMsg, mfInformation | mfOKButton);
                break;
            case cmVideoMode:
                newMode = TScreen::screenMode ^ TDisplay::smFont8x8;
                if ((newMode & TDisplay::smFont8x8) != 0)
                    shadowSize.x = 1;
                else
                    shadowSize.x = 2;
                setScreenMode((ushort)newMode);
                break;

            default:
                return;
            }
        clearEvent(event);
        }
}

TMenuBar *TFormApp::initMenuBar( TRect r)
{

    r.b.y = r.a.y + 1;
    return new TMenuBar(r,
      *new TSubMenu( "~\xF0~", hcNoContext ) +
        *new TMenuItem( "~V~ideo mode", cmVideoMode, kbNoKey, hcNoContext, "" ) +
             newLine() +
        *new TMenuItem( "~A~bout...", cmAboutBox, kbNoKey, hcNoContext ) +
      *new TSubMenu( "~F~ile", hcNoContext) +
        *new TMenuItem( "~O~pen...", cmListOpen, kbF3, hcNoContext, "F3" ) +
        *new TMenuItem( "~S~ave", cmListSave, kbF2, hcNoContext, "F2" ) +
             newLine() +
        *new TMenuItem( "~C~hange directory...", cmChgDir, kbNoKey, hcNoContext ) +
        *new TMenuItem( "~D~OS shell", cmDosShell, kbNoKey, hcNoContext ) +
        *new TMenuItem( "E~x~it", cmQuit, kbAltX, hcNoContext, "Alt-X" ) +
      *new TSubMenu( "~W~indow", hcNoContext ) +
        *new TMenuItem( "~M~ove", cmResize, kbCtrlF5, hcNoContext, "Cntl-F5") +
        *new TMenuItem( "~N~ext", cmNext, kbF6, hcNoContext, "F6") +
        *new TMenuItem( "~P~rev", cmPrev, kbShiftF6, hcNoContext, "Shift-F6") +
        *new TMenuItem( "~C~lose", cmClose, kbAltF3, hcNoContext, "Alt-F3")
      );
}

TStatusLine *TFormApp::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;
    return new TStatusLine( r,
      *new TStatusDef( 0, 0xFFFF ) +
        *new TStatusItem( "~F2~ Save", kbF2, cmListSave ) +
        *new TStatusItem( "~F3~ Open", kbF3, cmListOpen ) +
        *new TStatusItem( "~F10~ Menu", kbF10, cmMenu) +
        *new TStatusItem( 0, kbShiftDel, cmCut ) +
        *new TStatusItem( 0, kbCtrlIns, cmCopy ) +
        *new TStatusItem( 0, kbShiftIns, cmPaste ) +
        *new TStatusItem( "", kbCtrlF5, cmResize )
        );
}

int TurboMain(void)
{
    TFormApp *formApp = new TFormApp;
    formApp->run();
    TObject::destroy(formApp);

    return 0;
}
