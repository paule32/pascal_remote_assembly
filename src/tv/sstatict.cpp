/*------------------------------------------------------------*/
/* filename -       sstatict.cpp                              */
/*                                                            */
/* Registeration object for the class TStaticText             */
/*------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(NO_STREAMABLE)
#define Uses_TStaticText
#define Uses_TStreamableClass
#include <tvision/tv.h>

TStreamableClass RStaticText( TStaticText::name,
                              TStaticText::build,
                              __DELTA(TStaticText)
                            );

#endif
