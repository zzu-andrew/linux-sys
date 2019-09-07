#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

const char* event_description(int type);

int auth( void* x, int type, 
          const char* a, const char* b, 
          const char* c, const char* d );

int main(int argc, char **argv)
{
    sqlite3 *db;
    sqlite3 *db2;
    char *zErr;
    int rc;
    char *sql;

    /* Connect to test.db */
    rc = sqlite3_open("test.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    /* Connect to test2.db */
    rc = sqlite3_open("test2.db", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    /* Drop table foo2 in test2 if exists */
    sqlite3_exec(db2, "drop table foo2", NULL, NULL, &zErr);
    
    /* Register the authorizer function */
    sqlite3_set_authorizer(db, auth, NULL);

    /* Attach database test2.db to test.db */
    printf("program : Attaching database test2.db\n");
    sqlite3_exec(db, "attach 'test2.db' as test2", NULL, NULL, &zErr);

    /* Select record from test2.db foo2 in test.db */
    printf("program : Selecting record from attached database test2.db\n");
    sqlite3_exec(db, "select * from foo2", NULL, NULL, &zErr);

    /* Test transactions events */

    printf("program : Starting transaction\n");
    sqlite3_exec(db, "BEGIN", NULL, NULL, &zErr);

    printf("program : Committing transaction\n");
    sqlite3_exec(db, "COMMIT", NULL, NULL, &zErr);

    printf("program : Starting transaction\n");
    sqlite3_exec(db, "BEGIN", NULL, NULL, &zErr);

    printf("program : Aborting transaction\n");
    sqlite3_exec(db, "ROLLBACK", NULL, NULL, &zErr);

    /* Test table events */
    printf("program : Creating table\n");
    sqlite3_exec(db, "create table foo(x int)", NULL, NULL, &zErr);

    printf("program : Inserting record\n");
    sqlite3_exec(db, "insert into foo values (1)", NULL, NULL, &zErr);

    printf("program : Selecting record\n");
    sqlite3_exec(db, "select * from foo", NULL, NULL, &zErr);

    printf("program : Updating record\n");
    sqlite3_exec(db, "update foo set x=1", NULL, NULL, &zErr);

    printf("program : Deleting record\n");
    sqlite3_exec(db, "delete from foo", NULL, NULL, &zErr);

    printf("program : Dropping table\n");
    sqlite3_exec(db, "drop table foo", NULL, NULL, &zErr);
    
    sqlite3_close(db);

    return 0;    
}
 
int auth( void* x, int type, 
          const char* a, const char* b, 
          const char* c, const char* d )
{
    const char* operation = a;
    
    printf( "Authorizor %-6s : %s in ", c, event_description(type));

    if((a != NULL) && (type == SQLITE_TRANSACTION)) {
        printf("-> %s Transaction", operation);
    }

    switch(type) {
        case SQLITE_CREATE_INDEX:
        case SQLITE_CREATE_TABLE:
        case SQLITE_CREATE_TRIGGER:
        case SQLITE_CREATE_VIEW:
        case SQLITE_DROP_INDEX:
        case SQLITE_DROP_TABLE:
        case SQLITE_DROP_TRIGGER:
        case SQLITE_DROP_VIEW:
        {
            // Schema has been modified somehow.
            printf("-> Schema modified");
        }
    }

    if(type == SQLITE_ATTACH) {
        printf("-> %s", a);
    }

    if(type == SQLITE_DETACH) {
        printf("-> %s", a);
    }

    printf("\n");

    return SQLITE_OK;
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
