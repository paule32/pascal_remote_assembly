// -----------------------------------------------------------------
// File:   tvAsmJit.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
#pragma once

class  TStatusLine;
class  TMenuBar;
class  TPalette;
class  THeapView;
class  TClockView;
class  TMyTvEditor;
class  fpstream;

struct TEvent;

class TVDemo : public TApplication 
{

public:

    TVDemo( int argc, char **argv );

    static TStatusLine * initStatusLine( TRect r );
    static TMenuBar    * initMenuBar( TRect r );

    virtual void handleEvent(TEvent& Event);
    virtual void getEvent(TEvent& event);
    virtual void idle();              // Updates heap and clock views

    bool initialized = false;
    
private:
    
    THeapView  * heap;                // Heap view
    TClockView * clock;               // Clock view

    void aboutDlgBox();               // "About" box
    void puzzle();                    // Puzzle
    void calendar();                  // Calendar
    void asciiTable();                // Ascii table
    void calculator();                // Calculator
    void eventViewer();
    void printEvent(const TEvent &);
    void chBackground();              // Background pattern
    void openFile( const char *fileSpec );  // File Viewer
    void changeDir();                 // Change directory
    void mouse();                     // Mouse control dialog box
    void colors();                    // Color control dialog box
    void outOfMemory();               // For validView() function
    void loadDesktop(fpstream& s);    // Load and restore the
    void retrieveDesktop();           //  previously saved desktop
    void storeDesktop(fpstream& s);   // Store the current desktop
    void saveDesktop();               //  in a resource file

    void tvEditor();
    void create_info_window();
    void put_exception_message(const char* text);
    
    void newProjectServer();
    void toogleZoom();
};
