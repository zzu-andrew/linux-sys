#include <sqlite3.h>

/* Convenience function: Executes SQL and prints error info, if any. */
int execute(sqlite3 *db, const char* sql);

/* Executes SQL and prints results using sqlite3_get_table() */
int print_sql_result(sqlite3 *db, const char *sql);

/* Prints column headers w/type info and all rows for statement. */
int print_stmt_result(sqlite3_stmt *stmt);

/* Prints msg w/args followed by last error for db handle. */
void print_error(sqlite3 *db, const char* msg, ...);

/* Prints the event name given code.*/
const char* event_description(int type);

/* For sqlite3_trace() */
void trace_sql(void *data, const char *sql);
