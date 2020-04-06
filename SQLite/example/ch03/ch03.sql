create table episodes (
  id integer primary key,
  season int,
  name text );

create table foods(
  id integer primary key,
  type_id integer,
  name text );

create table food_types(
  id integer primary key,
  name text );

create table foods_episodes(
  food_id integer,
  episode_id integer );


select *
from foods
where name='JujyFruit'
and type_id=9;

select f.name name, types.name type
from foods f
inner join (
  select *
  from food_types
  where id=6) types
on f.type_id=types.id;

select burger
from kitchen
where patties=2
and toppings='jalopenos'
and condiment != 'mayo'
limit 1;

select id, name from foods;
insert into foods values (null, 'Whataburger');
delete from foods where id=413;


alter table contacts
        add column email text not null default '' collate nocase;

.schema contacts

create table contacts ( id integer primary key,
                        name text not null collate nocase,
                        phone text not null default 'UNKNOWN',
                        email text not null default '' collate nocase,
                        unique (name,phone) );




select * from foods where name='JujyFruit' and type_id=9;

select id, name from foods where name like 'J%';

select id, name from foods where name like '%ac%P%';

select id, name from foods
        where name like '%ac%P%' and name not like '%Sch%'

select * from food_types order by id limit 1 offset 1;

select * from foods where name like 'B%'
        order by type_id desc, name limit 10;

select * from foods where name like 'B%'
order by type_id desc, name limit 1 offset 2;

select * from foods where name like 'B%'
        order by type_id desc, name limit 2,1;

select upper('hello newman'), length('hello newman'), abs(-12);

select id, upper(name), length(name) from foods
        where type_id=1 limit 10;

select id, upper(name), length(name) from foods
        where length(name) < 5 limit 5;

select count(*) from foods where type_id=1;

select avg(length(name)) from foods;

select type_id from foods group by type_id;

select type_id, count(*) from foods group by type_id;

select type_id, count(*) from foods
        group by type_id having count(*) < 20;

select type_id, count(*) from foods;

select distinct type_id from foods;

select foods.name, food_types.name
        from foods, food_types
        where foods.type_id=food_types.id limit 10;

Select *
From foods inner join food_types on foods.id = food_types.id;

select * from foods, food_types;

select *
from foods left outer join foods_episodes on foods.id=foods_episodes.food_id;

select * from foods, food_types where foods.id=food_types.food_id;

select * from foods inner join food_types on foods.id=food_types.food_id;
select * from foods left outer join food_types on foods.id=food_types.food_id;
select * from foods cross join food_types;

select foods.name, food_types.name
from foods, food_types
where foods.type_id = food_types.id
limit 10;

select f.name, t.name
from foods f, food_types t
where f.type_id = t.id
limit 10;

select f.name as food, e1.name, e1.season, e2.name, e2.season
from episodes e1, foods_episodes fe1, foods f,
     episodes e2, foods_episodes fe2
where
  -- Get foods in season 4
  (e1.id = fe1.episode_id and e1.season = 4) and fe1.food_id = f.id
  -- Link foods with all other epsisodes
  and (fe1.food_id = fe2.food_id)
  -- Link with their respective episodes and filter out e1's season
  and (fe2.episode_id = e2.id AND e2.season != e1.season)
order by f.name;   

select count(*)
from foods
where type_id in
 (select id
  from food_types
  where name='Bakery' or name='Cereal');

select * from foods f
order by (select count(type_id)
from foods where type_id=f.type_id) desc;

select f.name, types.name from foods f
inner join (select * from food_types where id=6) types
on f.type_id=types.id;

select f.*, top_foods.count from foods f
inner join
  (select food_id, count(food_id) as count from foods_episodes
     group by food_id
     order by count(food_id) desc limit 1) top_foods
  on f.id=top_foods.food_id
union
select f.*, bottom_foods.count from foods f
inner join
  (select food_id, count(food_id) as count from foods_episodes
     group by food_id
     order by count(food_id) limit 1) bottom_foods
  on f.id=bottom_foods.food_id
order by top_foods.count desc;

select f.* from foods f
inner join
  (select food_id, count(food_id) as count
     from foods_episodes
     group by food_id
     order by count(food_id) desc limit 10) top_foods
  on f.id=top_foods.food_id
intersect
select f.* from foods f
  inner join foods_episodes fe on f.id = fe.food_id
  inner join episodes e on fe.episode_id = e.id
  where e.season between 3 and 5
order by f.name;

select f.* from foods f
inner join
  (select food_id, count(food_id) as count from foods_episodes
     group by food_id
     order by count(food_id) desc limit 10) top_foods
  on f.id=top_foods.food_id
except
select f.* from foods f
  inner join foods_episodes fe on f.id = fe.food_id
  inner join episodes e on fe.episode_id = e.id
  where e.season between 3 and 5
order by f.name;

select name || case type_id
                 when 7  then ' is a drink'
                 when 8  then ' is a fruit'
                 when 9  then ' is junkfood'
                 when 13 then ' is seafood'
                 else null
               end description
from foods
where description is not null
order by name
limit 10;

               case
                 when count(*) > 4 then 'Very High'
                 when count(*) = 4 then 'High'
                 when count(*) in (2,3) then 'Moderate'
                 else 'Low'
               end
             from foods_episodes
             where food_id=f.id) frequency
from foods f
where frequency like '%High';

