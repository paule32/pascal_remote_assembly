
#pragma once
#define __EVENT_CODES

/* Event codes */

const int evMouseDown = 0x0001;
const int evMouseUp   = 0x0002;
const int evMouseMove = 0x0004;
const int evMouseAuto = 0x0008;
const int evMouseWheel= 0x0020;
const int evKeyDown   = 0x0010;
const int evCommand   = 0x0100;
const int evBroadcast = 0x0200;

/* Event masks */

const int evNothing   = 0x0000;
const int evMouse     = 0x002f;
const int evKeyboard  = 0x0010;
const int evMessage   = 0xFF00;

/* Mouse button state masks */

const int mbLeftButton  = 0x01;
const int mbRightButton = 0x02;
const int mbMiddleButton= 0x04;

/* Mouse wheel state masks */

const int mwUp      = 0x01;
const int mwDown    = 0x02;
const int mwLeft    = 0x04;
const int mwRight   = 0x08;

/* Mouse event flags */

#if !defined( __WINDOWS_H )
#include <tvision/compat/windows/windows.h>
#endif
const int meMouseMoved = MOUSE_MOVED;       // NT values from WINDOWS.H
const int meDoubleClick = DOUBLE_CLICK;

// 0x04 and 0x08 are reserved by NT (MOUSE_WHEELED, MOUSE_HWHEELED).
const int meTripleClick = 0x10;

#define __TEvent

struct MouseEventType
{
    TPoint where;
    ushort eventFlags;          // Replacement for doubleClick.
    ushort controlKeyState;
    uchar buttons;
    uchar wheel;
};

class THWMouse
{

protected:

    THWMouse() noexcept;
    THWMouse( const THWMouse& ) noexcept {};
    ~THWMouse();
public:
    static void show() noexcept;
    static void hide() noexcept;
protected:
    static void setRange( ushort, ushort ) noexcept;
    static void getEvent( MouseEventType& ) noexcept;
    static Boolean present() noexcept;

    static void suspend() noexcept;
    static void resume() noexcept;
    static void inhibit() noexcept;

protected:

    static uchar _NEAR buttonCount;

private:

    static Boolean _NEAR handlerInstalled;
    static Boolean _NEAR noMouse;

};

inline Boolean THWMouse::present() noexcept
{
    return Boolean( buttonCount != 0 );
}

inline void THWMouse::inhibit() noexcept
{
    noMouse = True;
}

class TMouse : public THWMouse
{

public:

    TMouse() noexcept;
    ~TMouse();

    static void show() noexcept;
    static void hide() noexcept;

    static void setRange( ushort, ushort ) noexcept;
    static void getEvent( MouseEventType& ) noexcept;
    static Boolean present() noexcept;

    static void suspend() noexcept { THWMouse::suspend(); }
    static void resume() noexcept { THWMouse::resume(); }

};

inline void TMouse::show() noexcept
{
    THWMouse::show();
}

inline void TMouse::hide() noexcept
{
    THWMouse::hide();
}

inline void TMouse::setRange( ushort rx, ushort ry ) noexcept
{
    THWMouse::setRange( rx, ry );
}

inline void TMouse::getEvent( MouseEventType& me ) noexcept
{
    THWMouse::getEvent( me );
}

inline Boolean TMouse::present() noexcept
{
    return THWMouse::present();
}

struct CharScanType
{
    uchar charCode;
    uchar scanCode;
};

struct KeyDownEvent
{
    union
        {
        ushort keyCode;
        CharScanType charScan;
        };
    ushort controlKeyState;
    char text[4];               // NOT null-terminated.
    uchar textLength;

    TStringView getText() const;
    operator TKey() const;
};

inline TStringView KeyDownEvent::getText() const
{
    return TStringView(text, textLength);
}

inline KeyDownEvent::operator TKey() const
{
    return TKey(keyCode, controlKeyState);
}

struct MessageEvent
{
    ushort command;
    union
        {
        void *infoPtr;
        int32_t infoLong;
        ushort infoWord;
        short infoInt;
        uchar infoByte;
        char infoChar;
        };
};

struct TEvent
{
    ushort what;
    union
    {
        MouseEventType mouse;
        KeyDownEvent keyDown;
        MessageEvent message;
    };

    void getMouseEvent() noexcept;
    void getKeyEvent() noexcept;
    static void waitForEvent(int timeoutMs) noexcept;
    static void putNothing() noexcept;
};

#define __TEventQueue

class TEventQueue
{
public:
    TEventQueue() noexcept;
    ~TEventQueue();

    static void getMouseEvent( TEvent& ) noexcept;
    static void getKeyEvent( TEvent& ) noexcept;
    static void suspend() noexcept;
    static void resume() noexcept;
    static void waitForEvent( int ) noexcept;

