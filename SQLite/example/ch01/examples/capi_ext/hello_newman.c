#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/util.h"

void hello_newman(sqlite3_context* ctx, int nargs, sqlite3_value** values);

int main(int argc, char **argv)
{
    sqlite3 *db;

    sqlite3_open("test.db", &db);
    sqlite3_create_function( db, "hello_newman", 1, SQLITE_UTF8, NULL,
                             hello_newman, NULL, NULL);

    /* Log SQL as it is executed. */
    log_sql(db,1);

    /* Call function with one text argument. */
    fprintf(stdout, "Calling with one argument.\n");
    print_sql_result(db, "select hello_newman('Jerry')");

    /* Call function with two arguments. This will fail as we registered the     
    ** function as taking only one argument. */
    fprintf(stdout, "\nCalling with two arguments.\n");
    print_sql_result(db, "select hello_newman ('Jerry', 'Elaine')");

    /* Call function with no arguments. This will fail too */
    fprintf(stdout, "\nCalling with no arguments.\n");
    print_sql_result(db, "select hello_newman()");

    /* Done */
    sqlite3_close(db);

    return 0;    
}

void hello_newman(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    const char *msg;

	/* Generate Newman’s reply */
	msg = sqlite3_mprintf("Hello %s", sqlite3_value_text(values[0]));

	/* Set the return value. Have sqlite clean up msg w/ sqlite_free(). */        
    sqlite3_result_text(ctx, msg, (int)strlen(msg), sqlite3_free);
}

