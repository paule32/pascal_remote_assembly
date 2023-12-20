%{
// -----------------------------------------------------------------
// File:   dBase.lex
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <windows.h>

# include <stdio.h>
# include <libintl.h>
# include <locale.h>
# include <stdlib.h>

# undef __FLAT__
# include <strings.h>

# include <iostream>
# include <sstream>
# include <cstring>
# include <string>
# include <algorithm>

# include "Parser.h"

extern "C" {
    # include "dBaseParser.hh"
    
    int  DBASE_line=1,DBASE_column=1;

    int  DBASElex   (void );
    int  DBASEwrap  (void ) { return 1; }
    void DBASEerror (const char * msg) {
        std::cerr << "error: " << (DBASE_line-1) << ": " << msg << std::endl;
        exit(1);
    }
};

# define _(String) gettext(String)

extern std::stringstream output_stream;
extern std::stringstream output_stream_labels;

%}

ident       [a-zA-Z_][a-zA-Z0-9_]*
hexdigit    (0[xX])?[a-fA-F0-9]*
decdigit    [0..9]*

%x NEW_COMMENT

%%

"clear"     { std::cout << "ccleaarrr" << std::endl; }

{decdigit}  {
    DBASElval.db_token_struct.string_val = strdup(yytext);
    return DB_TOK_DEC;
}
{hexdigit}  {
    DBASElval.db_token_struct.string_val = strdup(yytext);
    return DB_TOK_HEX;
}

["'][^"']*["']|[''][^']*['']* {
    DBASElval.db_token_struct.string_val = strdup(yytext);
    return DB_TOK_STRING;
}

\{                      { DBASE_column += strlen(yytext); BEGIN(NEW_COMMENT);       }
<NEW_COMMENT>\}         { DBASE_column += strlen(yytext); BEGIN(INITIAL);           }
<NEW_COMMENT>\n         { DBASE_column += strlen(yytext); DBASE_line++; }
<NEW_COMMENT>.          { DBASE_column += strlen(yytext); }

"**"                   { }
"&&"

\[          { return '['; }
\]          { return ']'; }
\+          { return '+'; }
\-          { return '-'; }
\*          { return '*'; }
\,          { return ','; }

[ \t]                   { DBASE_column += 1; }
(\n|\r\n)               { DBASE_column  = 1; DBASE_line++; }

.   {
    DBASE_column += 1;
    std::stringstream ss;
    ss << _("Invalide character: ") << yytext[0];
    DBASEerror(ss.str().c_str());
}

<<EOF>>      {
    //std::cout << "lines: " << DBASE_line << std::endl;
    yyterminate();
}
%%

void dbase_parser_main(void)
{
    fclose(yyin);
}
