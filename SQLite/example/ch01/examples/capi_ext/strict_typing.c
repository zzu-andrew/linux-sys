#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../common/util.h"

/* Set up the types table for test. */
void setup(sqlite3* db);

/* Installs type validation triggers on column. It first looks the column's
** declared type in the schema and attempts find the matching validation
** function (validate_xxx()). If on exists, it creates INSERT/UPDATE triggers
** to call validation function.
*/
void add_strict_type_check_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values);

/* Helper function. Installs validation trigger on column */
int install_type_trigger( sqlite3* db, sqlite3_context* ctx, 
                          const char* table, const char* column );


/* Drops validation triggers on column */
void drop_strict_type_check_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values);

/* Helper function. Drops validation trigger on column */
int uninstall_type_trigger( sqlite3* db, sqlite3_context* ctx, 
                            const char* table, const char* column );


/* User-defined integer validation function. Use for integers, longs, etc. */
void validate_int_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values);

/* User-defined float validation function. Use for floats, doubles, reals, etc. */
void validate_double_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values);

/* User-defined column type function. Given a table name and column name,
** returns a column's declared type. 
*/
void column_type_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values);

/* C Function: Lookup column's declared type in sqlite_master. */
const char* column_type(sqlite3* db, const char* table, const char* column);

int main(int argc, char **argv)
{
    int rc;
    sqlite3 *db;
    char *sql;

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    setup(db);

    /* I. Register SQL functions ---------------------------------------------*/

    /* Generates and installs validation triggers. */
    rc = sqlite3_create_function( db, "add_strict_type_check", 2, SQLITE_UTF8, db,
                                  add_strict_type_check_udf, NULL, NULL);

    /* Removes validation triggers. */
    sqlite3_create_function( db, "drop_strict_type_check", 2, SQLITE_UTF8, db,
                             drop_strict_type_check_udf, NULL, NULL);

    /* Convenience function for pulling a column's type from sqlite_master. It
     * is a fine-grained 'PRAGMA table_info()'.*/
    sqlite3_create_function( db, "column_type", 2, SQLITE_UTF8, db,
                             column_type_udf, NULL, NULL);

    /* Type Validation: Called to validate integer. */
    sqlite3_create_function( db, "validate_int", 1, SQLITE_UTF8, db,
                             validate_int_udf, NULL, NULL);

    /* Type Validation: Called to validate long integer. Same UDF as above,
     * different SQL function name. */
    sqlite3_create_function( db, "validate_long", 1, SQLITE_UTF8, db,
                             validate_int_udf, NULL, NULL);

    /* Type Validation: Called to validate float. */
    sqlite3_create_function( db, "validate_double", 1, SQLITE_UTF8, db,
                             validate_double_udf, NULL, NULL);

    /* Type Validation: Called to validate long integer. Same UDF as above,
     * different SQL function name. */
    sqlite3_create_function( db, "validate_float", 1, SQLITE_UTF8, db,
                             validate_double_udf, NULL, NULL);

    /* II. Test ---------------------------------------------------------------*/

    log_sql(db,1);

    /* Add type check constraint trigger for types.id */
    printf("1. Add strict typing:\n");
    execute(db, "select add_strict_type_check('types', '*')");
    printf("\n");

    /* Insert a record with valid id */
    printf("2. Insert integer value -- should succeed:\n");
    execute(db, "insert into types (x) values (1)");
    printf("\n");

    /* Insert a record with invalid id type*/
    printf("3. Update with invalid values -- should fail:\n");
    execute(db, "update types set x = 'abc'");
    execute(db, "update types set y = 'abc'");
    printf("\n");

    /* Remove type check constraint trigger for types.id */
    printf("4. Remove strict typing\n");
    execute(db, "select drop_strict_type_check('types', '*')");
    printf("\n");

    /* Insert a record with invalid id type*/
    printf("5. Update with non-integer value -- should succeed:\n");
    execute(db, "update types set x = 'not an int'");
    printf("\n");

    printf("6. Select records:\n");
    print_sql_result(db, "select * from types");
    printf("\n");

    /* Test column_type() */
    printf("7. Test column_type() UDF\n");
    sql = "select column_type('types', 'id') as 'id',\n"
          "         column_type('types', 'x')  as 'x',\n"
          "         column_type('types', 'y')  as 'y'";
    print_sql_result(db, sql);
    printf("\n");

    sqlite3_close(db);

    return 0;    
}

