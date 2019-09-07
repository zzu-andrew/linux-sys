#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sqlite3.h"


int execute(sqlite3 *db, const char* sql, ...)
{
	int rc;
	char *err, *tmp;

	va_list ap;
    va_start(ap, sql);
    tmp = sqlite3_vmprintf(sql, ap);
    va_end(ap);

    rc = sqlite3_exec(db, tmp, NULL, NULL, &err);

    if(rc != SQLITE_OK) {
        if (err != NULL) {
            fprintf(stderr, "execute() Error: %s\n", err);
            sqlite3_free(err);
        }
    }

    sqlite3_free(tmp);

    return rc;
}


int drop_table(sqlite3* db, const char* name)
{
    sqlite3_stmt *stmt;
    const char *sql, *tmp, *tail;
    int exists;

    tmp = "select count(*) from sqlite_master where name='%s'";
    sql = sqlite3_mprintf(tmp, name);
    sqlite3_prepare(db, sql, (int)strlen(sql), &stmt, &tail);
    sqlite3_step(stmt);
    exists = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_free((void*)sql);

    if(exists) {
        execute(db, "drop table %s", name);
        return 1;
    }

    return 0;
}

void print_error(sqlite3 *db, const char* msg, ...)
{
    char* txt;

    if(msg) {
        va_list ap;
        va_start(ap, msg);
        txt = sqlite3_vmprintf(msg, ap);
        va_end(ap);

        fprintf(stderr, txt);
        sqlite3_free(txt);
    }
    
    fprintf(stderr, "%s\n", sqlite3_errmsg(db));
}

int print_sql_result(sqlite3 *db, const char *sql)
{
    char **result, *err;
    int i, j, k, l, nrows, ncols, width, *widths; 

    sqlite3_get_table(db,sql,&result,&nrows,&ncols,&err);

    /* Determine column widths*/
    widths = malloc(ncols*sizeof(int));
    memset(widths,0,ncols*sizeof(int));
    for(i=0; i <= nrows; i++) {
        for(j=0; j < ncols; j++) {
            if(result[i*ncols+j] == NULL)
                continue;
            width = (int)strlen(result[i*ncols+j]);
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
    fprintf(stderr, "  TRACE: %s\n", sql);
}

void log_sql(sqlite3* db, int flag)
{
    if(flag != 0) {
        sqlite3_trace(db, trace_sql, db);
    }
    else {
        sqlite3_trace(db, NULL, db);
    }
}

const char* convert_string(const char* value, int(*fn)(int))
{
    int i, len;
    const char *p;
    char *result;

    if(value == NULL) {
        return NULL;
    }

    // Convert type to lower case
    i = 0;
    p = &value[0];
    len = (int)strlen(value);
    result = malloc(strlen(value)+1);
    while(i < len) {
        result[i] = toupper(*p);
        p++;i++;
    }

    result[len] = '\0';

    return result;
}

const char* lowercase(const char* value)
{
    return convert_string(value, tolower);
}

const char* uppercase(const char* value)
{
    return convert_string(value, toupper);
}
