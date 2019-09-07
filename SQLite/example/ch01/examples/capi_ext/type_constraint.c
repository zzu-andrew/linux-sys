#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void is_type(sqlite3_context* ctx, int nargs, sqlite3_value** values);

int main(int argc, char **argv)
{
    int rc, i, ncols;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *sql, *tmp;
    const char *tail, *err;

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_create_function( db, "is_int", -1, SQLITE_UTF8, db,
                             test_fn, NULL, NULL);

    sql = "CREATE TEMPORARY TRIGGER %s_insert_%s_%s_constraint \n"
          "BEFORE INSERT ON %s \n"
          "BEGIN \n"
          "    SELECT CASE \n"
          "        WHEN (%s(new.%s) != 0) \n"
          "            THEN RAISE(ABORT, '%s') \n"
          "    END; \n"
          "END;";
    
    const char* table    = "episodes";
    const char* column   = "cid";
    const char* fn       = "test_fn";
    const char* emsg     = "test_fn FAILED";

    tmp = sqlite3_mprintf( sql, table, column, fn,
                           table, fn, column, emsg);

    printf("%s\n", tmp);
    
    rc = sqlite3_prepare(db, tmp, strlen(tmp), &stmt, &tail);

    if(rc != SQLITE_OK) {
        err = sqlite3_errmsg(db);
        if(err) {
            fprintf(stderr, "sqlite_prepare() ERROR: %s\n", err);
            sqlite3_free(err);
        }
        
        return 1;
    }
    
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) {
        err = sqlite3_errmsg(db);
        if(err) {
            fprintf(stderr, "%i %s\n", rc, err);
            sqlite3_free(err);
        }

        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_free(tmp);

    sql = "insert into episodes (cid,name) values (1,'1')";

    rc = sqlite3_exec(db, sql, NULL, NULL, &err);

    if(rc != SQLITE_OK) {
        if (err != NULL) {
            fprintf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);
        }
    }

    sqlite3_close(db);

    return 0;    
}

void test_fn(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    printf("test_fn nargs=%i\n", nargs);

    int i;
    for(i=0; i < nargs; i++)
    {
        printf("%s(%i) ", sqlite3_value_text(values[i]), sqlite3_value_type(values[i]));
    }

    printf("\n");

    //sqlite3_result_error(ctx, 1, "Not an integer value");
    sqlite3_result_int(ctx, 0);
}
