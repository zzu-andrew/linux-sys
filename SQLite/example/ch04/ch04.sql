insert into foods (name, type_id) values ('Cinnamon Bobka', 1);

select * from foods where name='Cinnamon Bobka';

select max(id) from foods;

select last_insert_rowid();

insert into foods values(NULL, 1, 'Blueberry Bobka');
select * from foods where name like '%Bobka';

insert into foods
values (null,
       (select id from food_types where name='Bakery'),
       'Blackberry Bobka');
select * from foods where name like '%Bobka';

insert into foods
select last_insert_rowid()+1, type_id, name from foods
where name='Chocolate Bobka';
select * from foods where name like '%Bobka';

create table foods2 (id int, type_id int, name text);
insert into foods2 select * from foods;
select count(*) from foods2;

create table foods2 as select * from foods;
select count(*) from list;

create temp table list as
select f.name food, t.name name,
       (select count(episode_id)
        from foods_episodes where food_id=f.id) episodes
from foods f, food_types t
where f.type_id=t.id;
select * from list;

update foods set name='CHOCOLATE BOBKA'
where name='Chocolate Bobka';
select * from foods where name like 'CHOCOLATE%';

delete from foods where name='CHOCOLATE BOBKA';

create table contacts (
id integer primary key,
name text not null collate nocase,
phone text not null default 'UNKNOWN',
unique (name,phone) );

insert into contacts (name,phone) values ('Jerry','UNKNOWN');
insert into contacts (name) values ('Jerry');
insert into contacts (name,phone) values ('Jerry', '555-1212');

select rowid, oid,_rowid_,id, name, phone from contacts;

create table maxed_out(id integer primary key autoincrement, x text);
insert into maxed_out values (9223372036854775807, 'last one');
select * from sqlite_sequence;

drop table maxed_out;
create table maxed_out(id integer primary key autoincrement, x text);
insert into maxed_out values(10, 'works');
select * from sqlite_sequence;

insert into maxed_out values(9, 'works');
select * from sqlite_sequence;

insert into maxed_out values (9, 'fails');

insert into maxed_out values (null, 'should be 11');
select * from maxed_out;

select * from sqlite_sequence;

create table pkey(x text, y text, primary key(x,y));
insert into pkey values ('x','y');
insert into pkey values ('x','x');
select rowid, x, y from pkey;

insert into contacts (name) values ('Jerry');
select * from contacts;

create table times ( id int,
  date not null default current_date,
  time not null default current_time,
  timestamp not null default current_timestamp );
insert into times (id) values (1);
insert into times (id) values (2);
select * from times;

insert into contacts (phone) values ('555-1212');

create table contacts
( id integer primary key,
name text not null collate nocase,
phone text not null default 'UNKNOWN',
unique (name,phone),
check (length(phone)>=7) );

create table foo
( x integer,
y integer check (y>x),
z integer check (z>abs(y)) );

insert into foo values (-2, -1, 2);
insert into foo values (-2, -1, 1);

update foo set y=-3 where x=-3;

create table foods(
  id integer primary key,
  type_id integer references food_types(id)
  on delete restrict
  deferrable initially deferred,
  name text );

insert into contacts (name,phone) values ('JERRY','555-1212');

select typeof(3.14), typeof('3.14'),
       typeof(314), typeof(x'3142'), typeof(NULL);

drop table domain;
create table domain(x);
insert into domain values (3.142);
insert into domain values ('3.142');
insert into domain values (3142);
insert into domain values (x'3142');
insert into domain values (null);
select rowid, x, typeof(x) from domain;

select f.name, ft.name, e.name
from foods f
inner join food_types ft on f.type_id=ft.id
inner join foods_episodes fe on f.id=fe.food_id
inner join episodes e on fe.episode_id=e.id;

create view details as
select f.name as fd, ft.name as tp, e.name as ep, e.season as ssn
from foods f
inner join food_types ft on f.type_id=ft.id
inner join foods_episodes fe on f.id=fe.food_id
inner join episodes e on fe.episode_id=e.id;

select fd as Food, ep as Episode
        from details where ssn=7 and tp like 'Drinks';

drop view name;

SELECT * FROM foods WHERE name='JujyFruit';

create table foo(a text, b text);
create unique index foo_idx on foo(a,b);
insert into foo values ('unique', 'value');
insert into foo values ('unique', 'value2');
insert into foo values ('unique', 'value');

create table foo (a,b,c,d);

create index foo_idx on foo (a,b,c,d);

select * from foo where a=1 and b=2 and d=3;

select * from foo where a>1 and b=2 and c=3 and d=4;

select * from foo where a=1 and b>2 and c=3 and d=4;

create temp table log(x);

create temp trigger foods_update_log update of name on foods
begin
  insert into log values('updated foods: new name=' || new.name);
end;

begin;
update foods set name='JUJYFRUIT' where name='JujyFruit';
select * from log;
rollback;

create temp table log(x);

create temp trigger foods_update_log after update of name on foods
begin
  insert into log values('updated foods: new name=' || new.name);
end;

begin;
update foods set name='JUJYFRUIT' where name='JujyFruit';
rollback;

create view foods_view as
  select f.id fid, f.name fname, t.id tid, t.name tname
  from foods f, food_types t;

create trigger on_update_foods_view
instead of update on foods_view
for each row
begin
   update foods set name=new.fname where id=new.fid;
   update food_types set name=new.tname where id=new.tid;
end;

.echo on
-- Update the view within a transaction
begin;
update foods_view set fname='Whataburger', tname='Fast Food' where fid=413;
-- Now view the underlying rows in the base tables:
select * from foods f, food_types t where f.type_id=t.id and f.id=413;
-- Roll it back
rollback;
-- Now look at the original record:
select * from foods f, food_types t where f.type_id=t.id and f.id=413;
begin;
update foods_view set fname='Whataburger', tname='Fast Food' where fid=413;
select * from foods f, food_types t where f.type_id=t.id and f.id=413;

rollback;

select * from foods f, food_types t where f.type_id=t.id and f.id=413;

begin;
delete from foods;
rollback;
select count(*) from foods;

create table test as select * from foods;
create unique index test_idx on test(id);
alter table test add column modified text not null default 'no';
select count(*) from test where modified='no';

update or fail test set id=800-id, modified='yes';

select count(*) from test where modified='yes';

drop table test;

create temp table cast(name text unique on conflict rollback);
insert into cast values ('Jerry');
insert into cast values ('Elaine');
insert into cast values ('Kramer');

begin;
insert into cast values('Jerry');
commit;

create trigger foods_update_trg
before update of type_id on foods
begin
  select case
     when (select id from food_types where id=new.type_id) is null
     then raise( abort,
                 'Foreign Key Violation: foods.type_id is not in food_types.id')
  end;
end

explain query plan select * from foods where id = 145;