    friend class TView;
    friend class TProgram;
    friend void genRefs();

    static ushort _NEAR doubleDelay;
    static Boolean _NEAR mouseReverse;

    static void putPaste( TStringView ) noexcept;

private:

    static TMouse * _NEAR mouse;
    static Boolean getMouseState( TEvent& ) noexcept;
    static Boolean getPasteEvent( TEvent& ) noexcept;
    static void getKeyOrPasteEvent( TEvent& ) noexcept;
    static Boolean readKeyPress( TEvent& ) noexcept;

#define __MOUSEHUGE

    static void __MOUSEHUGE mouseInt();

    static MouseEventType _NEAR lastMouse;
public:
    static MouseEventType _NEAR curMouse;
private:
    static MouseEventType _NEAR downMouse;
    static ushort _NEAR downTicks;

    static Boolean _NEAR mouseEvents;
    static Boolean _NEAR pendingMouseUp;

    static ushort _NEAR repeatDelay;
    static ushort _NEAR autoTicks;
    static ushort _NEAR autoDelay;

    static char * _FAR pasteText;
    static size_t _NEAR pasteTextLength;
    static size_t _NEAR pasteTextIndex;

    static TEvent _NEAR keyEventQueue[ keyEventQSize ];
    static size_t _NEAR keyEventCount;
    static size_t _NEAR keyEventIndex;
    static Boolean _NEAR keyPasteState;
};

inline void TEvent::getMouseEvent() noexcept
{
    TEventQueue::getMouseEvent( *this );
}

#define __TTimerQueue

typedef uint64_t TTimePoint;

struct _FAR TTimer;

class TTimerQueue
{
public:

    TTimerQueue() noexcept;
    TTimerQueue(TTimePoint (&getTimeMs)()) noexcept;
    ~TTimerQueue();

    TTimerId setTimer(uint32_t timeoutMs, int32_t periodMs = -1);
    void killTimer(TTimerId id);
    void collectTimeouts(void (&func)(TTimerId, void *), void *args);
    int32_t timeUntilTimeout();

private:

    TTimePoint (&getTimeMs)();
    TTimer *first;
};

#define __TClipboard

class TClipboard
{
public:

    ~TClipboard();

    static void setText(TStringView text) noexcept;
    static void requestText() noexcept;

private:

    TClipboard();

    static TClipboard instance;
    static char *localText;
    static size_t localTextLength;
};

#define __TScreen


class TDisplay
{

public:

    friend class TView;

    enum videoModes
        {
        smBW80      = 0x0002,
        smCO80      = 0x0003,
        smMono      = 0x0007,
        smFont8x8   = 0x0100,
        smColor256  = 0x0200,
        smColorHigh = 0x0400,
        smChanged   = 0x1000
        };

    static void clearScreen( uchar, uchar ) noexcept;

    static void setCursorType( ushort ) noexcept;
    static ushort getCursorType() noexcept;

    static ushort getRows() noexcept;
    static ushort getCols() noexcept;

    static void setCrtMode( ushort ) noexcept;
    static ushort getCrtMode() noexcept;

protected:

    TDisplay() noexcept { updateIntlChars(); };
    TDisplay( const TDisplay& ) noexcept { updateIntlChars(); };
    ~TDisplay() {};

private:

    static void updateIntlChars() noexcept;

};

class TScreen : public TDisplay
{

public:

    TScreen() noexcept;
    ~TScreen();

    static void setVideoMode( ushort mode ) noexcept;
    static void clearScreen() noexcept;
    static void flushScreen() noexcept;

    static ushort _NEAR startupMode;
    static ushort _NEAR startupCursor;
    static ushort _NEAR screenMode;
    static ushort _NEAR screenWidth;
    static ushort _NEAR screenHeight;
    static Boolean _NEAR hiResScreen;
    static Boolean _NEAR checkSnow;
    static TScreenCell * _NEAR screenBuffer;
    static ushort _NEAR cursorLines;
    static Boolean _NEAR clearOnSuspend;

    static void setCrtData() noexcept;
    static ushort fixCrtMode( ushort ) noexcept;

    static void suspend() noexcept;
    static void resume() noexcept;

};


#define __TSystemError

class _FAR TDrawBuffer;

struct TPMRegs
{
    unsigned long di, si, bp, dummy, bx, dx, cx, ax;
    unsigned flags, es, ds, fs, gs, ip, cs, sp, ss;
};

class TSystemError
{

public:

    TSystemError() noexcept;
    ~TSystemError();

    static Boolean _NEAR ctrlBreakHit;

    static void suspend() noexcept;
    static void resume() noexcept;

private:

    static Boolean _NEAR saveCtrlBreak;

};

