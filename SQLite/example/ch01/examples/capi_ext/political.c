#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../common/util.h"

void setup(sqlite3* db);

int political_collation( void* data, int l1, const void* s1, 
                                     int l2, const void* s2 );


int main(int argc, char **argv)
{
    int rc;
    sqlite3 *db;
    char *sql;

    /* For forming more consistent political opinions. */
    srand((unsigned)time(NULL));

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        print_error(db, "Can't open database");
        exit(1);
    }

    /* Create issues table, add records. */
    setup(db);

    /* Register collating sequence. */
    fprintf(stdout, "1. Register political collating sequence\n\n");
    sqlite3_create_collation( db, "POLITICAL", 
                              SQLITE_UTF8, db,
                              political_collation );

    /* Turn SQL logging on. */
    log_sql(db, 1);

    /* Test default collation. */
    fprintf(stdout, "2. Select records using default collation.\n");
    sql = "select * from issues order by issue";
    print_sql_result(db, sql);

    /* Test Oracle collation. */
    fprintf(stdout, "\nSelect records using political collation. \n");
    sql = "select * from issues order by issue collate POLITICAL";
    print_sql_result(db, sql);

    /* Done. */
    sqlite3_close(db);

    return 0;    
}

int political_collation( void* data, int l1, const void* s1, 
                                     int l2, const void* s2 )
{
    int value, opinion; struct tm* t; time_t rt;

    /* Get the unpolitical value */
	value = strcmp(s1,s2);

    /* Get the date and time */
    time(&rt);
    t = localtime(&rt);
    
    /* Form an opinion */
	switch(t->tm_wday) {
        case 0: /* Monday yes    */
            opinion = value;
            break;
        case 1: /* Tueday no     */
            opinion = -value;
            break;
        case 2: /* Wednesday bigger is better */
            opinion = l1 >= l2 ? -1:1;
            break;
        case 3: /* Thursday strongly no   */
            opinion = -100;
            break;
        case 4: /* Friday strongly yes    */
            opinion = 100;
            break;
        case 5: /* Saturday golf, everything's the same */
            opinion = 0;
            break;
        default: /* Sunday - Meet the Press, opinion changes 
                    by the hour */
            opinion = 2*(int)sin(t->tm_hour*180);
    }

    /* Now change it on a whim */
    opinion = rand()-(RAND_MAX/2) > 0 ? -1:1;

    return opinion;
}

void setup(sqlite3* db)
{
    const char* sql;

    /* Turn SQL logging on. */
    log_sql(db, 1);

    /* Drop table if exists. */
    fprintf(stdout, "Dropping table issues, if exists.\n");
    drop_table(db, "issues");

    /* Create table. */
    fprintf(stdout, "Creating table issues.\n");
    sql = "create table issues( issue text )";

    execute(db, sql);

    /* Add records. */
    fprintf(stdout, "Populating table issues.\n");

    sql = "insert into issues values ('%s')";
    execute(db, sql, "Defense");
    execute(db, sql, "Foreign Policy");
    execute(db, sql, "Health Care");
    execute(db, sql, "National Security");
    execute(db, sql, "Economy");
    execute(db, sql, "Unemployment");
    execute(db, sql, "Education");
    execute(db, sql, "Abortion");
    execute(db, sql, "Social Security");
    execute(db, sql, "Environment");

    /* Turn SQL logging off. */
    log_sql(db, 0);

    fprintf(stdout, "\n");
}
