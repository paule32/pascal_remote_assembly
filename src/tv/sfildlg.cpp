/*------------------------------------------------------------*/
/* filename -       sfildlg.cpp                               */
/*                                                            */
/* Registeration object for the class TFileDialog             */
/*------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(NO_STREAMABLE)
#define Uses_TFileDialog
#define Uses_TStreamableClass
#include <tvision/tv.h>

TStreamableClass RFileDialog( TFileDialog::name,
                              TFileDialog::build,
                              __DELTA(TFileDialog)
                            );
#endif

