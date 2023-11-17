// -----------------------------------------------------------------
// File:   tvEditor.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------

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

TDialog *createFindDialog()
{
    TDialog *d = new TDialog( TRect( 0, 0, 38, 12 ), "Find" );

    d->options |= ofCentered;

    TInputLine *control = new TInputLine( TRect( 3, 3, 32, 4 ), 80 );
    d->insert( control );
    d->insert(
        new TLabel( TRect( 2, 2, 15, 3 ), gettext("~T~ext to find"), control ) );
    d->insert(
        new THistory( TRect( 32, 3, 35, 4 ), control, 10 ) );

    d->insert( new TCheckBoxes( TRect( 3, 5, 35, 7 ),
        new TSItem( gettext("~C~ase sensitive"),
        new TSItem( "~W~hole words only", 0 ))));

    d->insert(
        new TButton( TRect( 14, 9, 24, 11 ), "O~K~", cmOK, bfDefault ) );
    d->insert(
        new TButton( TRect( 26, 9, 36, 11 ), gettext("Cancel"), cmCancel, bfNormal ) );

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

    d->insert(
        new TButton( TRect( 17, 13, 27, 15 ), "O~K~", cmOK, bfDefault ) );
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
            return messageBox( gettext("Not enough memory for this operation"),
                               mfError | mfOKButton );
        case edReadError:
            {
            va_start( arg, dialog );
            os << gettext("Error reading file ") << va_arg( arg, _charPtr )
               << "." << ends;
            va_end( arg );
            return messageBox( buf, mfError | mfOKButton );
            }
        case edWriteError:
            {
            va_start( arg, dialog );
            os << gettext("Error writing file ") << va_arg( arg,_charPtr )
               << "." << ends;
            va_end( arg );
            return messageBox( buf, mfError | mfOKButton );
            }
        case edCreateError:
            {
            va_start( arg, dialog );
            os << gettext("Error creating file ") << va_arg( arg, _charPtr )
               << "." << ends;
            va_end( arg );
            return messageBox( buf, mfError | mfOKButton );
            }
        case edSaveModify:
            {
            va_start( arg, dialog );
            os << va_arg( arg, _charPtr )
               << gettext(" has been modified. Save?") << ends;
            va_end( arg );
            return messageBox( buf, mfInformation | mfYesNoCancel );
            }
        case edSaveUntitled:
            return messageBox( gettext("Save untitled file?"),
                               mfInformation | mfYesNoCancel );
        case edSaveAs:
            {
            va_start( arg, dialog );
            return execDialog( new TFileDialog( "*.*",
                                                gettext("Save file as"),
                                                "~N~ame",
                                                fdOKButton,
                                                101 ), va_arg( arg, _charPtr ) );
            }

        case edFind:
            {
            va_start( arg, dialog );
            return execDialog( createFindDialog(), va_arg( arg, _charPtr ) );
            }

        case edSearchFailed:
            return messageBox( gettext("Search string not found."),
                               mfError | mfOKButton );
        case edReplace:
            {
            va_start( arg, dialog );
            return execDialog( createReplaceDialog(), va_arg( arg, _charPtr ) );
            }

        case edReplacePrompt:
            //  Avoid placing the dialog on the same line as the cursor
            TRect r( 0, 1, 40, 8 );
            r.move( (TProgram::deskTop->size.x-r.b.x)/2, 0 );
            TPoint t = TProgram::deskTop->makeGlobal( r.b );
            t.y++;
            va_start( arg, dialog );
            TPoint *pt = va_arg( arg, PPoint );
            if( pt->y <= t.y )
                r.move( 0, TProgram::deskTop->size.y - r.b.y - 2 );
            va_end( arg );
            return messageBoxRect( r, gettext("Replace this occurence?"),
                                   mfYesNoCancel | mfInformation );

        }

    return cmCancel;
}

