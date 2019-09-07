#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char **argv)
{
    sqlite3 *db;
    char *zErr;
    int rc;
    char *sql;

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    sql = "create table episodes(name text, cid int)";

    rc = sqlite3_exec(db, sql, NULL, NULL, &zErr);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErr);
    }
    
    sqlite3_close(db);

    return 0;    
}
