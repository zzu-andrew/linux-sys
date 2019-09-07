#include <stdio.h>
#include <stdlib.h>
#include "../common/util.h"

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *zErr;
    int rc;
    char *sql;

    rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    sql = "create table episodes( id integer primary key,"
          "                       name text, cid int)";

    rc = sqlite3_exec(db, sql, NULL, NULL, &zErr);

    if (rc != SQLITE_OK) {
        if (zErr != NULL) {
            fprintf(stderr, "SQL error: %s\n", zErr);
            sqlite3_free(zErr);
        }
    }

    sql = "insert into episodes (name,id) values ('Cinnamon Babka2',1)";
    rc = sqlite3_exec(db, sql, NULL, NULL, &zErr);

    if (rc != SQLITE_OK) {
        if (zErr != NULL) {
            fprintf(stderr, "SQL error: %s\n", zErr);
            sqlite3_free(zErr);
        }
    }

    sqlite3_close(db);

    return 0;    
}
