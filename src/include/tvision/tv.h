/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   TV.H                                                                  */
/*                                                                         */
/*   includes other header files based on which Uses_XXXX symbols are      */
/*   defined.                                                              */
/*                                                                         */
/* ------------------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */
#pragma once
#define _NEAR
#define _FAR

#define _TV_VERSION 0x0200

#define Uses_EventCodes
#define Uses_ViewCommands

#define Uses_TProgram
#define Uses_TEvent
#define Uses_TGroup
#define Uses_TGroup
#define Uses_TView
#define Uses_TWindow
#define Uses_TEditor
#define Uses_TView
#define Uses_TPoint
#define Uses_TView
#define Uses_TPoint
#define Uses_TTextDevice
#define Uses_TOutlineViewer
#define Uses_TScroller
#define Uses_TScrollBar
#define Uses_TView
#define Uses_TDrawSurface
#define Uses_TScreenCell
#define Uses_TPoint
#define Uses_TScroller
#define Uses_TView
#define Uses_TMenuBox
#define Uses_TMenuView
#define Uses_TMenuView
#define Uses_TView
#define Uses_TMenuItem
#define Uses_TColorGroup
#define Uses_TDialog
#define Uses_TListViewer
#define Uses_TListViewer
#define Uses_TView
#define Uses_TCluster
#define Uses_TView
#define Uses_TDialog
#define Uses_TListBox
#define Uses_TCollection
#define Uses_TDirEntry
#define Uses_TFilterValidator
#define Uses_TValidator
#define Uses_TLookupValidator
#define Uses_TStringCollection
#define Uses_TValidator
#define Uses_TValidator
#define Uses_TObject
#define Uses_TStreamable
#define Uses_TDialog
#define Uses_TView
#define Uses_TSearchRec
#define Uses_TSortedListBox
#define Uses_TFileCollection
#define Uses_TSearchRec
#define Uses_TListBox
#define Uses_TSortedCollection
#define Uses_TSortedCollection
#define Uses_TSearchRec
#define Uses_TInputLine
#define Uses_TView
#define Uses_TWindow
#define Uses_TListViewer
#define Uses_TStaticText
#define Uses_TView
#define Uses_TListViewer
#define Uses_TCluster
#define Uses_TCluster
#define Uses_TValidator
#define Uses_TWindow
#define Uses_TGroup
#define Uses_TRect
#define Uses_TView
#define Uses_TObject
#define Uses_TStreamable
#define Uses_TCommandSet
#define Uses_TPoint
#define Uses_TDrawBuffer
#define Uses_TPalette
#define Uses_TColorAttr
#define Uses_TObject
#define Uses_TStreamable
#define Uses_TStrIndexRec
#define Uses_TObject
#define Uses_TStreamable
#define Uses_TObject
#define Uses_TStringCollection
#define Uses_TSortedCollection
#define Uses_TEvent
#define Uses_TPoint
#define Uses_TScreenCell
#define Uses_TNSSortedCollection
#define Uses_TCollection

#include <tvision/config.h>
#include <tvision/ttypes.h>
#include <tvision/util.h>

#include <tvision/tspan.h>
#include <tvision/tstrview.h>
#include <tvision/colors.h>
#include <tvision/scrncell.h>
#include <tvision/hardware.h>
#include <tvision/tkeys.h>
#include <tvision/ttext.h>
#include <tvision/tvobjs.h>
#include <tvision/tobjstrm.h>
#include <tvision/drawbuf.h>
#include <tvision/objects.h>
#include <tvision/system.h>
#include <tvision/msgbox.h>
#include <tvision/resource.h>
#include <tvision/views.h>
#include <tvision/buffers.h>
#include <tvision/dialogs.h>
#include <tvision/validate.h>
#include <tvision/stddlg.h>
#include <tvision/colorsel.h>
#include <tvision/menus.h>
#include <tvision/textview.h>
#include <tvision/editors.h>
#include <tvision/outline.h>
#include <tvision/surface.h>
#include <tvision/app.h>
