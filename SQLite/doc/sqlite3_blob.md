[TOC]





## 使用二进制的形式对数据库进行保存

 *  说明：有很多很复杂的数据库保存的时候很难保存，可以直接使用二进制的形式将数据库
 *  按照一个整体进行保存，这样能够很大程度上将低数据表设计的难度

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>


/****

 * */

typedef struct school
{
    int teacher_num;
    int student_num;
    int bicycle_num;
}SCHOOL;


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
   SCHOOL school_temp;
   for(i=0; i<argc; i++){
       if (0 == strcmp("school", azColName[i]))
       {
            memcpy(&school_temp, argv[i], sizeof(school_temp));
            printf("teacher number  = [%d], student number = [%d], bicycle number = [%d]\n\n", 
                school_temp.teacher_num, school_temp.student_num, school_temp.bicycle_num);
       }
       else
       {
           printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
       }
       
        
   }
   printf("\n");
   return 0;
}


int main(int argc, char **argv)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;
    char *sql;
    char sql_str[1024];
    SCHOOL ZZU;
    sqlite3_stmt *stmt;
    const char* tail;

    memset(&ZZU, 0, sizeof(ZZU));
    ZZU.teacher_num = 35000;
    ZZU.student_num = 90000;
    ZZU.bicycle_num = 20000;
    
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
    sql = "CREATE TABLE IF NOT EXISTS test_blob("  \
            "id             INT," \
            "NAME           TEXT," \
            "school         blob," \
            "ADDRESS        CHAR(50)," \
            "primary key(ID));";

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
    snprintf(sql_str, sizeof(sql_str), "replace into test_blob"
                "(id, NAME, school, ADDRESS)"
                " values (%d, '%s', ?, '%s')",
                1, "ZZU", "10.1.1.1");

    rc = sqlite3_prepare(db, sql_str, (int)strlen(sql), &stmt, &tail);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Error: %s\n", tail);
    }

    /***
     * int sqlite3_bind_blob(
        sqlite3_stmt *pStmt, //stmt描述语句
        int i, //< 第几个绑定参数(位置参数)，也就是第几个问号，其中问号后面可以指定位置参数
        const void *zData, //< 绑定的参数数据
        int nData,   //< 二进制数据的大小
        void (*xDel)(void*) //< 数据的类型，说明需不需slqite对传入的数据进行管理
        )
     */
    sqlite3_bind_blob(stmt, 1, (void *)&ZZU, sizeof(ZZU), SQLITE_STATIC);
    //< 执行语句
    sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    //< 查询class表中的数据
    memcpy(sql_str, "select * from test_blob;", sizeof(sql_str));
    rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "get test_blob sucess!!\n");
    }

    sqlite3_close(db);

    return 0;    
}

```

