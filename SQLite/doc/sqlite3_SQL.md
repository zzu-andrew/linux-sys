[TOC]





## 常用SQL语句

```bash
$sqlite3 test.db #使用sqlite3打开一个数据库，如果数据库不存在就创建对应的数据库
.echo on  # 在屏幕上打印执行的SQL语句
.mode column #以列的模式显示 结果
.headers on # 包含列名称
.nullvalue NULL # 将nulls打印成NULL
```



## 创建表

```bash
create [temp] table table_name (column_definitions [, constraints]);
#指定 temp说明创建的表是临时表，临时表只存活于当前会话，会话结束表会立即释放
```



## 修改表

```bash
lter table table{rename to name | add column column_def};
# alter table contacts add column email text not  null default '' collate nocase;
```



## 数据表测查询

```bash
select name from (select name, type_id from (select * from foods));
select heading from tables where predicate;
select * from dogs where color='purple' and grin= 'toothy';
# %可以与任一多个或者单个字符匹配，下划线可以与任一一个字符匹配
select id, name from foods where name like '%ac%p%';
select id, name from foods where name like '%ac%P%' and name not like '%Sch%';
```

### 限定和排序

- 可以使用`limit`和`offset`关键字限定结果集的大小和范围，`limit`指定返回记录中的最大数量，`offset`指定偏移的记录数。

```bash
select * from food_types order by id limit 1 offset 1;
# 关键字offset在结果集中，跳过一行(Bakery)，关键字limit限制最多返回一行（Cereal）

# order by使返回的结果按照某种排序进行输出-asc(默认的升序)或desc(降序)。
select * from foods where name like 'B%' order by type_id desc, name limit 10;
# limit和offset一起使用时，可以使用逗号代替offset
# 有些人可能认为这里的语法应该倒过来，在SQLite中，使用缩写时，offset总是优先limit，紧随limit关键字的值是offset 2 ,也要注意到，offset依赖于limit, 也就是说，可以只使用Limit不到offset但是反过来不行。
select * from foods where name like 'B%' order by type_id desc, name limit 1 offset 2;
select * from foods where name like 'B%' order by type_id desc, name limit 2, 1;
```



### 多表连接

​	连接(join)是多表(关系)数据工作的关键，它是select命令的第一个操作，连接操作的结果作为输入，供select语句的其他部分(过滤)处理。

```bash
select foods.name, food_types_.name from foods, food_types where fods.type_id =food_types.id limit 10;
```

### 外连接

```bahs
# 外链接相当于取两表相交的地方
select * from foods inner join food_types  on foods.id = food_types.id;
```

### 交叉连接

```bash
select * from foods, food_types;
```

### 子查询

```bash
# 子查询就是子啊select语句又嵌套select语句。
select 1 in (1,2,3);
select count(*) from foods where type_id in (1,2);
select count(*) from foods where type_id in (select id from food_types where name='Bakery' or name='Cereal');
```

### 条件结果

```bash
select name || case type_id 
				when 7 then ' is a drink '
				when 8 then 'is a fruit'
				when 9 then ' is junkfood'
				when 13 then ' is seafood'
				else null
				end description
from foods 
where description is not null 
order by name
limit 10;
```

### 处理SQLite中的NULL

- 可以通过is null 或者is not null操作符监测null是否 存在。
- null不等于任何值，包含==NUL==L。



## 高级SQL

### 修改数据

#### 插入数据

```bash
insert into table (column_list) values (value_list);
# insert into foods (nam, type_id) values ('Cinnamon Bobla', 1);
```

#### 跟新记录

```bash
update table set update_list where predicate;
```

#### 删除数据

```bash
delete from table where predicate;
delete from foods where name = 'CHOCOLATE BOBKA';
```





