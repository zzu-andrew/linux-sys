#include "sqlite3.h"

/* Convenience function: Executes SQL and prints error info, if any. */
int execute(sqlite3 *db, const char* sql, ...);

/* Drops a table if it exists. */
int drop_table(sqlite3* db, const char* name);

/* Executes SQL and prints results using sqlite3_get_table() */
int print_sql_result(sqlite3 *db, const char *sql);

/* Prints column headers w/type info and all rows for statement. */
int print_stmt_result(sqlite3_stmt *stmt);

/* Prints msg w/args followed by last error for db handle. */
void print_error(sqlite3 *db, const char* msg, ...);

/* Prints the event name given code.*/
const char* event_description(int type);

/* Turn SQL tracing on or off */
void log_sql(sqlite3* db, int flag);

/* For sqlite3_trace() */
void trace_sql(void *data, const char *sql);

/* Convert a null terminated string to uppercase. Must free return value. */
const char* uppercase(const char* value);

/* Convert a null terminated string to lowercase. Must free return value. */
const char* lowercase(const char* value);
