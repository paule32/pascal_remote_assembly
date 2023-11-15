/*------------------------------------------------------------*/
/* filename -       schdrdlg.cpp                              */
/*                                                            */
/* Registeration object for the class TChDirDialog            */
/*------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(NO_STREAMABLE)
#define Uses_TChDirDialog
#define Uses_TStreamableClass
#include <tvision/tv.h>

TStreamableClass RChDirDialog( TChDirDialog::name,
                               TChDirDialog::build,
                               __DELTA(TChDirDialog)
                             );
#endif
