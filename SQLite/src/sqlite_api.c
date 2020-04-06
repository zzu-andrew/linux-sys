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
   char *sql;                                                                          

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
   sql = "CREATE TABLE COMPANY("  \
         "id INT PRIMARY KEY     NOT NULL," \
         "name           TEXT    NOT NULL," \
         "age            INT     NOT NULL," \
         "address        CHAR(50)," \
         "salary         REAL );";

   /* Execute SQL statement */
   //< 返回程序生成的执行的任何返回
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   //< insert 
   sql =  "insert into company()";
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
