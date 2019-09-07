#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main(int argc, char **argv)
{
    int rc, i, ncols;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *sql;
    const char *tail;
    const char *err;

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    
    sql = "select * from episodes;";

    rc = sqlite3_prepare(db, sql, strlen(sql), &stmt, &tail);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    
    rc = sqlite3_step(stmt);
    ncols = sqlite3_column_count(stmt); 

    while(rc == SQLITE_ROW) {
        
        for(i=0; i < ncols; i++) {
            fprintf(stderr, "'%s' ", sqlite3_column_text(stmt, i));
        }

        fprintf(stderr, "\n");

        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;    
}
