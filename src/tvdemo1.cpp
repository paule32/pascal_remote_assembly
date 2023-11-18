// ------------------------------------------------------------------
// File:   Exception.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// ------------------------------------------------------------------
# define Uses_TView
# define Uses_TRect
# define Uses_TStatusLine
# define Uses_TStatusDef
# define Uses_TStatusItem
# define Uses_TKeys
# define Uses_MsgBox
# define Uses_fpstream
# define Uses_TEvent
# define Uses_TDeskTop
# define Uses_TApplication
# define Uses_TWindow
# define Uses_TDeskTop
# define Uses_TScreen

# include <winsock2.h>
# include <tvision/tv.h>

# include "tvdemo.h"
# include "tvcmds.h"
# include "gadgets.h"
# include "fileview.h"
# include "puzzle.h"
# include "demohelp.h"
# include "evntview.h"
# include <tvision/help.h>

# include "Parser.h"

// -----------------------------------------------------------------
// used namespace ...
// -----------------------------------------------------------------
using namespace plog;    // logging
using namespace std;     // c++ std container

# include <stdio.h>
# include <string.h>

# define HELP_FILENAME "asmjit.hlp"

extern TPoint shadowSize;
extern ushort doEditDialog( int dialog, ... );

// -----------------------------------------------------------------
// Exception handling per event ...
// -----------------------------------------------------------------
# define cmUserMessage 20000

extern std::stringstream ApplicationCurrentExceptionText;
static TVDemo * demoProgram;

// -----------------------------------------------------------------
// helper function member to avoid using "goto", and as such avoid
// spagetty code.
// -----------------------------------------------------------------
int demoRunner()
{
    try {
        demoProgram->run();
    }
    // ----------------------------
    // we use try catch for errors:
    // ----------------------------
    catch (const boost::exception &e) {
        std::stringstream err;
        
        const int* errno_info = boost::get_error_info<boost::errinfo_errno>(e);
        
        err   <<   gettext("exception in function: ")
              << * boost::get_error_info<boost::throw_function>(e) << std::endl << gettext("file: ")
              << * boost::get_error_info<boost::throw_file>    (e) << std::endl << gettext("line: ")
              << * boost::get_error_info<boost::throw_line>    (e) << std::endl << gettext("code: ")
              << * errno_info <<   std::endl;
        PLOGE <<   err.str()  ;
        
        TEvent event;
        event.what = evBroadcast;
        event.message.command = cmUserMessage;
        
        ApplicationCurrentExceptionText.str(std::string(""));
        ApplicationCurrentExceptionText <<  err.str();
        
        demoProgram->putEvent(event);
        
        if (demoProgram->initialized)
        return demoRunner();
        return EXIT_FAILURE;
    }
    catch (std::exception &e) {
        std::stringstream err;
        
        err   << gettext("exception:")
              << std::endl << e.what()
              << std::endl ;
        PLOGE << err.str() ;
        
        TEvent event;
        event.what = evBroadcast;
        event.message.command = cmUserMessage;
        
        ApplicationCurrentExceptionText.str(std::string(""));
        ApplicationCurrentExceptionText <<  err.str();

        if (demoProgram->initialized)
        return demoRunner();
        return EXIT_FAILURE;
    }
    catch (...) {
        std::string err(gettext("exception: common"));
        
        PLOGE << err;
               
        TEvent event;
        event.what = evBroadcast;
        event.message.command = cmUserMessage;
        
        ApplicationCurrentExceptionText.str(std::string(""));
        ApplicationCurrentExceptionText <<  err;

        if (demoProgram->initialized)
        return demoRunner();
        return EXIT_FAILURE;
        
    }   return EXIT_SUCCESS;
}

// ------------------------------------------------------------------
// TV entry point for TU interface ...
// ------------------------------------------------------------------
int TurboMain(int argc, char **argv)
{
    demoProgram = new TVDemo(argc, argv);
    TEditor::editorDialog = doEditDialog;
    return demoRunner();
    
    TObject::destroy( demoProgram );
    return 0;
}

// ------------------------------------------------------------------
// Constructor for the application.
// ------------------------------------------------------------------
TVDemo::TVDemo( int argc, char **argv ) :
    TProgInit( &TVDemo::initStatusLine,
               &TVDemo::initMenuBar,
               &TVDemo::initDeskTop ) {
    TView *w;
    char fileSpec[128];
    int len;

    TRect r = getExtent();                      // Create the clock view.
    r.a.x = r.b.x - 9;      r.b.y = r.a.y + 1;
    clock = new TClockView( r );
    clock->growMode = gfGrowLoX | gfGrowHiX;
    insert(clock);

    r = getExtent();                            // Create the heap view.
    r.a.x = r.b.x - 23; r.b.x = r.a.x + 13; r.b.y = r.a.y + 1;
    heap = new THeapView( r );
    heap->growMode = gfGrowLoX | gfGrowHiX;
    insert(heap);

    create_info_window();
    initialized = true;
}

