#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
//#include "util.h"


static int print_sql_result(sqlite3 *db, const char *sql)
{
    char **result, *err;
    int  i, j, k, l, nrows, ncols, width, *widths; 



    sqlite3_get_table(db,sql,&result,&nrows,&ncols,&err);

    /* Determine column widths*/
    widths = malloc(ncols*sizeof(int));
    memset(widths,0,ncols*sizeof(int));
    for(i=0; i <= nrows; i++) {
        for(j=0; j < ncols; j++) {
            if(result[i*ncols+j] == NULL)
                continue;
            width = strlen(result[i*ncols+j]);
            if(width > widths[j]) {
                widths[j] = width;
            }
        }
    }

    for(i=0; i <= nrows; i++) {
        if(i==1) {
            for(k=0; k < ncols; k++) {
                for(l=0; l < widths[k]; l++) {
                    fprintf(stdout, "-");
                }
                fprintf(stdout, " ");
            }
            fprintf(stdout, "\n");
        }

        for(j=0; j < ncols; j++) {
            fprintf(stdout, "%-*s", widths[j]+1, result[i*ncols+j]);
        }
        fprintf(stdout, "\n");
    }

    free(widths);
    sqlite3_free_table(result);
    return 0;
}


static int execute(sqlite3 *db, const char* sql)
{
    char* err = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err);

    if(rc != SQLITE_OK) {
        if (err != NULL) {
            fprintf(stderr, "execute() Error: %s\n", err);
            sqlite3_free(err);
        }
    }

    return rc;
}

int test_positional_params(sqlite3 *db);
int test_numbered_params(sqlite3 *db);
int test_named_params(sqlite3 *db);

void cleanup_fn(void*);

int main(int argc, char **argv)
{
    int rc;
    sqlite3 *db;

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    execute(db, "drop table episodes");
    execute(db, "create table episodes(id int, cid int, name text)");

    /* Positional Parameters */
    fprintf(stdout, "Test Positional Parameters\n");
    execute(db, "delete from episodes");
    if(test_positional_params(db) != SQLITE_OK) {
        goto end;
    }
    print_sql_result(db, "select * from episodes");
    fprintf(stdout, "\n");

    /* Numbered Parameters */
    fprintf(stdout, "Test Numbered Parameters\n");
    execute(db, "delete from episodes");
    if(test_numbered_params(db) != SQLITE_OK) {
        goto end;
    }
    print_sql_result(db, "select * from episodes");
    fprintf(stdout, "\n");

    /* Named Parameters */
    fprintf(stdout, "Test Named Parameters\n");
    execute(db, "delete from episodes");
    if(test_named_params(db) != SQLITE_OK) {
        goto end;
    }
    print_sql_result(db, "select * from episodes");

end:
    sqlite3_close(db);

    return 0;    
}

int test_positional_params(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    const char* tail;

    const char* sql = "insert into episodes (id, cid, name) "
                      " values (?,?,'Mackinaw Peaches')";
    int rc = sqlite3_prepare(db, sql, (int)strlen(sql), &stmt, &tail);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "Error: %s\n", tail);
    }

    sqlite3_bind_int(stmt, 1, 10);
    sqlite3_bind_int(stmt, 2, 10);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return SQLITE_OK;
}

int test_numbered_params(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    const char* tail;
    char *name, *sql;
    int rc;

    name = "Mackinaw Peaches";
    sql = "insert into episodes (id, cid, name) "
          "values (?100,?100,?101)";

    rc = sqlite3_prepare(db, sql, (int)strlen(sql), &stmt, &tail);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_prepare() : Error: %s\n", tail);
        return rc;
    }

    sqlite3_bind_int(stmt, 100, 10);
    sqlite3_bind_text(stmt, 101, name, (int)strlen(name), SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return SQLITE_OK;
}

int test_named_params(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    char *name, *sql;
    int rc;
    const char* tail;

    name = "Mackinaw Peaches";
    sql = "insert into episodes (id, cid, name) values (:cosmo,:cosmo,:newman)";

    rc = sqlite3_prepare(db, sql, (int)strlen(sql), &stmt, &tail);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "Error: %s\n", tail);
        return rc;
    }

    sqlite3_bind_int( stmt, 
                      sqlite3_bind_parameter_index(stmt, ":cosmo"), 10);
    
    sqlite3_bind_text( stmt, 
                       sqlite3_bind_parameter_index(stmt, ":newman"), 
                       name, 
                       (int)strlen(name), cleanup_fn );

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return SQLITE_OK;
}

void cleanup_fn(void* data)
{
    fprintf(stderr, "Cleanup function called for: %p\n", data);
}
