// -----------------------------------------------------------------
// File:   tvEditor.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------

const ushort
    cmButtonInfoWindow1 = 5000,
    cmButtonInfoWindow2 = 5001,
    
    cmGetFocusedEditor  = 5010;

# include "TSyntaxFileEditor.cc"

void outOfMemory()
{
    messageBox(gettext("Not enough memory for this operation."),
    mfError | mfOKButton );
}

typedef char *_charPtr;
typedef TPoint *PPoint;

ushort execDialog( TDialog *d, void *data )
{
    TView *p = TProgram::application->validView( d );

    if( p == 0 )
    return cmCancel;

    else {
        if( data != 0 )
        p->setData( data );
    
        ushort result = TProgram::deskTop->execView( p );
        
        if( result != cmCancel && data != 0 )
        p->getData( data );
    
        TObject::destroy( p );
        return result;
    }
}

TDialog *createFindDialog()
{
    TDialog *d = new TDialog( TRect( 0, 0, 38, 12 ), "Find" );

    d->options |= ofCentered;

    TInputLine *control = new TInputLine( TRect( 3, 3, 32, 4 ), 80 );
    d->insert( control );
    
    d->insert(new TLabel( TRect( 2, 2, 15, 3 ), gettext("~T~ext to find"), control ) );
    d->insert(new THistory( TRect( 32, 3, 35, 4 ), control, 10 ) );

    d->insert(new TCheckBoxes( TRect( 3, 5, 35, 7 ),
        new TSItem( gettext("~C~ase sensitive"),
        new TSItem( "~W~hole words only", 0 ))));

    d->insert(new TButton( TRect( 14, 9, 24, 11 ), "O~K~", cmOK, bfDefault ) );
    d->insert(new TButton( TRect( 26, 9, 36, 11 ), gettext("Cancel"), cmCancel, bfNormal ) );

    d->selectNext( False );
    return d;
}

TDialog *createReplaceDialog()
{
    TDialog *d = new TDialog( TRect( 0, 0, 40, 16 ), gettext("Replace") );

    d->options |= ofCentered;

    TInputLine *control = new TInputLine( TRect( 3, 3, 34, 4 ), 80 );
    d->insert( control );
    d->insert(
        new TLabel( TRect( 2, 2, 15, 3 ), gettext("~T~ext to find"), control ) );
    d->insert( new THistory( TRect( 34, 3, 37, 4 ), control, 10 ) );

    control = new TInputLine( TRect( 3, 6, 34, 7 ), 80 );
    d->insert( control );
    d->insert( new TLabel( TRect( 2, 5, 12, 6 ), gettext("~N~ew text"), control ) );
    d->insert( new THistory( TRect( 34, 6, 37, 7 ), control, 11 ) );

    d->insert( new TCheckBoxes( TRect( 3, 8, 37, 12 ),
        new TSItem(gettext("~C~ase sensitive"),
        new TSItem("~W~hole words only",
        new TSItem(gettext("~P~rompt on replace"),
        new TSItem(gettext("~R~eplace all"), 0 ))))));

    d->insert( new TButton( TRect( 17, 13, 27, 15 ), "O~K~", cmOK, bfDefault ) );
    d->insert( new TButton( TRect( 28, 13, 38, 15 ),
                            gettext("Cancel"), cmCancel, bfNormal ) );
    d->selectNext( False );
    return d;
}