void add_strict_type_check_udf( sqlite3_context* ctx, int nargs, 
                                sqlite3_value** values )
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *table, *column, *sql, *tmp, *tail, *err;

    db=(sqlite3*)sqlite3_user_data(ctx);

    table  = sqlite3_value_text(values[0]);
    column = sqlite3_value_text(values[1]);

    if(strncmp(column,"*",1) == 0) {

        /* Install on all columns */

        sql = "pragma table_info(%s)";
        tmp = sqlite3_mprintf(sql, table);
        
        rc = sqlite3_prepare(db, tmp, (int)strlen(tmp), &stmt, &tail);
        sqlite3_free((void*)tmp);

        if(rc != SQLITE_OK) {
            err = sqlite3_errmsg(db);
            sqlite3_result_error(ctx, err, (int)strlen(err));
        }
    
        rc = sqlite3_step(stmt);

        while(rc == SQLITE_ROW) {
            /* If not primary key */
            if(sqlite3_column_int(stmt, 5) != 1) {
                column = sqlite3_column_text(stmt, 1); 
                install_type_trigger(db, ctx, table, column);
            }

            rc = sqlite3_step(stmt);
        }
    
        sqlite3_finalize(stmt);
    }
    else {

        /* Just installing on a single column */
        if(install_type_trigger(db, ctx, table, column) != 0) {
            return;
        }
    }

    sqlite3_result_int(ctx, 0);
}

int install_type_trigger( sqlite3* db, sqlite3_context* ctx, 
                          const char* table, const char* column )
{
    int rc;
    char buf[256];
    char *tmp;
    const char *type, *sql, *emsg;
    char* err;

    type = column_type(db, table, column);

    if(type == NULL) {
        emsg = "column has no declared type";
        sqlite3_result_error(ctx, emsg, (int)strlen(emsg));
        sqlite3_free((void*)type);
        return 1;
    }

    /* Check to see if corresponding validation function exists */

    sql = "select validate_%s(null)";
    tmp = sqlite3_mprintf(sql, type);
    rc = sqlite3_exec(db, tmp, NULL, NULL, &err);
    sqlite3_free(tmp);

    if(rc != SQLITE_OK && err != NULL) {
        emsg = "No validator exists for column type";
        sqlite3_result_error(ctx, emsg, (int)strlen(emsg));
        sqlite3_free((void*)type);
        sqlite3_free(err);
        return 1;
    }

    /* Create INSERT trigger */
    sql = "CREATE TRIGGER %s_insert_%s_typecheck_tr \n"
          "BEFORE INSERT ON %s \n"
          "BEGIN \n"
          "   SELECT CASE \n"
          "     WHEN(SELECT validate_%s(new.%s) != 1) \n"
          "     THEN RAISE(ABORT, 'invalid %s value for %s.%s') \n"
          "   END; \n"
          "END;";

    tmp = sqlite3_mprintf(sql, table, column, table, type, 
                           column, type, table, column);    

    rc = sqlite3_exec(db, tmp, NULL, NULL, &err);
    sqlite3_free(tmp);

    if(rc != SQLITE_OK && err != NULL) {
        strncpy(&buf[0], err, 255);
        buf[256] = '\0';
        sqlite3_result_error(ctx, &buf[0], (int)strlen(&buf[0]));
        sqlite3_free((void*)type);

        return 1;
    }

    /* Create UPDATE trigger */

    sql = "CREATE TRIGGER %s_update_%s_typecheck_tr \n"
          "BEFORE UPDATE OF %s ON %s \n"
          "FOR EACH ROW BEGIN \n"
          "  SELECT CASE \n"
          "    WHEN(SELECT validate_%s(new.%s) != 1) \n"
          "    THEN RAISE(ABORT, 'invalid %s value for %s.%s') \n"
          "  END; \n"
          "END;";

    tmp = sqlite3_mprintf(sql, table, column, column, table, 
                           type, column, type, table, column);

    rc = sqlite3_exec(db, tmp, NULL, NULL, &err);
    sqlite3_free(tmp);
    sqlite3_free((void*)type);

    if(rc != SQLITE_OK && err != NULL) {
        strncpy(&buf[0], err, 255);
        buf[256] = '\0';
        sqlite3_result_error(ctx, &buf[0], (int)strlen(&buf[0]));
        sqlite3_free(err);

        return 1;
    }

    return 0;
}

void drop_strict_type_check_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *table, *column, *sql, *tmp, *tail, *err;

    db = (sqlite3*)sqlite3_user_data(ctx);
    table  = sqlite3_value_text(values[0]);
    column = sqlite3_value_text(values[1]);

    if(strncmp(column,"*",1) == 0) {

        /* Install on all columns */

        sql = "pragma table_info(%s)";
        tmp = sqlite3_mprintf(sql, table);
        
        rc = sqlite3_prepare(db, tmp, (int)strlen(tmp), &stmt, &tail);
        sqlite3_free((void*)tmp);

        if(rc != SQLITE_OK) {
            err = sqlite3_errmsg(db);
            sqlite3_result_error(ctx, err, (int)strlen(err));
        }
    
        rc = sqlite3_step(stmt);

        while(rc == SQLITE_ROW) {
            /* If not primary key */
            if(sqlite3_column_int(stmt, 5) != 1) {
                column = sqlite3_column_text(stmt, 1); 
                uninstall_type_trigger(db, ctx, table, column);
            }

            rc = sqlite3_step(stmt);
        }
    
        sqlite3_finalize(stmt);
    }
    else {

        /* Just installing on a single column */

        if(uninstall_type_trigger(db, ctx, table, column) != 0) {
            return;
        }
    }

    sqlite3_result_int(ctx, 0);
}

