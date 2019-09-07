#include <stdio.h>
#include <stdlib.h>
#include "../common/util.h"

int main(int argc, char **argv)
{
    int rc, i, ncols, id, cid; char *name, *sql;
    sqlite3 *db; sqlite3_stmt *stmt;

	sql = "select id,cid,name from episodes";
    sqlite3_open("test.db", &db);

    sqlite3_prepare(db, sql, strlen(sql), &stmt, NULL);

    ncols = sqlite3_column_count(stmt); 
    rc = sqlite3_step(stmt);

    /* Print column information */
    for(i=0; i < ncols; i++) {
        fprintf(stdout, "Column: name=%s, storage class=%i, declared=%s\n", 
                         sqlite3_column_name(stmt, i),
                         sqlite3_column_type(stmt, i),
                         sqlite3_column_decltype(stmt, i));
    }

    fprintf(stdout, "\n");

    while(rc == SQLITE_ROW) {
        id = sqlite3_column_int(stmt, 0);
        cid = sqlite3_column_int(stmt, 1);
        name = sqlite3_column_text(stmt, 2);
        if(name != NULL){
            fprintf(stderr, "Row:  id=%i, cid=%i, name='%s'\n", id,cid,name);
        } else {
            /* Field is NULL */
            fprintf(stderr, "Row:  id=%i, cid=%i, name=NULL\n", id,cid);
        } 
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
