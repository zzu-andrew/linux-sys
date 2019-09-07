/*
+--------+     +-------+     +--------------+     +---------------+
| B-tree | --> | Pager | --> |      os      | --> | Database File |
+--------+     +-------+     +--------------+     +---------------+
                               |
                               |
                               v
                             +--------------+
                             | Journal File |
                             +--------------+
*/
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>


#define create_test_table "CREATE TABLE test("  \
                            "id                 integer," \
                            "idx1                integer," \
                            "chan                 integer," \
                            "name           TEXT    NOT NULL," \
                            "age            INT     NOT NULL," \
                            "address        CHAR(50)," \
                            "salary         REAL,"\
                            "primary key(id));"

#define create_test_null_table "CREATE TABLE test_null("  \
                            "id                 integer," \
                            "idx1                integer," \
                            "chan                 integer," \
                            "name           TEXT    NOT NULL," \
                            "age            INT     NOT NULL," \
                            "address        CHAR(50)," \
                            "salary         REAL,"\
                            "primary key(id));"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;                                                   
   char sql_str[512]; 
   int i = 0;                                                                      

   /* Open database */
   //< 如果文件存在就打开数据库文件
   //< 如果文件不存在就打开一个数据库，等有实际操作了在创建该数据库文件
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
   rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   //< 建表语句定义
   /* 创建主键 */ //"ID INT PRIMARY KEY     NOT NULL," 


   /* Execute SQL statement */
   //< 返回程序生成的执行的任何返回
   rc = sqlite3_exec(db, create_test_table, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL test: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

     for (i = 0; i < 30; i++)
    {
        snprintf(sql_str, sizeof(sql_str), 
            "replace into test(id, idx1, chan, name, age)"
            "values(%d, %d, %d, '%s', %d);",
                1, 2, 3, "Mack", i);
    }
    rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }


   /* Execute SQL statement */
   //< 返回程序生成的执行的任何返回
   rc = sqlite3_exec(db, create_test_null_table, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

   
    for (i = 0; i < 30; i++)
    {
        snprintf(sql_str, sizeof(sql_str), 
            "replace into test_null(id, idx1, name, age)"
            "values(%d, %d, '%s', %d);",
                1, 2, "Mack", i);
    }
    rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }

   sqlite3_close(db);
   return 0;
}