/* Helper function. Drops validation trigger on column */
int uninstall_type_trigger( sqlite3* db, sqlite3_context* ctx, 
                            const char* table, const char* column )
{
    int rc;
    char buf[256];
    char *tmp;
    const char *sql;
    char* err;

    /* Drop INSERT trigger */
    sql = "DROP TRIGGER %s_insert_%s_typecheck_tr";
    tmp = sqlite3_mprintf(sql, table, column);    
    rc = sqlite3_exec(db, tmp, NULL, NULL, &err);
    sqlite3_free(tmp);

    if(rc != SQLITE_OK && err != NULL) {
        strncpy(&buf[0], err, 255);
        buf[256] = '\0';
        sqlite3_result_error(ctx, &buf[0], (int)strlen(&buf[0]));
        return 1;
    }

    /* Drop UPDATE trigger */
    sql = "DROP TRIGGER %s_update_%s_typecheck_tr";
    tmp = sqlite3_mprintf(sql, table, column);    
    rc = sqlite3_exec(db, tmp, NULL, NULL, &err);
    sqlite3_free(tmp);

    if(rc != SQLITE_OK && err != NULL) {
        strncpy(&buf[0], err, 255);
        buf[256] = '\0';
        sqlite3_result_error(ctx, &buf[0], (int)strlen(&buf[0]));
        return 1;
    }

    return 0;
}


void validate_int_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    sqlite3 *db;
    const char *value;
    char *tmp;

    db    = (sqlite3*)sqlite3_user_data(ctx);
    value = sqlite3_value_text(values[0]);

    /* Assuming NULL values for type checked columns not allowed */
    if(value == NULL) {
        sqlite3_result_int(ctx, 0);
        return;
    }

    // Validate type:
    tmp = NULL;
    strtol(value, &tmp, 0);
    
    if(*tmp != '\0') {
        // Value does not conform to type
        sqlite3_result_int(ctx, 0);
        return;
    }

    // If we got this far value is valid.
    sqlite3_result_int(ctx, 1);
}

void validate_double_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    sqlite3 *db;
    const char *value;
    char *tmp;

    db    = (sqlite3*)sqlite3_user_data(ctx);
    value = sqlite3_value_text(values[0]);

    /* Assuming NULL values for type checked columns not allowed */
    if(value == NULL) {
        sqlite3_result_int(ctx, 0);
        return;
    }

    // Validate type:
    tmp = NULL;
    strtod(value, &tmp);
    
    if(*tmp != '\0') {
        // Value does not conform to type
        sqlite3_result_int(ctx, 0);
        return;
    }

    // If we got this far value is valid.
    sqlite3_result_int(ctx, 1);
}

void column_type_udf(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    sqlite3 *db;
    const char *table, *column, *type;

    db=(sqlite3*)sqlite3_user_data(ctx);

    table  = sqlite3_value_text(values[0]);
    column = sqlite3_value_text(values[1]);

    /* Get declared type from schema */
    type = column_type(db, table, column);

    /* Return type */
    sqlite3_result_text(ctx, type, (int)strlen(type), free);
}

const char* column_type(sqlite3* db, const char* table, const char* column)
{
    sqlite3_stmt *stmt;
    int i, len, rc;
    char *sql, *tmp, *type;
    const char *p, *tail, *sql_type;

    sql = "select %s from %s;";
    tmp = sqlite3_mprintf(sql, column, table);
    rc = sqlite3_prepare(db, tmp, (int)strlen(tmp), &stmt, &tail);
    
    if(rc != SQLITE_OK) {
        return NULL;
    }

    sql_type = sqlite3_column_decltype(stmt, 0);

    // Convert type to lower case
    i = 0;
    p = &sql_type[0];
    len = (int)strlen(sql_type);
    type = malloc(strlen(sql_type)+1);
    while(i < len) {
        type[i] = tolower(*p);
        p++;i++;
    }

    type[len] = '\0';

    /* Free statement handle and tmp sql string */
    sqlite3_finalize(stmt);
    sqlite3_free(tmp);

    return type;
}

void setup(sqlite3* db)
{
    const char* sql;
    log_sql(db, 1);

    printf("Dropping table types, if exists.\n");
    drop_table(db, "types");

    printf("Creating table types.\n");
    sql = "create table types(\n"
          "id integer primary key, "
          "x int not null default 0,"
          "y float not null default 0.0);";
    execute(db, sql);

    printf("Populating table types.\n");

    execute(db, "insert into types(x,y) values (1, 1.1)");
    execute(db, "insert into types(x,y) values (2, 2.1)");
    execute(db, "insert into types(x,y) values (3, 3.1)");

    log_sql(db, 0);

    printf("\n");
}