ushort doEditDialog( int dialog, ... )
{
    va_list arg;
    char buf[256] = {0};
    
    ostrstream os( buf, sizeof( buf )-1 );
    switch( dialog )
    {
        case edOutOfMemory:
        return messageBox(
            gettext("Not enough memory for this operation"),
            mfError | mfOKButton );
            
        case edReadError: {
        va_start( arg, dialog );
            os << gettext("Error reading file ")
               << va_arg( arg, _charPtr )
               << "."
               << ends;
        va_end( arg );
        return messageBox(
            buf,
            mfError | mfOKButton );
        }
        case edWriteError: {
        va_start( arg, dialog );
            os << gettext("Error writing file ") << va_arg( arg,_charPtr )
               << "."
               << ends;
        va_end( arg );
        return messageBox(
            buf,
            mfError | mfOKButton );
        }
        case edCreateError: {
        va_start( arg, dialog );
        os  << gettext("Error creating file ")
            << va_arg( arg, _charPtr )
            << "."
            << ends;
        va_end( arg );
        return messageBox(
        buf,
        mfError | mfOKButton );
        }
        case edSaveModify: {
        va_start( arg, dialog );
          os << va_arg( arg, _charPtr )
             << gettext(" has been modified. Save?")
             << ends;
        va_end( arg );
        return messageBox(
            buf,
            mfInformation | mfYesNoCancel );
        }
        case edSaveUntitled:
        return messageBox( gettext("Save untitled file?"),
                           mfInformation | mfYesNoCancel );
        case edSaveAs: {
        va_start( arg, dialog );
            return execDialog(
            new TFileDialog( "*.*",
                gettext("Save file as"),
                "~N~ame",
                fdOKButton,
                101 ),
        va_arg( arg, _charPtr ) );
        }

        case edFind: {
        va_start( arg, dialog );
        return execDialog(
            createFindDialog(),
            va_arg( arg, _charPtr ) );
        }

        case edSearchFailed:
        return messageBox(
            gettext("Search string not found."),
            mfError | mfOKButton );
            
        case edReplace: {
        va_start( arg, dialog );
        return execDialog(
            createReplaceDialog(),
            va_arg( arg, _charPtr ) );
        }

        case edReplacePrompt: {
        //  Avoid placing the dialog on the same line as the cursor
        TRect r( 0, 1, 40, 8 );
        r.move( (  TProgram::deskTop->size.x-r.b.x)/2, 0 );
        TPoint t = TProgram::deskTop->makeGlobal( r.b );
        t.y++;
        
        va_start( arg, dialog );
            TPoint *pt = va_arg( arg, PPoint );
            if( pt->y <= t.y )
            r.move( 0, TProgram::deskTop->size.y - r.b.y - 2 );
        va_end( arg );
        
        return messageBoxRect(
            r, gettext("Replace this occurence?"),
            mfYesNoCancel | mfInformation );
        }
    }
    return cmCancel;
}

// -----------------------------------------------------------------
// green color palette for information window:
// -----------------------------------------------------------------
#define cpGreenDialog \
    "\x75\x75\x75\x73\x74\x75\x76\x77\x75\x74\x7a\x7b\x74\x75\x12\x6f"\
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"
        
// -----------------------------------------------------------------
// information window buttons implementation ...
// -----------------------------------------------------------------
class TMyButton : public TButton {
public:
    TMyButton(const TRect& bounds, const char* text, ushort cmd, ushort aOptions) :
    TButton(bounds, text, cmd, aOptions) {}
    
    TColorAttr mapColor(uchar index) noexcept {
        switch (index) {
            case  1:  return {0xffff00, 0x008000};
            case  2:  return {0xffff00, 0x008000};
            case  3:  return {0x0000ff, 0xffff00};
            case  4:  return {0x438939, 0x091297};
            case  5:  return {0x438939, 0x091297};
            case  6:  return {0x438939, 0x091297};
            case  7:  return {0x438939, 0x091297};
            case  8:  return {0x000000, 0x32cd32};  // shadow
            default:  return errorAttr;
        }
    }
};

// -----------------------------------------------------------------
// editor for source files ...
// -----------------------------------------------------------------
class TMyTvEditor : public TDialog {
public:
    class MyEditorChild: public TSyntaxFileEditor {
    public:
        MyEditorChild(
            TMyTvEditor* parent,
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
        TMyTvEditor * owner;
    };

    ~TMyTvEditor() {
    }
    TMyTvEditor(const TRect& bounds):
        TWindowInit(&TMyTvEditor::initFrame),
        TDialog(bounds, "Mein Fenster") {
        palette = dpBlueDialog;

        insert(hScrollBar = new TScrollBar( TRect( 18, size.y - 1, size.x - 23, size.y     ) ));
        insert(vScrollBar = new TScrollBar( TRect( size.x - 23, 1, size.x - 22, size.y - 1 ) ));
        insert(indicator  = new TIndicator( TRect(  2, size.y - 1,          16, size.y     ) ));
        
        insert(editor = new MyEditorChild(this,
            TRect(1, 1, size.x - 24, size.y - 1),
            hScrollBar,
            vScrollBar,
            indicator,
            "www.txt"));

        insert(button1 = new TButton(TRect(size.x - 21, 2, size.x - 3, 4), "Start",   cmButton1, bfNormal));
        insert(button2 = new TButton(TRect(size.x - 21, 5, size.x - 3, 7), "Compile", cmButton2, bfNormal));
        
        options   |= ofSelectable;
        eventMask |= evBroadcast; // for get word under cursor
        
        drawView();
    }
    // -------------------------------
    // event handler ...
    // -------------------------------
    void handleEvent(TEvent & event ){
        TWindow::handleEvent( event );
        if (event.what == evCommand) {
            switch (event.message.command) {
                case cmClose:
                    close();
                    clearEvent(event);
                    break;
                case cmButton1:
                    // Aktion für Schaltfläche 1
                    break;
                case cmButton2:
                    // Aktion für Schaltfläche 2
                    break;
            }
        }
    }

private:
    MyEditorChild * editor;
    TIndicator    * indicator;
    
