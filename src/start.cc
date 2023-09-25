// -----------------------------------------------------------------
// File:   start.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include "Parser.h"
# include "AnsiColor.h"

// -----------------------------------------------------------------
// global used namespaces ...
// -----------------------------------------------------------------
using namespace std;

// -----------------------------------------------------------------
// global variable's/declaration's ...
// -----------------------------------------------------------------
Parser    * parser = nullptr;
AnsiColor * ansi   = nullptr;

// -----------------------------------------------------------------
// console command line: main entry point:
// -----------------------------------------------------------------
int main(int argc, char **argv)
{
    uint8_t result = 1;

    // ------------------------------------------------------------
    // you must be append a file that should be parsed after the
    // command line tool input.
    // ------------------------------------------------------------
    try
    {
        ansi = new AnsiColor();
 
        // --------------------------------------------------------
        // check arguments, if a input file was found.
        // --------------------------------------------------------
        if (argc < 2)
        throw EPascalException_Argument("no input file given.");

        // --------------------------------------------------------
        // start the race run ...
        // --------------------------------------------------------
        parser = new Parser( argv[1] );
        parser->yyparse();

        // ------------------------------------------------------------
        // after all, close opened file handles, and try to free memory
        // ------------------------------------------------------------
        delete parser;
        delete ansi;
        
        result = 0;
    }
    catch (EPascalException_Argument &e) {
        cerr << ansi->Normal.red  () << "exception:"         << endl
             << ansi->Normal.cyan () << "what: Argument:"    << endl
             << ansi->Normal.white() << "Text: " << e.what() << endl
             ;
        if (nullptr != parser)
        delete parser;
        delete ansi;
    }
    catch (exception &e) {
        cerr << ansi->Normal.red  () << "exception:" << endl
             << ansi->Normal.cyan () << "what: any:" << endl
             << ansi->Normal.white() << "Text: "     << e.what() << endl
             ;
        if (nullptr != parser)
        delete parser;
        delete ansi;
    }
    catch (...) {
        cerr << ansi->Normal.red  () << "exception:"    << endl
             << ansi->Normal.cyan () << "what: common:" << endl
             << ansi->Normal.white() << "Text: none."   << endl
             ;
        if (nullptr != parser)
        delete parser;
        delete ansi;
    }   return result;
}
