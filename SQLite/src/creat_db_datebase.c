#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h> 

/**
 * @brief  callback
 * @note    回调函数，用于获取查看SQL语句返回数据
 * @param  *NotUsed:sqlite3_exec函数的第四个参数传入的数据 
 * @param  argc: 数据的行数
 * @param  **argv: 列数据数组
 * @param  **azColName: 列标识符数组
 * @retval 
 */
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
   char sql_str[1024];
   /* Open database */
   //< 打开数据库文件，如果对应的数据库不存在就创建
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
   //< 表格不存在就创建表格，存在不重新创建，但是返回成功
   sql = "CREATE TABLE IF NOT EXISTS class("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";

   /* Execute SQL statement */
   //< 返回程序生成的执行的任何返回
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

    memset(sql_str, 0, sizeof(sql_str));

    //< replace 官网上很少说名，其他写SQLite数据库的文章也很少介绍，我这里理解的 replace就是
    //< update与insert的合体，当存在记录的时候就相当于使用update  当记录不存在的时候就相当与使用insert
    snprintf(sql_str, sizeof(sql_str), "replace into class"
                "(ID, NAME, AGE, ADDRESS, SALARY)"
                " values (%d, '%s', %d, '%s', %f)",
                1, "alice", 18, "10.1.1.1", 100000.123
                     );
    rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table replace successfully\n");
    }

    memset(sql_str, 0, sizeof(sql_str));

    //< 查询class表中的数据
    memcpy(sql_str, "select * from class;", sizeof(sql_str));
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