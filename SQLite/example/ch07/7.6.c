int main(int argc, char **argv)
{
    char *sql; sqlite3 *db; int rc;

    sqlite3_open("foods.db", &db);

    /* Register Collation. */
    fprintf(stdout, "1. Register length_first Collation\n\n");
    sqlite3_create_collation_v2( db, "LENGTH_FIRST", SQLITE_UTF8, db,
                              length_first_collation, length_first_collation_del );

    /* Turn SQL logging on. */
    log_sql(db, 1);

    /* Test default collation. */
    fprintf(stdout, "2. Select records using default collation.\n");
    sql = "select name from foods order by name";
    print_sql_result(db, sql);

    /* Test Length First collation. */
    fprintf(stdout, "\nSelect records using length_first collation. \n");
    sql = "select name from foods order by name collate LENGTH_FIRST";
    print_sql_result(db, sql);

    /* Done. */
    sqlite3_close(db);

    return 0;
}
