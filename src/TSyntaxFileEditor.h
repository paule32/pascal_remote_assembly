// -----------------------------------------------------------------
// File:   TSyntaxFileEditor.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
//
// @brief This file provides a very simple Syntax Highlighter for
//        TurboVision C++. Based on TFileEditor. We have to change
//        the member "formatLine" to "virtual" in source header
//        file: editors.hpp.
//        The tokens for the syntax can be easily store into the:
//
//        std::map< std::string, TColorAttr > EditorSyntaxToken;
// -----------------------------------------------------------------
#ifndef TSYNTAXFILEEDITOR_H_
#define TSYNTAXFILEEDITOR_H_

# pragma once

# define Uses_TApplication
# define Uses_TProgram
# define Uses_TDialog
# define Uses_TStaticText
# define Uses_TButton
# define Uses_TEvent
# define Uses_TWindow
# define Uses_TPalette
# define Uses_TDeskTop
# define Uses_TScreen
# define Uses_TView
# define Uses_TEditWindow
# define Uses_TFileEditor
# define Uses_TFileDialog
# define Uses_TObject
# define Uses_MsgBox
# define Uses_TIndicator
# define Uses_TRect
# define Uses_TEditor
# define Uses_TKeys
# define Uses_TScrollBar

// -----------------------------------------------------------------
// __FLAT__ will be defined, if you simply #include this file.
// We #undef it, because we re-include the #include <tvision/tv.h>
// -----------------------------------------------------------------
#ifdef  __FLAT__
# undef __FLAT__
#endif
# include <tvision/tv.h>

# include <iostream>
# include <vector>
# include <map>

// -----------------------------------------------------------------
// this is our "syntax type" enum class to describe the highlighter
// -----------------------------------------------------------------
enum class TSyntaxLanguageType : unsigned char {
    ltPascal = 0x01
};
enum class TSyntaxCommentType  : unsigned char {
    ctPascal = 0x01,
    ctCpp    = 0x02,
    ctDbase  = 0x03
};
// -----------------------------------------------------------------
// std::vector is a simple way, to search for enum class items ...
// -----------------------------------------------------------------
extern std::vector< TSyntaxLanguageType > TSyntaxType;
extern std::vector< TSyntaxCommentType  > TSyntaxComment;

// -----------------------------------------------------------------
// this map holds the possible token's for the Pasccal DSL.
// It will be used, if "TSyntaxType" contains:
// "TSyntaxLanguageType::pascal"
// -----------------------------------------------------------------
extern std::map< std::string, TColorAttr > SyntaxPascalToken;

// -----------------------------------------------------------------
// editor for syntax highligter, based on:  TEditor <-- TFileEdior
// -----------------------------------------------------------------
class TSyntaxFileEditor: public TFileEditor
{
public:
    TSyntaxFileEditor(
        const TRect  & bounds,
        TScrollBar   * hScrollBar,
        TScrollBar   * vScrollBar,
        TIndicator   * indicator,
        TStringView    filename);
        
    
    // -------------------------------
    // event handler ...
    // -------------------------------
    void handleEvent( TEvent &event );
    
    // -----------------------------------------------------
    // this is our "syntax highlight" member function ...
    // -----------------------------------------------------
    virtual void formatLine(
        TScreenCell *DrawBuf,
        uint P,
        int Width,
        TAttrPair Colors
        ) override;
    
    // -------------------------------
    // get the word under the cursor:
    // -------------------------------
    virtual std::string getWordUnderCursor();

    // -----------------------------------------------------
    // provide DSL Token & Color for highlight text
    // -----------------------------------------------------
    std::map< std::string, TColorAttr > EditorSyntaxToken;

    // -----------------------------------------------------
    // change the text & background color of TEditor,
    // default is blue on yellow the BIOS color code:
    // 0x1e => blue background on yellow text ...
    // -----------------------------------------------------
    TColorAttr EditorTextColor    = 0x1e;  // blue on yellow
    TColorAttr EditorCommentColor = 0x30;  // green on black
};

#endif  // TSYNTAXFILEEDITOR_H_
