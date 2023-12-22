// -----------------------------------------------------------------
// File:   TurboDBASEoutputChild.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# define Uses_TKeys
# define Uses_TView
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

# include <shlwapi.h>

# include <string.h>
# include <stdlib.h>
# include <libintl.h>
# include <locale.h>

# include <iostream>
# include <string>
# include <sstream>
# include <locale>
# include <codecvt>
# include <map>

# include "Exception.h"
# include "formcmds.h"
# include "tvcmds.h"
# include "demohelp.h"

# include "dBaseHelp.h"

# include "TSyntaxFileEditor.h"
# include "TurboDBASEoutputWindow.h"
# include "TurboDBASEoutputChild.h"

# define HELP_FILENAME "dbase.hlp"

extern ushort doEditDialog( int dialog, ... );
extern ushort execDialog( TDialog *d, void *data );

extern std::string ApplicationExePath;

std::map< HelpTopics, std::string > helpTopicMap = {
    { HELP_Welcome, "Welcome" },
    { HELP_Introduction, "Introduction" }
};

const char*
GetHelpTopicString(HelpTopics topic)
{
    std::string help = helpTopicMap[topic];
    if (help.length() > 0) {
        help.append(".htm");
        return help.c_str();
    }   return "";
}

TdBaseOutputWindowChild::TdBaseOutputWindowChild(
    TdBaseOutputWindow * parent,
    const TRect& bounds):
    TView(bounds),
    owner(parent) {
    
    options |= ofSelectable;
}

// -------------------------------
// event handler ...
// -------------------------------
void TdBaseOutputWindowChild::handleEvent( TEvent &event )
{
    TView::handleEvent( event );
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
            
            // -------------------------------
            // path to the help file ...
            // -------------------------------
            std::stringstream ss;
            ss << ApplicationExePath << "\\dBaseHelp.chm";
            std::string chmFileName = ss.str();
            
            if (!PathFileExists(chmFileName.c_str())) {
                messageBox("dBaseHelp.chm could not be open.",mfInformation|mfOKButton);
                return;
            }
            
            HelpTopics selectedTopic = HELP_Welcome;
            
            char commandLine[MAX_PATH + 50];
            char topicString[MAX_PATH + 50];
            
            sprintf_s(topicString, "::/%s", GetHelpTopicString(selectedTopic));
            sprintf_s(commandLine, "hh.exe %s%s", chmFileName.c_str(), topicString);
            
            STARTUPINFO si = { sizeof(si) };
            PROCESS_INFORMATION pi;
            
            if (CreateProcessA(nullptr,commandLine,
                nullptr,nullptr,FALSE,0,nullptr,
                nullptr,&si,&pi)) {
                WaitForSingleObject(pi.hProcess,INFINITE);
                CloseHandle(pi.hThread);
                CloseHandle(pi.hProcess);
            }   else {
                messageBox("the process could not be started.",mfInformation|mfOKButton);
            }
            
            //messageBox("getkey F1",mfInformation|mfOKButton);
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

TColorAttr
TdBaseOutputWindowChild::mapColorOutsideClass(uchar index)
{
    switch (index)
    {
        case  1: return 0x01; break;
        case  2: return 0x02; break;
        case 11: return 0x0b; break;
        case 14: return 0x0e; break;
        case 15: return 0x0f; break;
        
        default:
            return TView::mapColor(index);
    }
}

void TdBaseOutputWindowChild::drawContent()
{
    int y = 0, ymax = size.y;
    for (y; y < ymax; ++y) {
        writeChar(0, y, ' ', getColor(14), size.x);
    }
    
    writeStr(0,1, "dBase output Console v1.0.0 (c) 2023 paule32", getColor(11));
    writeStr(0,2, "All rights reserved.", getColor(14));
    writeStr(0,4, "#", getColor(15));
}
