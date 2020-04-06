[TOC]



## delete的实现

衔接[SQLite数据库-数据表的创建，插入数据和查询数据]:<https://blog.csdn.net/andrewgithub/article/details/100717099> 



​	上一篇文章讲述了，数据库的创建、数据的插入和删除，这里衔接上一篇文章主要讲述数据的删除。

​	删除数据，注意并不是删除一个数据表，只是删除一个数据表中的一个数据项；

`creat_db_delete.c` 代码仓库路径：<https://github.com/zzu-andrew/linux-sys/tree/dfew/SQLite>

```c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
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
   int rc;
   char *sql;
   char sql_str[512];
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
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

    //< 插入一条，ID为2的数据
    snprintf(sql_str, sizeof(sql_str), "replace into class"
                "(ID, NAME, AGE, ADDRESS, SALARY)"
                " values (%d, '%s', %d, '%s', %f)",
                2, "alice", 18, "10.1.1.1", 100000.123
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
    fprintf(stdout, "----------------------------------------------------------!\n");
    fprintf(stdout, "Before delete !!\n");
    memcpy(sql_str, "select * from class;", sizeof(sql_str));
    rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }

   /* Create merged SQL statement */
   //< 将 ID = 2的数据删除
    fprintf(stdout, "----------------------------------------------------------!\n");
    fprintf(stdout, "after delete !!\n");
   sql = "DELETE from class where ID=2; " \
         "SELECT * from class";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
 
   sqlite3_close(db);
   return 0;
}
```

- 数据表中 ID=2的数据项以被删除

```bash
Opened database successfully
Table created successfully
Table replace successfully
----------------------------------------------------------!
Before delete !!
(null): ID = 1
NAME = alice
AGE = 18
ADDRESS = 10.1.1.1
SALARY = 100000.123

(null): ID = 2
NAME = alice
AGE = 18
ADDRESS = 10.1.1.1
SALARY = 100000.123

Table created successfully
----------------------------------------------------------!
# 数据表中 ID=2的数据项以被删除
after delete !!
Callback function called: ID = 1
NAME = alice
AGE = 18
ADDRESS = 10.1.1.1
SALARY = 100000.123

Operation done successfully
```

