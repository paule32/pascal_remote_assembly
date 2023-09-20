// -----------------------------------------------------------------
// File:   start.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include "Parser.h"

// -----------------------------------------------------------------
// global used namespaces ...
// -----------------------------------------------------------------
using namespace std;

// -----------------------------------------------------------------
// global variable's/declaration's ...
// -----------------------------------------------------------------
Parser *parser = nullptr;

extern void create_output();

// -----------------------------------------------------------------
// console command line: main entry point:
// -----------------------------------------------------------------
int main(int argc, char **argv)
{
    // ------------------------------------------------------------
    // you must be append a file that should be parsed after the
    // command line tool input.
    // ------------------------------------------------------------

    // --------------------------------------------------------
    // check arguments, if a input file was found.
    // --------------------------------------------------------
    if (argc < 2) {
        cerr << "error: no input file given." << endl;
        return 1;
    }

    // --------------------------------------------------------
    // start the race run ...
    // --------------------------------------------------------
    parser = new Parser( argv[1] );
    parser->yyparse();

    // ------------------------------------------------------------
    // after all, close opened file handles, and try to free memory
    // ------------------------------------------------------------
    delete parser;
    
    create_output();
    
    return 0;
}
