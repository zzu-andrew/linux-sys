# SQLite



## 命令

**创建数据库**

`sqlite3 test.db`

``

**创建数据表**

`sqlite> create	table test (id integer primary key ,value text);`



**插入数据**

```
sqlite> insert into test (id, value) values (1, 'name');
sqlite> insert into test (id, value) values (2, 'meenie');
sqlite> insert into test (value) values ('minay'); 
sqlite> insert into test (value) values ('mo');
```



**设置索引和视图**

```
sqlite> create index test_idx on test (value);
sqlite> select * from test;
id          value     
----------  ----------
1           enable    
2           meenie    
3           minay     
4           mo        
sqlite> create view shema as select * from sqlite_master;
```



**设置输出模式**

```
sqlite> .mode column
sqlite> .headers on
sqlite> select * from test;
id          value     
----------  ----------
1           enable    
2           meenie    
3           minay     
4           mo 
.nullvalue NULL NULL显示时是空字符串
改变CLP的shell提示符，使用：
.prompt [value]
```

输出为`csv`格式

```
sqlite> .output file.csv
sqlite> .separator ,
sqlite> select * from test;
sqlite> .output stdout
sqlite> .q 
SQLite$ cat file.csv 
1,enable
2,meenie
3,minay
4,mo
```

导出test表中以带字母m开始的值，并以逗号分隔，导出到csv文件

```
sqlite> .output test.csv
sqlite> .separator ,
sqlite> select * from test where value like 'm%';  
sqlite> .output stdout
sqlite> .q
```





**查看所有的表和视图**

```
sqlite> .tables
shema  test
```

`shema`视图，　`test`索引

**显示一个表的索引**

```
.indices [table name]
```



**显示一个表的建表语句(DDL)**

```
sqlite> .schema test
CREATE TABLE test (id integer primary key ,value text);
CREATE INDEX test_idx on test (value);
```

**导出数据文件到新文件－SQL**

```
sqlite> .output filenam.db
sqlite> .dump
sqlite> .output stdout
sqlite> .q
```

**导入一个数据表**

```
.import [file][table] 
```

**查看分隔符的当前值**

```
sqlite> .show
        echo: off
         eqp: off
     explain: auto
     headers: off
        mode: list
   nullvalue: ""
      output: stdout
colseparator: "|"
rowseparator: "\n"
       stats: off
       width: 
    filename: test.db
```

**read命令**

`.read`命令用来导入`.dump`命令创建的文件

```
drop table test
drop view  schema 
.read file.db
```

## SQLite中的SQL

**insert**

`insert into table (column_list) values (value_list);`

`insert into foods (name, type_id) values ('Cinnamon Bobka'm 1);`

- 如果insert语句为表助中所有的字段提供值，可以省略字段列表

`insert into foods values(NULL, 1, 'Blueberry Bobka');`

```sql
insert into foods 
values (null,
	(select id from food_types where name='Bakery'), 'Blackberry Boabka');
```

- 插入多行

```sql
insert into foods2 select * from foods
```

**create**

- 有一种方便的方式创建表和插入表

```sql
create table foods as select * from foods;
```

- 可以指定多个主键，只要主键不是完全相同就不会报错

```sql
create table pkey(x text, y text, primary key(x, y));
insert into pkey values ('x', 'y');
insert into pkey values ('x', 'x');
```

```sql
sqlite> create table pkey(x text, y text, primary key(x, y));
sqlite> insert into pkey values ('x', 'y');
sqlite> insert into pkey values ('x', 'y');
Error: UNIQUE constraint failed: pkey.x, pkey.y
sqlite> insert into pkey values ('x', 'x');
sqlite> 
```





**select**

`select * from foods where name = 'Cinnnamon Bobka';`

`select max(id) from foods ;`

**update**

`update table set update_list where predicate;`

`update foods set name 'CHOCOLATE BOBKA' where name = 'Cholocate Bobka';`

**delete**

`delete from table where predicate;`

`delete from foods where name='CHOCOLATE BOBKA';`



### 默认值

- 设置默认值，当没有提供该值的时候就会将默认值写到数据库中

```sql
create table times(id int, 
                   data not null default current_date,
                   time not null default current_time,
                   timestamp not null default current_timestamp
                  );
```



### 约束

- 如果你不想使用null值，那么可以指定NOT NULL
- 使用check约束允许定义表达式来插入或这更新字段值

```sql
create table contacts 	
	(id integer primary key,
    name text not null collate nocase,
    phone text not null default 'UNKNOW',
    unique (name , phone),
    check (length(phone) >= 7));
```

- 也可以这样指定约束条件，该表中每一个ｚ值必须大于对应的ｙ字段,y大于x字段

```sql
create table foo 
(x integer,
y integer check (y>x),
z integer check (z>abs(y)) );
```

### 存储

- 使用typeof函数定义对应的数据存储类型

```sql
sqlite> select typeof(NULL);
typeof(NULL)
------------
null        
sqlite> select typeof(3.123);                   
typeof(3.123)
-------------
real         
sqlite> select ('text');
('text')  
----------
text
-- x'abcd' 按照１６进制存储数据
sqlite> select typeof(x'abcd');
typeof(x'abcd')
---------------
blob
```



### 视图

- 视图即虚拟表，也称为派生表，因为他的内容个都是派生自其他表的查询结果，虽然视图的内容看起来像基本表一样，但是他们不是基本表，基本表的内容是持久的，而视图的内容是使用时动态产生的；

- 创建视图的语法

`create view name as select-stmt;`

- 删除视图的语法

`drop view name;`

### 索引

- 索引是一种用来在某种情况下加速查询的结构

`select * from foods where name='jujyfruit';`

