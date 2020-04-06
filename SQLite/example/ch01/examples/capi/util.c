#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int execute(sqlite3 *db, const char* sql)
{
    const char* err;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err);

    if(rc != SQLITE_OK) {
        if (err != NULL) {
            fprintf(stderr, "execute() Error: %s\n", err);
            sqlite3_free(err);
        }
    }

    return rc;
}

void print_error(sqlite3 *db, const char* msg, ...)
{
    const char* txt;

    if(msg) {
        va_list ap;
        va_start(ap, s);
        txt = sqlite3_vmprintf(s, ap);
        va_end(ap);

        fprintf(stderr, txt);
        sqlite3_free(txt);
    }
    
    fprintf(stderr, "%s\n", sqlite3_errmsg(db));
}

int print_sql_result(sqlite3 *db, const char *sql)
{
    char **result, *err;
    int rc, i, j, k, l, nrows, ncols, width, *widths; 
    const char *tail;
    sqlite3_stmt *stmt;

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
}

int print_stmt_result(sqlite3_stmt *stmt)
{    
    int i, rc, ncols;

    /* Execute, get first row */
    rc = sqlite3_step(stmt);
    ncols = sqlite3_column_count(stmt); 

    /* Print column information */
    for(i=0; i < ncols; i++) {
        fprintf( stdout, "  Column: %s (%i/%s)\n", 
                 sqlite3_column_name(stmt, i),
                 sqlite3_column_type(stmt, i),
                 sqlite3_column_decltype(stmt, i));
    }

    /* Print rows */                
    while(rc == SQLITE_ROW) {        
        fprintf(stdout, "  Record: ");
        for(i=0; i < ncols; i++) {
            fprintf(stdout, "'%s' ", sqlite3_column_text(stmt, i));
        }
        fprintf(stdout, "\n");

        rc = sqlite3_step(stmt);
    }

    return 0;    
}

const char* event_description(int type)
{
    switch(type)
    {
        case SQLITE_CREATE_INDEX:
            return "SQLITE_CREATE_INDEX";

        case SQLITE_CREATE_TABLE:
            return "SQLITE_CREATE_TABLE";

        case SQLITE_CREATE_TEMP_INDEX:
            return "SQLITE_CREATE_TEMP_INDEX";

        case SQLITE_CREATE_TEMP_TABLE:
            return "SQLITE_CREATE_TEMP_TABLE";

        case SQLITE_CREATE_TEMP_TRIGGER:
            return "SQLITE_CREATE_TEMP_TRIGGER";

        case SQLITE_CREATE_TEMP_VIEW:
            return "SQLITE_CREATE_TEMP_VIEW";

        case SQLITE_CREATE_TRIGGER:
            return "SQLITE_CREATE_TRIGGER";

        case SQLITE_CREATE_VIEW:
            return "SQLITE_CREATE_VIEW";

        case SQLITE_DELETE:
            return "SQLITE_DELETE";

        case SQLITE_DROP_INDEX:
            return "SQLITE_DROP_INDEX";

        case SQLITE_DROP_TABLE:
            return "SQLITE_DROP_TABLE";

        case SQLITE_DROP_TEMP_INDEX:
            return "SQLITE_DROP_TEMP_INDEX";

        case SQLITE_DROP_TEMP_TABLE:
            return "SQLITE_DROP_TEMP_TABLE";

        case SQLITE_DROP_TEMP_TRIGGER:
            return "SQLITE_DROP_TEMP_TRIGGER";

        case SQLITE_DROP_TEMP_VIEW:
            return "SQLITE_DROP_TEMP_VIEW";

        case SQLITE_DROP_TRIGGER:
            return "SQLITE_DROP_TRIGGER";

        case SQLITE_DROP_VIEW:
            return "SQLITE_DROP_VIEW";

        case SQLITE_INSERT:
            return "SQLITE_INSERT";

        case SQLITE_PRAGMA:
            return "SQLITE_PRAGMA";

        case SQLITE_READ:
            return "SQLITE_READ";

        case SQLITE_SELECT:
            return "SQLITE_SELECT";

        case SQLITE_TRANSACTION:
            return "SQLITE_TRANSACTION";

        case SQLITE_UPDATE:
            return "SQLITE_UPDATE";

        case SQLITE_ATTACH:
            return "SQLITE_ATTACH";

        case SQLITE_DETACH:
            return "SQLITE_DETACH";
    }

    return "UNKNOWN EVENT";
}

void trace_sql(void* data, const char* sql)
{
    fprintf(stderr, "TRACE: %s\n", sql);
}
