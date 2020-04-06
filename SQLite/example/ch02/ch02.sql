create table test (id integer primary key, value text);

insert into test (id, value) values(1, 'eenie');
insert into test (id, value) values(2, 'meenie');
insert into test (value) values('miny');
insert into test (value) values('mo');

.mode column
.headers on
select * from test;

select last_insert_rowid();

create index test_idx on test (value);
create view schema as select * from sqlite_master;

