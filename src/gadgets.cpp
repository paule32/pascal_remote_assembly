/*-------------------------------------------------------------------*/
/*                                                                   */
/*   Turbo Vision Demo                                               */
/*                                                                   */
/*   Gadgets.cpp:  Gadgets for the Turbo Vision Demo.  Includes a    */
/*        heap view and a clock view which display the clock at the  */
/*        right end of the menu bar and the current heap space at    */
/*        the right end of the status line.                          */
/*                                                                   */
/*-------------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#define Uses_TRect
#define Uses_TView
#define Uses_TDrawBuffer
#include <tvision/tv.h>

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <iomanip>

using std::resetiosflags;
using std::setiosflags;
using std::setbase;
using std::setfill;
using std::setprecision;
using std::setw;

#include <strstream>
#include <ostream>

using std::ends;
using std::istrstream;
using std::ostrstream;
using std::strstream;
using std::strstreambuf;

#include <malloc.h>
#include <time.h>

#include "gadgets.h"

//extern "C" unsigned long farcoreleft( void );

//
// ------------- Heap Viewer functions
//

THeapView::THeapView(TRect& r) : TView( r )
{
    oldMem = 0;
    newMem = heapSize();
}


void THeapView::draw()
{
    TDrawBuffer buf;
    TColorAttr c = getColor(2);

    buf.moveChar(0, ' ', c, (short)size.x);
    buf.moveStr(0, heapStr, c);
    writeLine(0, 0, (short)size.x, 1, buf);
}


void THeapView::update()
{
    if( (newMem = heapSize()) != oldMem )
        {
        oldMem = newMem;
        drawView();
        }
}


long THeapView::heapSize()
{
    ostrstream totalStr( heapStr, sizeof heapStr);

    // mallinfo is defined in malloc.h but only exists in Glibc.
    // It doesn't exactly measure the heap size, but it kinda does the trick.
    totalStr << ends;
    return 0;

}


//
// -------------- Clock Viewer functions
//

TClockView::TClockView( TRect& r ) : TView( r )
{
    strcpy(lastTime, "        ");
    strcpy(curTime, "        ");
}


void TClockView::draw()
{
    TDrawBuffer buf;
    TColorAttr c = getColor(2);

    buf.moveChar(0, ' ', c, (short)size.x);
    buf.moveStr(0, curTime, c);
    writeLine(0, 0, (short)size.x, 1, buf);
}


void TClockView::update()
{
    time_t t = time(0);
    char *date = ctime(&t);

    date[19] = '\0';
    strcpy(curTime, &date[11]);        /* Extract time. */

    if( strcmp(lastTime, curTime) )
        {
        drawView();
        strcpy(lastTime, curTime);
        }
}

