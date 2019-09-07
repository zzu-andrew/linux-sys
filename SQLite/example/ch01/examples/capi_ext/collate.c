#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../common/util.h"

#include "oracle_date.h"

void setup(sqlite3* db);

/* Oracle data collation sequence.
**
** Breaks up Oracle date fields (e.g. 01-APR-04) and sorts them chronologically
** rather than lexographically.
*/
int oracle_date_collation( void* data, 
                           int len1, const void* arg1, 
                           int len2, const void* arg2 );

/* Return ISO date format from Oracel date format */
static void iso_from_oradate(sqlite3_context* ctx, int nargs, sqlite3_value** values);

/* Validate an Oracle date format. Raises error if not valid. */
static void validate_oradate(sqlite3_context* ctx, int nargs, sqlite3_value** values);

/* Installs the above two Oracle date functions. */
void install_date_functions(sqlite3* db);

/* Installs date validate triggers (INSERT and UPDATE) */
void install_date_triggers(sqlite3* db);

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

    /* Install oracle related date functions. */
    install_date_functions(db);

    /* Register collating sequence. */
    fprintf(stdout, "Registering collation sequence oracle_date\n");
    sqlite3_create_collation( db, "oracle_date", 
                              SQLITE_UTF8, db,
                              oracle_date_collation );

    /* Create dates table, add records. */
    setup(db);

    /* Install date */
    install_date_triggers(db);

    /* Turn SQL logging on. */
    log_sql(db, 1);

    /* Test default collation. */
    fprintf(stdout, "Select records. Use default collation.\n");
    sql = "select * from dates order by date";
    print_sql_result(db, sql);

    /* Test Oracle collation. */
    fprintf(stdout, "\nSelect records. Use Oracle data collation. \n");
    sql = "select * from dates order by date collate oracle_date";
    print_sql_result(db, sql);

    /* Get ISO Date from Oracle date. */
    fprintf(stdout, "\nConvert Oracle date to ISO format.\n");
    sql = "select iso_from_oradate('01-APR-05') as 'ISO Date'";
    print_sql_result(db, sql);

    /* Validate Oracle date. */
    fprintf(stdout, "\nValidate Oracle format. Should fail.\n");
    sql = "select validate_oradate('01-NOT-2005')";
    execute(db, sql);

    /* Test Oracle date triggers. */

    fprintf(stdout, "\nTest Oracle insert trigger -- should fail.\n");
    sql = "insert into dates (date) values ('01-NOT-2005')";
    execute(db, sql);

    fprintf(stdout, "\nTest Oracle update trigger -- should succeed.\n");
    sql = "update dates set date='01-JAN-2005'";
    execute(db, sql);
    print_sql_result(db, "select * from dates");

    /* Done. */
    sqlite3_close(db);

    return 0;    
}

void install_date_functions(sqlite3* db)
{
    sqlite3_create_function( db, "validate_oradate", 1, 
                             SQLITE_UTF8, NULL,
                             validate_oradate, NULL, NULL);

    sqlite3_create_function( db, "iso_from_oradate", 1, 
                             SQLITE_UTF8, NULL,
                             iso_from_oradate, NULL, NULL);
}

void install_date_triggers(sqlite3* db)
{
    const char *sql;

    sql = "CREATE TRIGGER date_insert_typecheck_tr \n"
          "BEFORE INSERT ON dates \n"
          "BEGIN \n"
          "    SELECT validate_oradate(new.date) \n"
          "    END; \n"
          "END;"
          "    "
          "CREATE TRIGGER date_update_typecheck_tr \n"
          "BEFORE UPDATE OF date ON dates \n"
          "FOR EACH ROW BEGIN\n"
          "    SELECT validate_oradate(new.date) \n"
          "    END; \n"
          "END;";

    execute(db, sql);
}

