#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/util.h"

/* SQLite Aggregate Example
** 
** Creates a simple sum() aggregate function and tests it on a simple table.
*/

/* For setting up table for example. */
void setup();

/* Aggregate running total */
typedef struct {
    int x;
} sum;

/* Aggregate step function */
void step(sqlite3_context* ctx, int ncols, sqlite3_value** values);

/* Aggregate final function */
void finalize(sqlite3_context* ctx);

int main(int argc, char **argv)
{
    int rc;
    sqlite3 *db;
    char *sql;

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        print_error(db, "Can't open database");
        exit(1);
    }

    /* Create aggregate table, add records. */
    setup(db);

    /* Register aggregate. */
    fprintf(stdout, "Registering aggregate sum_int()\n");

    log_sql(db, 1);

    sqlite3_create_function( db, "sum_int", 1, SQLITE_UTF8, db,
                             NULL, step, finalize);

    /* Test it. */
    fprintf(stdout, "\nRunning query: \n");
    sql = "select sum_int(id) from aggregate";
    print_sql_result(db, sql);

    /* Done. */
    sqlite3_close(db);

    return 0;    
}

void step(sqlite3_context* ctx, int ncols, sqlite3_value** values)
{
    sum* s;
    int x;

    s = (sum*)sqlite3_aggregate_context(ctx, sizeof(sum));

    if(sqlite3_aggregate_count(ctx) == 1) {
        s->x = 0;
    }

    x = sqlite3_value_int(values[0]);;
    s->x += x;

    fprintf(stdout, "step()     : value=%i, total=%i\n", x, s->x);
}

void finalize(sqlite3_context* ctx)
{
    sum* s;
    s = (sum*)sqlite3_aggregate_context(ctx, sizeof(sum));
    sqlite3_result_int(ctx, s->x);

    fprintf(stdout, "finalize() : total=%i\n\n", s->x);
}

void setup(sqlite3* db)
{
    log_sql(db, 1);

    fprintf(stdout, "Dropping table aggregate, if exists.\n");
    drop_table(db, "aggregate");

    fprintf(stdout, "Creating table aggregate.\n");
    execute(db, "create table aggregate(id integer)");

    fprintf(stdout, "Populating table aggregate.\n");

    execute(db, "insert into aggregate values (1)");
    execute(db, "insert into aggregate values (2)");
    execute(db, "insert into aggregate values (3)");

    log_sql(db, 0);

    fprintf(stdout, "\n");
}
