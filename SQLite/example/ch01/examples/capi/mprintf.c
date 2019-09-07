#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char **argv)
{
    char *sql;
    char *trouble = "'Here's trouble'";
    
    sql = sqlite3_mprintf("insert into x values('%q')", trouble);
    fprintf(stdout, "%s\n", sql);
    sqlite3_free(sql);

    return 0;    
}