// ------------------------------------------------------------------
// DemoApp::getEvent()
//  Event loop to check for context help request
// ------------------------------------------------------------------
void TVDemo::getEvent(TEvent &event)
{
    TWindow *w;
    THelpFile *hFile;
    fpstream *helpStrm;
    static Boolean helpInUse = False;

    TApplication::getEvent(event);
    printEvent(event);
    switch (event.what)
    {
    case evBroadcast:
        if ((event.message.command == cmUserMessage)) {
            put_exception_message(
            ApplicationCurrentExceptionText.str().c_str());
            clearEvent(event);
        }
        break;
    case evCommand:
        if ((event.message.command == cmHelp) && ( helpInUse == False)) {
            helpInUse = True;
            helpStrm = new fpstream(HELP_FILENAME, ios::in|ios::binary);
            hFile = new THelpFile(*helpStrm);
            if (!helpStrm) {
                messageBox("Could not open help file", mfError | mfOKButton);
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
        if (event.message.command == cmVideoMode) {
            int newMode = TScreen::screenMode ^ TDisplay::smFont8x8;
            if ((newMode & TDisplay::smFont8x8) != 0)
            shadowSize.x = 1; else
            shadowSize.x = 2;
            setScreenMode((ushort)newMode);
        }
        break;
    case evMouseDown:
        if (event.mouse.buttons == mbRightButton)
            event.what = evNothing;
        break;
    }
}  

// ------------------------------------------------------------------
// Create statusline.
// ------------------------------------------------------------------
TStatusLine *TVDemo::initStatusLine( TRect r )
{
    r.a.y = r.b.y - 1;

    return (new TStatusLine( r,
      *new TStatusDef( 0, 50 ) +
        *new TStatusItem( "~F1~ Help", kbF1, cmHelp ) +
        *new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
        *new TStatusItem( 0, kbShiftDel, cmCut ) +
        *new TStatusItem( 0, kbCtrlIns, cmCopy ) +
        *new TStatusItem( 0, kbShiftIns, cmPaste ) +
        *new TStatusItem( 0, kbAltF3, cmClose ) +
        *new TStatusItem( 0, kbF10, cmMenu ) +
        *new TStatusItem( 0, kbF5, cmZoom ) +
        *new TStatusItem( 0, kbCtrlF5, cmResize ) +
      *new TStatusDef( 50, 0xffff ) +
        *new TStatusItem( "Howdy", kbF1, cmHelp )
        )
    );
}

// ------------------------------------------------------------------
// Puzzle function
// ------------------------------------------------------------------
void TVDemo::puzzle()
{
    TPuzzleWindow *puzz = (TPuzzleWindow *)
    validView(new TPuzzleWindow);

    if(puzz != 0) {
        puzz->helpCtx = hcPuzzle;
        deskTop->insert(puzz);
	}
}

// ------------------------------------------------------------------
// retrieveDesktop() function ( restores the previously stored
// Desktop )
// ------------------------------------------------------------------
void TVDemo::retrieveDesktop()
{
    if (!ifstream("asmjit.dst").good())
        messageBox(gettext("Could not find desktop file"),
        mfOKButton | mfError);
    else  {
        fpstream *f = new fpstream("asmjit.dst",
        ios::in|ios::binary);
        
        if (!f)
        messageBox(gettext("Could not open desktop file"),
        mfOKButton | mfError);
        else {
            TVDemo::loadDesktop(*f);
            if (!f)
            messageBox(gettext("Error reading desktop file"),
            mfOKButton | mfError);
        }
        delete f;
    }
}

// ------------------------------------------------------------------
// saveDesktop() function ( saves the DeskTop by calling storeDesktop
// function )
// ------------------------------------------------------------------
void TVDemo::saveDesktop()
{
    fpstream *f = new
    fpstream("asmjit.dst", ios::out|ios::binary);

    if (f) {
        TVDemo::storeDesktop(*f);
        if (!f) {
            std::stringstream err;
            
            err << gettext("Could not create ")
                << "asmjit.dst";
                
            messageBox(
                err.str(),
                mfOKButton | mfError);
                
            delete f;
            ::remove("asmjit.dst");
            return;
        }
    }
    delete f;
}

//
// writeView() function ( writes a view object to a resource file )
//

static void writeView(TView *p, void *strm)
{
   fpstream *s = (fpstream *) strm;
   if (p != TProgram::deskTop->last)
      *s << p;
}

//
// storeDesktop() function ( stores the Desktop in a resource file )
//
void TVDemo::storeDesktop(fpstream& s)
{
    deskTop->forEach(::writeView, &s);
    s << 0;
}
