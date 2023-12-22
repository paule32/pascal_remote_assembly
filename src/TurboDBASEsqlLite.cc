// -----------------------------------------------------------------
// File:   TurboDBASEsqlLite.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------

# include <iostream>

# include <sqlite3.h>

namespace dBaseRelease {
sqlite3 *directoryDB;

int open_sqlite(std::string& filename) {
    int rc = sqlite3_open("folder.db", &directoryDB);
    if (rc != SQLITE_OK) {
        return EXIT_FAILURE;
    }
    const std::string sql = R"(
    CREATE TABLE IF NOT EXISTS folder (
        id   INT,
        name TEXT
    );";
    char* errorMessage = 0;
    rc = sqlite3_exec(directoryDB, sql, 0,0, &errorMessage);
    if (rc != SQLITE_OK) {
        
    }
    close_sqlite(directoryDB);
    return EXIT_SUCCESS;
}
}   // dBaseRelease