void setup(sqlite3* db)
{
    const char* sql;

    /* Turn SQL logging on. */
    log_sql(db, 1);

    /* Drop table if exists. */
    fprintf(stdout, "Dropping table dates, if exists.\n");
    drop_table(db, "dates");

    /* Create table. */
    fprintf(stdout, "Creating table dates.\n");
    sql = "create table dates( \n"
          "    id integer primary key, \n"
          "    date ora_date )";

    execute(db, sql);

    /* Add records. */
    fprintf(stdout, "Populating table dates.\n");

    sql = "insert into dates values (NULL, '%s')";
    execute(db, sql, "1-JAN-2005");
    execute(db, sql, "1-FEB-2005");
    execute(db, sql, "1-MAR-2005");
    execute(db, sql, "1-APR-2005");
    execute(db, sql, "1-MAY-2005");
    execute(db, sql, "1-JUN-2005");
    execute(db, sql, "1-JUL-2005");
    execute(db, sql, "1-AUG-2005");
    execute(db, sql, "1-SEP-2005");
    execute(db, sql, "1-OCT-2005");
    execute(db, sql, "1-NOV-2005");
    execute(db, sql, "1-DEC-2005");

    /* Turn SQL logging off. */
    log_sql(db, 0);

    fprintf(stdout, "\n");
}

int oracle_date_collation( void* data, 
                           int len1, const void* arg1, 
                           int len2, const void* arg2 )
{
    int len;
    date d1;
    date d2;
    char zDate1[25];
    char zDate2[25];

    /* Copy date 1 */

    if(len1 > 24) {
        len = 24;
    } else {
        len = len1;
    }

    strncpy(&zDate1[0], arg1, len);
    zDate1[len] = '\0';

    /* Copy date 2 */

    if(len2 > 24) {
        len = 24;
    } else {
        len = len2;
    }

    strncpy(&zDate2[0], arg2, len);
    zDate2[len] = '\0';

    /* Convert dates to date struct */
    oracle_date_str_to_struct(zDate1, &d1);
    oracle_date_str_to_struct(zDate2, &d2);

    fprintf(stdout, "collate_fn() : date1=%s, date2=%s\n", zDate1, zDate2);

    /* Compare structs */

    if(d1.year < d2.year)
    {
        return -1;
    }
    else if(d1.year > d2.year)
    {
        return 1;
    }

    /* If this far, years are equal. */

    if(d1.month < d2.month)
    {
        return -1;
    }
    else if(d1.month > d2.month)
    {
        return 1;
    }

    /* If this far, months are equal. */

    if(d1.day < d2.day)
    {
        return -1;
    }
    else if(d1.day > d2.day)
    {
        return 1;
    }

    /* If this far, dates are equal. */

    return 0;
}

void iso_from_oradate(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    const char *msg, *date, *iso_date;

    if(nargs != 1) {
        msg = "iso_from_oradate -- ERROR : Called with wrong number of functions.";
        sqlite3_result_error(ctx, msg, strlen(msg));
        return;
    }

    date = sqlite3_value_text(values[0]); 

    if(is_valid_oracle_date(date) != 1) {
        msg = "Invalid Oracle date format.";
        sqlite3_result_error(ctx, msg, strlen(msg));
        return;
    }
    
    iso_date = iso_from_oracle_date(date);
    sqlite3_result_text(ctx, iso_date, strlen(iso_date), free);
}

void validate_oradate(sqlite3_context* ctx, int nargs, sqlite3_value** values)
{
    const char *msg, *date;

    if(nargs != 1) {
        msg = "validate_oradate() -- ERROR : Called with wrong number of functions.";
        sqlite3_result_error(ctx, msg, strlen(msg));
        return;
    }

    date = sqlite3_value_text(values[0]); 

    if(is_valid_oracle_date(date) != 1) {
        msg = "Invalid Oracle date format.";
        sqlite3_result_error(ctx, msg, strlen(msg));
        return;
    }
    
    sqlite3_result_int(ctx, 0);
}
