#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "util.h"

int main(int argc, char **argv)
{
    sqlite3 *db;
    int rc;
    char *sql;
    char *zErr;

    rc = sqlite3_open("db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    dump(db, "select firstname, lastname, license, box_num, home_phone from agent");

    sqlite3_close(db);

    return 0;    
}