class TMyTvEditor : public TDialog {
public:
    class MyEditorChild: public TFileEditor {
    public:
        MyEditorChild(
            TMyTvEditor* parent,
            const TRect& bounds,
            TScrollBar * hScrollBar,
            TScrollBar * vScrollBar,
            TIndicator * indicator,
            TStringView  filename):
            TFileEditor( bounds,hScrollBar,vScrollBar,indicator,filename),
            owner(parent) {
                EditorTextColor    = 0x1e;
                EditorCommentColor = 0x40;
            }
        void handleEvent( TEvent &event )
        {
            TFileEditor::handleEvent( event );
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

        hScrollBar = new TScrollBar( TRect( 18, size.y - 1, size.x - 23, size.y ) );
        insert(hScrollBar);

        vScrollBar = new TScrollBar( TRect( size.x - 23, 1, size.x - 22, size.y - 1 ) );
        insert(vScrollBar);

        indicator = new TIndicator( TRect( 2, size.y - 1, 16, size.y) );
        insert(indicator);
        
        editor = new MyEditorChild(this, TRect(1, 1, size.x - 24, size.y - 1), hScrollBar, vScrollBar, indicator, "www.txt");
        insert(editor);

        button1 = new TButton(TRect(size.x - 21, 2, size.x - 3, 4), "Start", cmButton1, bfNormal);
        insert(button1);

        button2 = new TButton(TRect(size.x - 21, 5, size.x - 3, 7), "Compile", cmButton2, bfNormal);
        insert(button2);
        
        options |= ofSelectable;
        
        drawView();
    }

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

#define cpGreenDialog \
        "\x11\x75\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f"\
        "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"

class TMyTvInfoWindow : public TDialog {
public:
    class MyEditorChild: public TEditor {
    public:
        MyEditorChild(
        TMyTvInfoWindow * parent,
        const TRect     & bounds,
        TScrollBar      * hScrollBar,
        TScrollBar      * vScrollBar,
        TIndicator      * indicator,
        TStringView       filename):
        TEditor( bounds,hScrollBar,vScrollBar,indicator,999999999),
        owner(parent) {
        std::map< std::string, TColorAttr > PascalToken =
        {
            { "program",        0x2f },    // 0x2f = green on white
            
            { "array",          0x2f },
            { "begin",          0x2f },
            { "byte",           0x2f },
            { "case",           0x2f },
            { "char",           0x2f },
            { "class",          0x2f },
            { "do",             0x2f },
            { "dec",            0x2f },
            { "else",           0x2f },
            { "end",            0x2f },
            { "for",            0x2f },
            { "if",             0x2f },
            { "implementation", 0x2f },
            { "inc",            0x2f },
            { "integer",        0x2f },
            { "interface",      0x2f },
            { "of",             0x2f },
            { "record",         0x2f },
            { "string",         0x2f },
            { "then",           0x2f },
            { "unit",           0x2f },
            { "until",          0x2f },
            { "uses",           0x2f },
            { "while",          0x2f },
            { "word",           0x2f }
        };
        EditorSyntaxToken  = PascalToken;   // use Pascal Highlighter
        
        EditorTextColor    = 0x20;          // green on black
        EditorCommentColor = 0x21;          // green on blze
    }
    void handleEvent( TEvent &event )
        {
            TEditor::handleEvent( event );
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
        TMyTvInfoWindow * owner;
    };
    
    ~TMyTvInfoWindow() {
    }
    TMyTvInfoWindow(const TRect& bounds):
        TWindowInit(&TMyTvInfoWindow::initFrame),
        TDialog(bounds, "Info window") {
        
        hScrollBar = new TScrollBar( TRect( 18, size.y - 1, size.x - 23, size.y ) );
        insert(hScrollBar);

        vScrollBar = new TScrollBar( TRect( size.x - 23, 1, size.x - 22, size.y - 1 ) );
        insert(vScrollBar);

        indicator = new TIndicator( TRect( 2, size.y - 1, 16, size.y) );
        insert(indicator);
        
        editor = new MyEditorChild(this, TRect(2, 1, size.x - 24, size.y - 1), hScrollBar, vScrollBar, indicator, "www.txt");
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
    virtual TPalette& getPalette() const {
        static TPalette palette( cpGreenDialog, sizeof(cpGreenDialog)-1 );
        return palette;
    }

private:
    MyEditorChild * editor;
    TIndicator    * indicator;

    TScrollBar    * vScrollBar;
    TScrollBar    * hScrollBar;
};

void TVDemo::tvEditor()
{
    TMyTvEditor *editor = (TMyTvEditor *) validView(
    new TMyTvEditor(TRect(0, 0, 81, 23)));

    if (editor != nullptr) {
        editor->helpCtx = hcCalendar;
        deskTop->insert( editor );
    }
}

void TVDemo::create_info_window()
{
    TMyTvInfoWindow *p = (TMyTvInfoWindow*) validView(
    new TMyTvInfoWindow(TRect(2,size.y-10,size.x-4,size.y-3)));

    if (p != nullptr) {
        p->helpCtx = hcCalendar;
        deskTop->insert( p );
    }
}