    TScrollBar    * vScrollBar;
    TScrollBar    * hScrollBar;
    
    TButton       * button1;
    TButton       * button2;
};

// -----------------------------------------------------------------
// window for global information output's ...
// -----------------------------------------------------------------
class TMyTvInfoWindow : public TDialog {
public:
    class MyEditorChild: public TSyntaxFileEditor {
    public:
        MyEditorChild(
        TMyTvInfoWindow * parent,
        const TRect     & bounds,
        TScrollBar      * hScrollBar,
        TScrollBar      * vScrollBar,
        TIndicator      * indicator,
        TStringView       filename):
        TSyntaxFileEditor( bounds,hScrollBar,vScrollBar,indicator,"www.txt"),
        owner(parent) {
        
            EditorTextColor    = 0x20;          // green on black
            EditorCommentColor = 0x21;          // green on blze
        
            // ----------------------------------------------
            // standard pascal token color map ...
            // ----------------------------------------------
            std::map< std::string, TColorAttr > ErrorToken =
            {
                { "info",     0x2f },    // 0x2f = green on white
                { "debug",    0x2f },    // 0x2f = green on white
                { "warning",  0x2f },    // 0x2f = green on white
                { "error",    0x2f }     // 0x2f = green on white
            };
            EditorSyntaxToken = ErrorToken;
        }
        // -------------------------------
        // event handler ...
        // -------------------------------
        void handleEvent( TEvent &event )
        {
            TEditor::handleEvent( event );
            if (event.what            == evBroadcast
            &&  event.message.command == cmGetFocusedEditor
            && (state & sfFocused)) {
                clearEvent(event);
            }   else
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
                    //messageBox("getkey F2",mfInformation|mfOKButton);
                    messageBox(getWordUnderCursor().c_str(), mfInformation|mfOKButton);
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
        TMyTvInfoWindow * owner;
    };
    
    // -------------------------------
    // dtor: free allocated memory:
    // -------------------------------
    ~TMyTvInfoWindow() {
        TObject::destroy(button2);
        TObject::destroy(button1);
        
        TObject::destroy(hScrollBar);
        TObject::destroy(vScrollBar);
        
        TObject::destroy(indicator);
        TObject::destroy(editor);
    }
    
    // -------------------------------
    // ctor: create information window
    // -------------------------------
    TMyTvInfoWindow(const TRect& bounds):
        TWindowInit(&TMyTvInfoWindow::initFrame),
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
        
        insert(button1 = new TMyButton(TRect( size.x - 19, 2, size.x - 4, 4 ), "Clear", cmButtonInfoWindow1, bfNormal));
        insert(button2 = new TMyButton(TRect( size.x - 19, 4, size.x - 4, 6 ), "Copy" , cmButtonInfoWindow2, bfNormal));

    }
    // -------------------------------
    // event handler ...
    // -------------------------------
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
    
    // --------------------------------------------------
    // set the "green" style, depend on the palette items
    // --------------------------------------------------
    virtual TPalette& getPalette() const {
        static TPalette palette( cpGreenDialog, sizeof(cpGreenDialog)-1 );
        return palette;
    }
    
    // -------------------------------
    // insert text to the info window
    // -------------------------------
    bool insertText(const void* text, uint length) {
        if (editor) {
            editor->insertText(text,length,false);
            return true;
        }
        return false;
    }

private:
    MyEditorChild * editor;
    TIndicator    * indicator;

    TScrollBar    * vScrollBar;
    TScrollBar    * hScrollBar;
    
    TMyButton     * button1;
    TMyButton     * button2;
};

// -----------------------------------------------------------------
// create the editor view ...
// -----------------------------------------------------------------
void TVDemo::tvEditor()
{
    TMyTvEditor *editor = (TMyTvEditor *) validView(
    new TMyTvEditor(TRect(0, 0, 81, 23)));

    if (editor != nullptr) {
        editor->helpCtx = hcCalendar;
        deskTop->insert( editor );
    }
}

// -----------------------------------------------------------------
// create the information window view.
// -----------------------------------------------------------------
static TMyTvInfoWindow * info_message_window = nullptr;
void TVDemo::create_info_window()
{
    info_message_window = (TMyTvInfoWindow*) validView(
    new TMyTvInfoWindow(
        TRect(    2,
        size.y - 10,
        size.x -  4,
        size.y -  3)));

    if (info_message_window != nullptr) {
        info_message_window->helpCtx = hcCalendar;
        deskTop->insert( info_message_window );
    }
}

// -----------------------------------------------------------------
// this function is a external helper, to insert exception text into
// the information window ...
// -----------------------------------------------------------------
void TVDemo::put_exception_message(const char* text)
{
    info_message_window->insertText(text,strlen(text));
}
