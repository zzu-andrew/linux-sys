
create table episodes (
  id integer primary key,
  season int,
  name text );

create table foods(
  id integer primary key,
  type_id integer,
  name text );

create table foods_episodes(
  food_id integer,
  episode_id integer );

create table food_types(
  id integer primary key,
  name text );

insert into food_types values (NULL, 'Bakery');
insert into food_types values (NULL, 'Cereal');
insert into food_types values (NULL, 'Chicken/Fowl');
insert into food_types values (NULL, 'Condiments');
insert into food_types values (NULL, 'Dairy');
insert into food_types values (NULL, 'Dip');
insert into food_types values (NULL, 'Drinks');
insert into food_types values (NULL, 'Fruit');
insert into food_types values (NULL, 'Junkfood');
insert into food_types values (NULL, 'Meat');
insert into food_types values (NULL, 'Rice/Pasta');
insert into food_types values (NULL, 'Sandwiches');
insert into food_types values (NULL, 'Seafood');
insert into food_types values (NULL, 'Soup');
insert into food_types values (NULL, 'Vegetables');
