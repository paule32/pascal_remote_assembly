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
std::vector< TSyntaxLanguageType > TSyntaxType;
std::vector< TSyntaxCommentType  > TSyntaxComment;

// -----------------------------------------------------------------
// this map holds the possible token's for the Pasccal DSL.
// It will be used, if "TSyntaxType" contains:
// "TSyntaxLanguageType::pascal"
// -----------------------------------------------------------------
std::map< std::string, TColorAttr > SyntaxPascalToken =
{
    { "program",        0x1f },    // 0x1f = blue on white
    
    { "array",          0x1f },
    { "begin",          0x1f },
    { "byte",           0x1f },
    { "case",           0x1f },
    { "char",           0x1f },
    { "class",          0x1f },
    { "do",             0x1f },
    { "dec",            0x1f },
    { "else",           0x1f },
    { "end",            0x1f },
    { "for",            0x1f },
    { "if",             0x1f },
    { "implementation", 0x1f },
    { "inc",            0x1f },
    { "integer",        0x1f },
    { "interface",      0x1f },
    { "of",             0x1f },
    { "record",         0x1f },
    { "string",         0x1f },
    { "then",           0x1f },
    { "unit",           0x1f },
    { "until",          0x1f },
    { "uses",           0x1f },
    { "while",          0x1f },
    { "word",           0x1f }
};

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
        TStringView    filename):
        TFileEditor( bounds,hScrollBar,vScrollBar,indicator,filename) {

        // ----------------------------------------------
        // standard pascal token color map ...
        // ----------------------------------------------
        EditorSyntaxToken = SyntaxPascalToken;

        // for get word under cursor
        eventMask |= evBroadcast;
    }
    
    // -------------------------------
    // event handler ...
    // -------------------------------
    void handleEvent( TEvent &event ) {
        TFileEditor::handleEvent( event );
    }
    
    // -----------------------------------------------------
    // this is our "syntax highlight" member function ...
    // -----------------------------------------------------
    virtual void formatLine(
        TScreenCell *DrawBuf,
        uint P,
        int Width,
        TAttrPair Colors
        ) override {
            
        TSpan<TScreenCell> Cells(DrawBuf, Width);
        TStringView chars;
        TColorAttr  Color;
        std::string token;
        
        bool tokenIsComment = false;
        
        int  pos;
        char Ch;
        
        int X = 0;
        Color = EditorTextColor;
        token = "";
        
        while (1) {
            if (P >= bufLen || X >= Width) break;
            tokenIsComment = false;
            chars = bufChars(P);
            Color = EditorTextColor;
            Ch    = chars[0];
            
            // ----------------------------
            // parse white space's ...
            // ----------------------------
            if (Ch == ' ') {
                Color = EditorTextColor;
                while (X < Width) {
                    ::setCell(Cells[X], Ch, Color);
                    X++;
                    P++;
                    chars = bufChars(P);
                    Ch = chars[0];
                    if (Ch != ' ') break;
                }
            }
            
            // ----------------------------
            // parse token for Pascal DSL
            // ----------------------------
            if (((Ch >= 'A') && (Ch <= 'Z'))
            ||  ((Ch >= 'a') && (Ch <= 'z'))) {
                pos = X;
                ::setCell(Cells[X++], Ch, EditorTextColor);
                token.push_back(Ch);
                while (1) {
                    if ((P >= bufLen) || (X >= Width)) break;
                    P++;
                    chars = bufChars(P);
                    Ch = chars[0];
                    if (((Ch >= 'A') && (Ch <= 'Z'))
                    ||  ((Ch >= 'a') && (Ch <= 'z'))
                    ||  ((Ch >= '0') && (Ch <= '9'))
                    ||  (Ch == '_')) {
                        ::setCell(Cells[X++], Ch, EditorTextColor);
                        token.push_back(Ch);
                    }   else break;
                }
                if (X >= Width) break;
                
                // ---------------------------------------------
                // convert token letter's to lower case letter's
                // ---------------------------------------------
                for (char &c : token)
                c = std::tolower(c);
                X = pos;
            
                auto it = EditorSyntaxToken.find(token);
                if (it != EditorSyntaxToken.end()) {
                    for (char &c: token) {
                        if (X >= Width) break;
                        ::setCell(Cells[X++], c, it->second);
                    }
                }   else {
                    for (char &c: token) {
                        if (X >= Width) break;
                        ::setCell(Cells[X++], c, EditorTextColor);
                    }
                }
                token = "";
            }
            
            // ----------------------------
            // parse comment's ...
            // ----------------------------
            if (Ch == '&') {
                Color = EditorTextColor;
                ::setCell(Cells[X], '&', Color);
                X++;
                P++;
                chars = bufChars(P);
                Ch = chars[0];
                if (P >= bufLen || X >= Width) break;
                
                // ----------------------------
                // dBase comment &&
                // ----------------------------
                if (Ch == '&') {
                    tokenIsComment = true;
                    ::setCell(Cells[X-1], Ch, EditorCommentColor);
                    if (X < Width) {
                        do  {
                            ::setCell(Cells[X++], Ch, EditorCommentColor);
                            P++;
                            chars = bufChars(P);
                            Ch = chars[0];
                            if (Ch == '\r' || Ch == '\n') {
                                while (X < Width)
                                ::setCell(Cells[X++], ' ', Color);
                                P++;
                                break;
                            }
                        }   while (X < Width);
                        ++P;
                    }   else break;
                }   else
                if (Ch == '\r' || Ch == '\n') {
                    while (X < Width)
                    ::setCell(Cells[X++], ' ', Color);
                    P++;
                    break;
                }   else {
                    ::setCell(Cells[X], Ch, Color);
                    X++;
                    P++;
                    if (P >= bufLen || X >= Width) break;
                }
            }   else
            if (Ch == '/') {
                ::setCell(Cells[X], '/', Color);
                X++;
                P++;
                chars = bufChars(P);
                Ch = chars[0];
                if (P >= bufLen || X >= Width) break;
                
                // ----------------------------
                // c++ comment
                // ----------------------------
                if (Ch == '/') {
                    tokenIsComment = true;
                    ::setCell(Cells[X-1], Ch, EditorCommentColor);
                    if (X < Width) {
                        do  {
                            ::setCell(Cells[X++], Ch, EditorCommentColor);
                            P++;
                            chars = bufChars(P);
                            Ch = chars[0];
                            if (Ch == '\r' || Ch == '\n') {
                                while (X < Width)
                                ::setCell(Cells[X++], ' ', Color);
                                P++;
                                break;
                            }
                        }   while (X < Width);
                        ++P;
                    }   else break;
                }   else
                    
                // ----------------------------
                // c comment
                // ----------------------------
                if (Ch == '*') {
                    tokenIsComment = true;
                    Color = EditorCommentColor;
                    ::setCell(Cells[X-1], '/', Color);
                    ::setCell(Cells[X  ], '*', Color);
                    X++;
                    P++;
                    while (1) {
                        if (P >= bufLen || X >= Width) break;
                        chars = bufChars(P);
                        Ch = chars[0];
                        if (Ch == '*') {
                            ::setCell(Cells[X], '*', Color);
                            X++;
                            P++;
                            if (P >= bufLen || X >= Width) break;
                            chars = bufChars(P);
                            Ch = chars[0];
                            if (Ch == '/') {
                                ::setCell(Cells[X], Ch, Color);
                                tokenIsComment = false;
                                Color = EditorTextColor;
                                X++;
                                P++;
                                break;
                            }   else
                            if (Ch == '\r' || Ch == '\n') {
                                while (X < Width)
                                ::setCell(Cells[X++], ' ', Color);
                                P++;
                                break;
                            }   else {
                                ::setCell(Cells[X], Ch, Color);
                                X++;
                                P++;
                                if (P >= bufLen || X >= Width) break;
                            }
                        }   else
                        if (Ch == '\r' || Ch == '\n') {
                            while (X < Width)
                            ::setCell(Cells[X++], ' ', EditorCommentColor);
                            P++;
                            if (P >= bufLen || X >= Width) break;
                        }   else {
                            ::setCell(Cells[X], Ch, EditorCommentColor);
                            X++;
                            P++;
                            if (P >= bufLen || X >= Width) break;
                        }
                    }
                }   else {
                    ::setCell(Cells[X], Ch, EditorTextColor);
                    X++;
                    P++;
                    if (P >= bufLen || X >= Width) break;
                }
            }   else
            if (Ch == '(') {
                ::setCell(Cells[X], '(', EditorTextColor);
                X++;
                P++;
                chars = bufChars(P);
                Ch = chars[0];
                if (P >= bufLen || X >= Width) break;
                
                // ----------------------------
                // old style pascal comment
                // ----------------------------
                if (Ch == '*') {
                    tokenIsComment = true;
                    Color = EditorCommentColor;
                    ::setCell(Cells[X-1], '(', Color);
                    ::setCell(Cells[X  ], '*', Color);
                    X++;
                    P++;
                    while (1) {
                        if (P >= bufLen || X >= Width) break;
                        chars = bufChars(P);
                        Ch = chars[0];
                        if (Ch == '*') {
                            ::setCell(Cells[X], '*', Color);
                            X++;
                            P++;
                            if (P >= bufLen || X >= Width) break;
                            chars = bufChars(P);
                            Ch = chars[0];
                            if (Ch == ')') {
                                ::setCell(Cells[X], Ch, Color);
                                tokenIsComment = false;
                                Color = EditorTextColor;
                                X++;
                                P++;
                                break;
                            }   else
                            if (Ch == '\r' || Ch == '\n') {
                                while (X < Width)
                                ::setCell(Cells[X++], ' ', Color);
                                P++;
                                break;
                            }   else {
                                ::setCell(Cells[X], Ch, Color);
                                X++;
                                P++;
                                if (P >= bufLen || X >= Width) break;
                            }
                        }   else
                        if (Ch == '\r' || Ch == '\n') {
                            while (X < Width)
                            ::setCell(Cells[X++], ' ', EditorCommentColor);
                            P++;
                            if (P >= bufLen || X >= Width) break;
                        }   else {
                            ::setCell(Cells[X], Ch, EditorCommentColor);
                            X++;
                            P++;
                            if (P >= bufLen || X >= Width) break;
                        }
                    }
                }   else {
                    ::setCell(Cells[X], Ch, EditorTextColor);
                    X++;
                    P++;
                    if (P >= bufLen || X >= Width) break;
                }
            }   else
            if (Ch == '*') {
                if (tokenIsComment)
                Color = EditorCommentColor; else
                Color = EditorTextColor;
                ::setCell(Cells[X], '*', Color);
                X++;
                P++;
                if (P >= bufLen || X >= Width) break;
                chars = bufChars(P);
                Ch = chars[0];
                
                // ----------------------------
                // dBase comment **
                // ----------------------------
                if (Ch == '*') {
                    tokenIsComment = true;
                    ::setCell(Cells[X-1], Ch, EditorCommentColor);
                    if (X < Width) {
                        do  {
                            ::setCell(Cells[X++], Ch, EditorCommentColor);
                            P++;
                            chars = bufChars(P);
                            Ch = chars[0];
                            if (Ch == '\r' || Ch == '\n') {
                                while (X < Width)
                                ::setCell(Cells[X++], ' ', Color);
                                P++;
                                break;
                            }
                        }   while (X < Width);
                        ++P;
                    }   else break;
                }   else
                    
                // ----------------------------
                // end of c comment
                // ----------------------------
                if (Ch == '/') {
                    tokenIsComment = false;
                    Color = EditorTextColor;
                    ::setCell(Cells[X], '/', EditorCommentColor);
                    X++;
                    P++;
                    if (P >= bufLen || X >= Width) break;
                }   else
                    
                // ----------------------------
                // end of pascal comment
                // ----------------------------
                if (Ch == ')') {
                    tokenIsComment = false;
                    Color = EditorTextColor;
                    ::setCell(Cells[X], ')', EditorCommentColor);
                    X++;
                    P++;
                    if (P >= bufLen || X >= Width) break;
                }   else {
                    Color = EditorCommentColor;
                    ::setCell(Cells[X], '*', EditorCommentColor);
                    X++;
                    P++;
                    if (P >= bufLen || X >= Width) break;
                }
            }   else
            if (Ch == '\r' || Ch == '\n') {
                tokenIsComment = false;
                while (X < Width)
                ::setCell(Cells[X++], ' ', Color);
                P++;
                break;
            }   else
            if (Ch == '\t') {
                if (tokenIsComment)
                Color = EditorCommentColor; else
                Color = EditorTextColor;
                if (X < Width) {
                    do {
                        ::setCell(Cells[X++], ' ', Color);
                    }   while (X%8 != 0 && X < Width);
                    ++P;
                }   else break;
            }   else {
                if (tokenIsComment)
                Color = EditorCommentColor; else
                Color = EditorTextColor;
                if (!formatCell(Cells, (uint&) X, chars, P, Color))
                break;
            }
        }
        while (X < Width)
        ::setCell(Cells[X++], ' ', Color);
    }
    
    // -------------------------------
    // get the word under the cursor:
    // -------------------------------
    virtual std::string getWordUnderCursor() {
        std::string word;
        
        uint wordEnd   = nextWord(curPtr);
        uint wordStart = prevWord(wordEnd);
        
        for (uint i = wordStart; i < wordEnd; ++i) {
            char c = bufChar(i);
            if (!std::isspace(c))
            word.push_back(c);
        }
        
        return word;
    }

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
