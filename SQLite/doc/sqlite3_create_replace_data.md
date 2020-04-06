[TOC]

## `SQLITE3`

​	在开始之前先介绍一下什么是`SQLite`数据库,`SQLite`是一款开源的、嵌入式关系型数据库，`SQLite`非常适合前途是产品，因为其没有独立运行的进程，它与服务的应用程序在应用程序的进程空间内共生共存。它的代码和应用程序的代码是在一起的或者说是嵌入其中，作为托管它的程序的一部分。

​	为什么学习数据库建议你先学习`SQLite`数据库，特别是嵌入式开发的人员。因为`SQLite`的作者都说过`SQLite`是一款无论你使用的是什么操作系统，都能够在5分钟内完成，数据库的安装配置，以及创建自己的第一个数据库。

## 为什么要用 `SQLite`？

- 不需要一个单独的服务器进程或操作的系统（无服务器的）。
- `SQLite` 不需要配置，这意味着不需要安装或管理。
- 一个完整的 `SQLite` 数据库是存储在一个单一的跨平台的磁盘文件。
- `SQLite` 是非常小的，是轻量级的，完全配置时小于 `400KiB`，省略可选功能配置时小于`250KiB`。
- `SQLite` 是自给自足的，这意味着不需要任何外部的依赖。
- `SQLite` 事务是完全兼容 ACID 的，允许从多个进程或线程安全访问。
- `SQLite` 支持 `SQL92`（`SQL2`）标准的大多数查询语言的功能。
- `SQLite` 使用 ANSI-C 编写的，并提供了简单和易于使用的 `API`。
- `SQLite` 可在 UNIX（Linux, Mac OS-X, Android, `iOS`）和 Windows（`Win32`, `WinCE`, `WinRT`）中运行

​	好了说了那么多，现在直接进入正题，进入 [地址]:https://www.sqlite.org/index.html 下载最新的`SQLite`源码，按照源码中文档安装数据库，一下的代码都是在`UBUNTU 16.04`上测试通过的代码 ，测试代码的git仓库见文末。

## `SQLite`命令

​	将命令按照操作的性质可以分为一下几种;

**`DDL`- 数据定义语言**

| `CREATE` | 创建一个新的表，一个表的视图，或者数据库中其他的对象 |
| -------- | ---------------------------------------------------- |
| `ALTER`  | 修改数据库中某个已有的数据库对象，比如一个表         |
| `DROP`   | 删除整个表，或者表的视图，或者数据库中其他对象       |



**`DML`- 数据操作语言**

| `INSERT` | 创建一条记录 |
| -------- | ------------ |
| `UPDATE` | 修改记录     |
| `DELETE` | 删除记       |



**`DQL`- 数据查询语言**

| 命令     | 描述                       |
| -------- | -------------------------- |
| `SELECT` | 从一个或者多个表中检索记录 |



- `SQLite`的一些简单的使用，以及命令可以参考 [地址](https://www.runoob.com/sqlite/sqlite-tutorial.html)
- 这里就主要说一些使用的场景

## 本文用到的函数说明

```c
/*
** Open a new database handle.
*/
//< 打开操作句柄
int sqlite3_open(
  const char *zFilename,  //< 文件名字
  sqlite3 **ppDb   //< 操作句柄
)

//< 返回UTF8编码的英文常见错误
/*
** Return UTF-8 encoded English language explanation of the most recent
** error.
*/
const char *sqlite3_errmsg(sqlite3 *db)
    
/*
** Execute SQL code.  Return one of the SQLITE_ success/failure
** codes.  Also write an error message into memory obtained from
** malloc() and make *pzErrMsg point to that message.
**
** If the SQL is a query, then for each row in the query result
** the xCallback() function is called.  pArg becomes the first
** argument to xCallback().  If xCallback=NULL then no callback
** is invoked, even for queries.
*/
 //< 执行SQL语句
int sqlite3_exec(
  sqlite3 *db,                /* The database on which the SQL executes */
  const char *zSql,           /* The SQL to be executed */
  sqlite3_callback xCallback, /* Invoke this callback routine，回调函数，执行的SQL语句有输出时 */
  void *pArg,                 /* First argument to xCallback() */
  char **pzErrMsg             /* Write error messages here */
)
    
/*
** Windows systems should call this routine to free memory that
** is returned in the in the errmsg parameter of sqlite3_open() when
** SQLite is a DLL.  For some reason, it does not work to call free()
** directly.
**
** Note that we need to call free() not sqliteFree() here.
*/
    
void sqlite3_free(char *p){ free(p); }

/*
** The type for a callback function.
*/
//< 回调函数定义
typedef int (*sqlite3_callback)(void*,int,char**, char**);
/*
** A function to close the database.
**
** Call this function with a pointer to a structure that was previously
** returned from sqlite3_open() and the corresponding database will by closed.
**
** All SQL statements prepared using sqlite3_prepare() or
** sqlite3_prepare16() must be deallocated using sqlite3_finalize() before
** this routine is called. Otherwise, SQLITE_BUSY is returned and the
** database connection remains open.
*/
//< 关闭SQL句柄
int sqlite3_close(sqlite3 *);
```



​	实现创建数据表，向数据表中添加数据，并查询对应表格数据，使用回调函数打印出查询出的数据。

`creat_db_datebase.c`

```c
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
```



[代码地址]:https://github.com/zzu-andrew/linux-sys/tree/dfew/SQLite