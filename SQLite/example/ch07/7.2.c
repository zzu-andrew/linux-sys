int main(int argc, char **argv)
{
    int rc; sqlite3 *db; char *sql;

    sqlite3_open_v2("foods.db", &db);

    /* Register aggregate. */
    fprintf(stdout, "Registering aggregate str_agg()\n");

    /* Turn SQL tracing on. */
    log_sql(db, 1);

    /* Register aggregate. */
    sqlite3_create_function( db, "str_agg", 1, SQLITE_UTF8, db,
                             NULL, str_agg_step, str_agg_finalize);

    /* Test. */
    fprintf(stdout, "\nRunning query: \n");
    sql = "select season, str_agg(name, ', ') from episodes group by season";
    print_sql_result(db, sql);

    sqlite3_close(db);

    return 0;
}