SQLite使用B-Tree做索引，索引会增加数据库的大小，加快数据库的查找速度，但是可能会降低insert、update和类似的操作速度。

- 创建索引的命令

`create index [unique] index_name on table_name (columns)`

​    变量index_name是索引的名称，table_name是包含索引所在字段的表的名称，变量columns是一个字段或以逗号分隔的多个字段

​    在foods.name上创建大小写不敏感的索引：

`create index foods_name_index on foods (name collate nocase);`

​	这意味着name字段的值将按照大小写无关进行排序，可以在shell中使用SQL命令.indices foods 列出表中的索引

​	也可以用.shema foods命令查看更多的信息

​	使用多字段索引

```sql
create index foo_idx on foo (a, b, c, d);
select * from foo where a=1 and b=2 and d=3;
select * from foo where a>1 and b=2 and c=3 and d=4;
select * from foo where a=1 and b>2 and c=3 and d=4;
```

### 触发器

​	当具体的表发生特定的数据库事件时，触发器执行对应的SQL命令。

- 创建触发器的命令

```sql
create [temp|temporary] trigger name
[before|after] [insert|delete|update|update of columns] on table 
action
```

### 事务

​	事务由三个命令控制：`begin、commit和rollback`，begain开始一个事务，begin之后的所用操作都可以取消，如果连接终止前没有发出commit，也会被取消。commit提交事务开始后所执行的所有操作，类似的rollback还原之后所有的操作。

```sql
sqlite>begin;
sqlite>delete from foods;
sqlite>rollback;
sqlite>select count(*) from foods;
```

### 数据库锁

​	SQLite采用粗粒度的锁，当一个连接要写数据库的时候，所有其他的连接被锁住，直到写连接结束它的事务。SQLite有一个加锁表，用于帮助不同的写数据库能够在最后一刻在加锁，以保证最大的并发性。

## API

​																																																						函数sqlite																	3_mpr													intf(),它是标准C语言库函数sprintf()的变体，它具有特殊的替换功能，它替换%q和%Q标示位置，转义SQL的特定值，%q和%s的工作方式类似，因为它取代参数列表中以NULL结尾的字符串，同时它会将单引号字符转义，这有																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																	助于防止SQL注入攻击。%Q和%q的格式相同，但它会用额外的单引号包围所产生的字符串。

```c
char * before = "Hey, at least %q no pigman.";
char * after = sqlite3_mprintf(before, "he's");
//转化的结果为
// “Ｈｅy, at least he''s no pig-man”
```



### 连接与断开

​																																																																																																																																																																		可以使用`sqlite3_open_v2()`、`sqlite3_open()`或`sqlite3_open16()`函数打开数据库，这些函数声明如下：

```c
SQLITE_API int sqlite3_open_v2(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb,         /* OUT: SQLite db handle */
  int flags,              /* Flags */
  const char *zVfs        /* Name of VFS module to use */
);
```

- 对应的flag定义

```c
  /*
  ** CAPI3REF: Flags For File Open Operations
  **
  ** These bit values are intended for use in the
  ** 3rd parameter to the [sqlite3_open_v2()] interface and
  ** in the 4th parameter to the [sqlite3_vfs.xOpen] method.
  */
  #define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_DELETEONCLOSE    0x00000008  /* VFS only */
  #define SQLITE_OPEN_EXCLUSIVE        0x00000010  /* VFS only */
  #define SQLITE_OPEN_AUTOPROXY        0x00000020  /* VFS only */
  #define SQLITE_OPEN_URI              0x00000040  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_MEMORY           0x00000080  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_MAIN_DB          0x00000100  /* VFS only */
  #define SQLITE_OPEN_TEMP_DB          0x00000200  /* VFS only */
  #define SQLITE_OPEN_TRANSIENT_DB     0x00000400  /* VFS only */
  #define SQLITE_OPEN_MAIN_JOURNAL     0x00000800  /* VFS only */
  #define SQLITE_OPEN_TEMP_JOURNAL     0x00001000  /* VFS only */
  #define SQLITE_OPEN_SUBJOURNAL       0x00002000  /* VFS only */
  #define SQLITE_OPEN_MASTER_JOURNAL   0x00004000  /* VFS only */
  #define SQLITE_OPEN_NOMUTEX          0x00008000  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_FULLMUTEX        0x00010000  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_SHAREDCACHE      0x00020000  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_PRIVATECACHE     0x00040000  /* Ok for sqlite3_open_v2() */
  #define SQLITE_OPEN_WAL              0x00080000  /* VFS only */
```

  

```c
SQLITE_API int sqlite3_open(
  const char *zFilename, 
  sqlite3 **ppDb 
);
```

```c
SQLITE_API int sqlite3_open16(
  const void *zFilename, 
  sqlite3 **ppDb
)
```



注：使用`sqlite3_close`关闭连接时，如果连接上有打开的事务，该事务将进行回滚。

- `sqlite3_exec`提供一种快速、方便执行SQL命令的方法，对修改数据库的命令特别方便，因此通常也称为便捷函数，一个简单的API调用能很好地封装很多其他的任务。
- 参数**`zSql`**中能提供很多SQL命令，`sqlite3_exec`将解析和执行`sql`字符串中的每个命令，直到达到该字符串的末尾或遇到错误。

```c
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
SQLITE_API int sqlite3_exec(
  sqlite3 *db,                /* The database on which the SQL executes */
  const char *zSql,           /* The SQL to be executed */
  sqlite3_callback xCallback, /* Invoke this callback routine */
  void *pArg,                 /* First argument to xCallback() */
  char **pzErrMsg             /* Write error messages here */
)
```





​																																																																																																																																	

​																																																																																																																																																																																																																																																																																																																																																																																																																																		







































