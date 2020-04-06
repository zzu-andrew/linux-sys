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


#define create_test_table "CREATE TABLE test_not_null("  \
                            "id                 integer," \
                            "idx1                integer," \
                            "chan                 integer," \
                            "name           TEXT    NOT NULL," \
                            "age            INT     NOT NULL," \
                            "address        CHAR(50)," \
                            "salary         REAL,"\
                            "primary key(id, idx1, chan));"

#define create_test_null_table "CREATE TABLE test_null("  \
                            "id                 integer," \
                            "idx1                integer," \
                            "chan                 integer," \
                            "name           TEXT    NOT NULL," \
                            "age            INT     NOT NULL," \
                            "address        CHAR(50)," \
                            "salary         REAL,"\
                            "primary key(id, idx1, chan));"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

//TODO: 部分的sqlite版本中，对于主键为null使的处理方式不同
/***
 *  1.null不等于任何值，包括它自身，当主键为null时，会导致插入的数据会持续增长，因为数据数据库插入数据的时候
 *  找不到相同的主键组合(NULL != NULL)
 *  2.将主键为null是认为是相同的如有三个主键的组合(1, 2, null) == (1, 2, null)
 *  
 *  处理方式不同，这里处理函数执行之后看到的结果是不一样的。
 * */

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;                                                   
   char sql_str[512]; 
   int i = 0;   
   int j = 0;                                                                 

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

   /***
    * 创建含有创建主键全不为null的表
    * 
    * */
   rc = sqlite3_exec(db, create_test_table, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL test: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

    /***
    * 创建用于测试主键中含有null时的表
    * 
    * */
   rc = sqlite3_exec(db, create_test_null_table, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL test: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
    
    for (j = 0; j < 2; j ++)
    {
        /**
         * @brief 循环写入主键中没有null的数据 
         * 
         */
        for (i = 0; i < 30; i++)
        {
            memset(sql_str, 0, sizeof(sql_str));
            snprintf(sql_str, sizeof(sql_str), 
                "replace into test_not_null(id, idx1, chan, name, age)"
                "values(%d, %d, %d, '%s', %d);",
                    i, 2, 3, "Mack", i);
            rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
            if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            }else{
                fprintf(stdout, "Table created successfully\n");
            }
        }
        
        /**
         * @brief 循环写入主键中含有null的数据表
         * 
         */
        for (i = 0; i < 30; i++)
        {   
            memset(sql_str, 0, sizeof(sql_str));
            snprintf(sql_str, sizeof(sql_str), 
                "replace into test_null(id, idx1, name, age)"
                "values(%d, %d, '%s', %d);",
                    i, 2, "Mack", i);
            rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
            if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            }else{
                fprintf(stdout, "Table created successfully\n");
            }
        }
    }

    //< 查询，test_not_null表中的数据
    memcpy(sql_str, "select * from test_not_null;", sizeof(sql_str));
    rc = sqlite3_exec(db, sql_str, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }

    //< 查询，test_null表中的数据
    memcpy(sql_str, "select * from test_null;", sizeof(sql_str));
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
