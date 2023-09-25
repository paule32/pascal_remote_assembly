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

char * locale_utf8;

// -----------------------------------------------------------------
// console command line: main entry point:
// -----------------------------------------------------------------
int main(int argc, char **argv)
{
    uint8_t result = 1;

    // -------------------------------------------------------------
    // you must be append a file that should be parsed after the
    // command line tool input.
    // -------------------------------------------------------------
    try
    {
        // ---------------------------------------------------------
        // perform pre-tasks: de-compress the locale file:
        // ---------------------------------------------------------
        try {
            LCID lcid = 0;
            if (GetLocaleInfoEx(
                LOCALE_NAME_USER_DEFAULT,
                LOCALE_RETURN_NUMBER | LOCALE_ILANGUAGE,
                (LPWSTR)&lcid,
                sizeof(lcid)) < 2)
            throw std::string(_("can not get locale, use default en-en."));

            // -----------------------------------------------------
            // first supported locale is german: de_DE-UTF8 ...
            // -----------------------------------------------------
            if (lcid == 0x0407) {
                struct stat buffer;
                if (stat("locales/de_DE/LC_MESSAGES/de_DE_utf8.mo.gz",
                    &buffer) == 1)
                throw std::string(_("localization de_DE does not exists."));

                // store name, for delete it later ...
                locale_utf8 = strdup("de");

                system("gzip -d -c "
                "locales/de_DE/LC_MESSAGES/de_DE_utf8.mo.gz >"
                "locales/de_DE/LC_MESSAGES/de_DE_utf8.mo");
                
                // -----------------------------------------------------
                // try to bind de_DE locale as default ...
                // -----------------------------------------------------
                setlocale(LC_ALL,"");
                bindtextdomain("de_DE_utf8", "locales");
                textdomain("de_DE_utf8");
            }   else
            throw std::string(_("detected locale not supported."));
        }
        // ---------------------------------------------------------
        // de_DE_utf8.mo not found, use english locale ...
        // ---------------------------------------------------------
        catch (std::string &e) {
            struct stat buffer;
            if (stat("locales/en_US/LC_MESSAGES/en_US_utf8.mo.gz",
            &buffer) == 1)
            {
                std::cerr << _("localization en_US does not exists.") <<
                std::endl;
            }
            else {
                // store name, for delete it later ...
                locale_utf8 = strdup("en");
                
                system("gzip -d -c "
                "locales/en_US/LC_MESSAGES/en_US_utf8.mo.gz >"
                "locales/en_US/LC_MESSAGES/en_US_utf8.mo");
                
                // ------------------------------------------------
                // try to bind de_DE locale as default ...
                // ------------------------------------------------
                setlocale(LC_ALL,"");
                bindtextdomain("en_US_utf8", "locales");
                textdomain("en_US_utf8");
            }
        }

        ansi = new AnsiColor();
 
        // ---------------------------------------------------------
        // check arguments, if a input file was found.
        // ---------------------------------------------------------
        if (argc < 2)
        throw EPascalException_Argument(_("no input file given."));

        // ---------------------------------------------------------
        // start the race run ...
        // ---------------------------------------------------------
        parser = new Parser( argv[1] );
        parser->yyparse();

        // ------------------------------------------------------------
        // after all, close opened file handles, and try to free memory
        // ------------------------------------------------------------
        parser_cleanup();
        result = EXIT_SUCCESS;
    }
    catch (EPascalException_Argument &e) {
        cerr << ansi->Normal.red  () << _("exception:")         << endl
             << ansi->Normal.cyan () << _("what: Argument:")    << endl
             << ansi->Normal.white() << _("Text: ") << e.what() << endl
             ;
        parser_cleanup();
    }
    catch (exception &e) {
        cerr << ansi->Normal.red  () << _("exception:") << endl
             << ansi->Normal.cyan () << _("what: any:") << endl
             << ansi->Normal.white() << _("Text: ")     << e.what() << endl
             ;
        parser_cleanup();
    }
    catch (...) {
        cerr << ansi->Normal.red  () << _("exception:")    << endl
             << ansi->Normal.cyan () << _("what: common:") << endl
             << ansi->Normal.white() << _("Text: none.")   << endl
             ;
        parser_cleanup();
    }   return result;
}
