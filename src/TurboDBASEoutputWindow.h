// -----------------------------------------------------------------
// File:   TurboDBASEoutputWindow.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
#ifndef TDBASE_OUTPUT_WINDOW__H_
#define TDBASE_OUTPUT_WINDOW__H_

#pragma once

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
# include "TurboDBASEoutputChild.h"

# define HELP_FILENAME "dbase.hlp"

extern ushort doEditDialog( int dialog, ... );
extern ushort execDialog( TDialog *d, void *data );

class TdBaseOutputWindowChild;
class TdBaseOutputWindow: public TDialog {
public:
    ~TdBaseOutputWindow();
    TdBaseOutputWindow(const TRect& bounds);
   
    void handleEvent(TEvent & event );

    TdBaseOutputWindowChild      * editor;
    
    TIndicator    * indicator_1, * indicator_2;

    TScrollBar    * vScrollBar_1, * vScrollBar_2;
    TScrollBar    * hScrollBar_1, * hScrollBar_2;
};

#endif  // TDBASE_OUTPUT_WINDOW__H_
