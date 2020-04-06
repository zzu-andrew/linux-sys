#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/util.h"

void function(sqlite3_context* ctx, int nargs, sqlite3_value** values);

int main(int argc, char **argv)
{
    int rc;
    sqlite3 *db;
    const char* sql;

    sqlite3_open("test.db", &db);
    sqlite3_create_function( db, "function", -1, SQLITE_UTF8, NULL,
                             function, NULL, NULL);

    /* Turn on SQL logging */
    log_sql(db, 1);

    /* Call function with one text argument. */
    execute(db, "select function(1)");

    /* Call function with several arguments of various types. */
    execute(db, "select function(1, 2.71828)");

    /* Call function with variable arguments, the first argument’s value
    ** being 'fail'. This will trigger the function to call 
    ** sqlite3_result_error(). */
    execute(db, "select function('fail', 1, 2.71828, 'three', X'0004', NULL)");

    /* Done */
    sqlite3_close(db);

    return 0;    
}

void function(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    int i; const char *msg;

    fprintf(stdout, "function() : Called with %i arguments\n", nargs);

    for(i=0; i < nargs; i++) {
        fprintf( stdout, "    arg %i: value=%-7s type=%i\n", i, 
                 sqlite3_value_text(values[i]), 
                 sqlite3_value_type(values[i]));
    }

    if(strcmp(sqlite3_value_text(values[0]), "fail") == 0) {
        msg = "function() : Failing because you told me to.";
        sqlite3_result_error(ctx, msg, strlen(msg));
        fprintf(stdout, "\n");
        return;
    }

    fprintf(stdout, "\n");
    sqlite3_result_int(ctx, 0);
}
