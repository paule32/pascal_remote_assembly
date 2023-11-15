/*------------------------------------------------------------*/
/* filename -       slstview.cpp                              */
/*                                                            */
/* Registeration object for the class TListViewer             */
/*------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(NO_STREAMABLE)
#define Uses_TListViewer
#define Uses_TStreamableClass
#include <tvision/tv.h>

TStreamableClass RListViewer( TListViewer::name,
                              TListViewer::build,
                              __DELTA(TListViewer)
                            );
#endif

