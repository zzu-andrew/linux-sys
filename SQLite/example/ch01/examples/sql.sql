.mode col
.headers on
.nullvalue NULL

CREATE TABLE contacts ( id INTEGER PRIMARY KEY,
                        name TEXT NOT NULL COLLATE NOCASE,
                        phone TEXT NOT NULL DEFAULT 'UNKNOWN',
                        UNIQUE (name,phone) );

ALTER TABLE contacts 
        ADD COLUMN email TEXT NOT NULL DEFAULT '' COLLATE NOCASE;
.schema contacts

SELECT id, name FROM food_types;

SELECT NULL;

SELECT id, name FROM foods WHERE name LIKE 'J%';
SELECT id, name FROM foods WHERE name LIKE '%ac%P%';

SELECT id, name FROM foods 
WHERE name like '%ac%P%' AND name NOT LIKE '%Sch%'

SELECT * FROM foods WHERE name LIKE 'B%' 
ORDER BY type_id DESC, name LIMIT 10;

SELECT * FROM foods WHERE name LIKE 'B%' 
ORDER BY type_id DESC, name LIMIT 1,2;

SELECT UPPER('hello newman'), LENGTH('hello newman'), ABS(-12);
SELECT id, UPPER(name), LENGTH(name) FROM foods 
WHERE type_id=1 LIMIT 10;

SELECT id, UPPER(name), LENGTH(name) FROM foods 
WHERE LENGTH(name) < 5 LIMIT 5;

SELECT COUNT(*) FROM foods WHERE type_id=1;

SELECT AVG(LENGTH(name)) FROM foods;

SELECT type_id FROM foods GROUP BY type_id;

SELECT type_id, COUNT(*) FROM foods GROUP BY type_id;

SELECT type_id, COUNT(*) FROM foods 
GROUP BY type_id HAVING COUNT(*) < 20;

SELECT DISTINCT type_id FROM foods; 

SELECT foods.name, food_types.name 
FROM foods, food_types
WHERE foods.type_id=food_types.id LIMIT 10;

SELECT foods.name, food_types.name FROM foods, food_types
WHERE foods.type_id=food_types.id LIMIT 10;

SELECT f.name, t.name FROM foods f, food_types t
WHERE f.type_id=t.id LIMIT 10;

.m col
.h on
.w 20 17 6 23 6
.e on

SELECT f.name as food, e1.name, e1.season, e2.name, e2.season 
FROM episodes e1, foods_episodes fe1, foods f, 
     episodes e2, foods_episodes fe2
WHERE 
  -- Get foods in season 4
  (e1.id = fe1.episode_id AND e1.season = 4) AND fe1.food_id = f.id
  -- Link foods with all other epsisodes
  AND (fe1.food_id = fe2.food_id) 
  -- Link with their respective episodes and filter out e1's season
  AND (fe2.episode_id = e2.id AND e2.season != e1.season)
ORDER BY f.name;    

SELECT e.name AS Episode, COUNT(f.id) AS Foods 
FROM foods f 
    JOIN foods_episodes fe on f.id=fe.food_id
    JOIN episodes e on fe.episode_id=e.id
GROUP BY e.id
ORDER BY Foods DESC 
LIMIT 10;

SELECT 1 IN (1,2,3);
SELECT 2 IN (3,4,5);
SELECT COUNT(*) FROM foods WHERE type_id IN (1,2);
SELECT COUNT(*) FROM foods WHERE type_id
IN (SELECT id FROM food_types WHERE name='Bakery' OR name='Cereal');

SELECT name, 
(SELECT COUNT(id) FROM foods_episodes WHERE food_id=f.id) count 
FROM foods f ORDER BY count DESC LIMIT 10;

SELECT (SELECT name FROM food_types WHERE id=f.type_id) Type,   
COUNT(type_id) Items, 
COUNT(type_id)*100.0/(SELECT COUNT(*) FROM foods) as Percentage 
FROM foods f GROUP BY type_id ORDER BY Percentage DESC;

SELECT * FROM foods f 
ORDER BY (SELECT COUNT(type_id) 
FROM foods WHERE type_id=f.type_id) DESC;

SELECT f.name, types.name FROM foods f 
INNER JOIN (SELECT * FROM food_types WHERE id=6) types 
ON f.type_id=types.id;

SELECT e.name name, COUNT(fe.food_id) foods FROM episodes e
INNER JOIN foods_episodes fe ON e.id=fe.episode_id
GROUP BY e.id
ORDER BY foods DESC
LIMIT 10;

SELECT e.name, agg.foods FROM episodes e
INNER JOIN
(SELECT fe.episode_id as eid, count(food_id) as foods
   FROM foods_episodes fe
   GROUP BY episode_id ) agg
ON e.id=agg.eid
ORDER BY agg.foods DESC
LIMIT 10;

SELECT e.name, agg.foods FROM episodes e
INNER JOIN
(SELECT fe.episode_id as eid, count(food_id) as foods
   FROM foods_episodes fe
   GROUP BY episode_id
   ORDER BY foods DESC LIMIT 10) agg
ON e.id=agg.eid
ORDER BY agg.foods DESC;

SELECT f.* FROM foods f
INNER JOIN
  (SELECT food_id, count(food_id) as count FROM foods_episodes
     GROUP BY food_id
     ORDER BY count(food_id) DESC LIMIT 10) top_foods
  ON f.id=top_foods.food_id
INTERSECT
SELECT f.* FROM foods f
  INNER JOIN foods_episodes fe ON f.id = fe.food_id
  INNER JOIN episodes e ON fe.episode_id = e.id
  WHERE e.season BETWEEN 3 and 5
ORDER BY f.name;

SELECT f.* FROM foods f
INNER JOIN
  (SELECT food_id, count(food_id) AS count FROM foods_episodes
     GROUP BY food_id
     ORDER BY count(food_id) DESC LIMIT 10) top_foods
  ON f.id=top_foods.food_id
EXCEPT
SELECT f.* FROM foods f
  INNER JOIN foods_episodes fe ON f.id = fe.food_id
  INNER JOIN episodes e ON fe.episode_id = e.id
  WHERE e.season BETWEEN 3 and 5
ORDER BY f.name;

SELECT f.*, top_foods.count FROM foods f
INNER JOIN
  (SELECT food_id, count(food_id) AS count FROM foods_episodes
     GROUP BY food_id
     ORDER BY count(food_id) DESC LIMIT 1) top_foods
  ON f.id=top_foods.food_id
UNION
SELECT f.*, bottom_foods.count FROM foods f
INNER JOIN
  (SELECT food_id, count(food_id) AS count FROM foods_episodes
     GROUP BY food_id
     ORDER BY count(food_id) LIMIT 1) bottom_foods
  ON f.id=bottom_foods.food_id
ORDER BY top_foods.count DESC;

SELECT name || CASE type_id
                 WHEN 7  THEN ' is a drink'
                 WHEN 8  THEN ' is a fruit'
                 WHEN 9  THEN ' is junkfood'
                 WHEN 13 THEN ' is seafood'
                 ELSE NULL
               END description
FROM foods
WHERE description IS NOT NULL
ORDER BY name
LIMIT 10;

SELECT name,(SELECT 
               CASE
                 WHEN count(*) > 4
                   THEN 'Very High'
                 WHEN count(*) = 4
                   THEN 'High'
                 WHEN count(*) IN (2,3)
                   THEN 'Moderate'
                 ELSE 'Low'
               END
             FROM foods_episodes 
             WHERE food_id=f.id) frequency
FROM foods f
WHERE frequency LIKE '%High'

SELECT NULL=NULL;
SELECT NULL OR NULL;
SELECT NULL AND NULL;
SELECT NOT NULL;
SELECT 9E9 - 1E-9*NULL;

SELECT NULLIF(1,1);
SELECT NULLIF(1,2);

CREATE TABLE sales (product_id int, amount real, discount real);
INSERT INTO sales VALUES (1, 10.00, 1.00);
INSERT INTO sales VALUES (2, 10000.00, NULL);
SELECT * FROM sales;

SELECT SUM(amount-discount) FROM sales;

SELECT SUM(amount) from sales WHERE amount-discount > 100.00;

SELECT SUM(amount-COALESCE(discount,0)) FROM sales;

SELECT SUM(amount) from sales 
WHERE amount-COALESCE(discount,0) > 100.00;

INSERT INTO foods (name, type_id) VALUES ('Cinnamon Bobka', 1);

SELECT * FROM foods WHERE name='Cinnamon Bobka';

SELECT MAX(id) from foods;

SELECT last_insert_rowid();

INSERT INTO foods VALUES(NULL, 1, 'Blueberry Bobka');

SELECT * FROM foods WHERE name LIKE '%Bobka';

CREATE TABLE foods(
  id integer primary key,
  type_id integer,
  name text );
CREATE INDEX foods_name_idx on foods (name COLLATE NOCASE);

INSERT INTO foods 
VALUES (NULL, 
       (SELECT id FROM food_types WHERE name='Bakery'), 
       'Blackberry Bobka');
SELECT * FROM foods WHERE name LIKE '%Bobka';

INSERT INTO foods 
SELECT last_insert_rowid()+1, type_id, name FROM foods 
WHERE name='Chocolate Bobka';
SELECT * FROM foods WHERE name LIKE '%Bobka';

CREATE TABLE foods2 (id int, type_id int, name text);
INSERT INTO foods2 SELECT * FROM foods;
SELECT COUNT(*) FROM foods2;

CREATE TABLE foods2 AS SELECT * from foods;
SELECT COUNT(*) FROM list;

CREATE TEMP TABLE list AS
SELECT f.name Food, t.name Name,
       (SELECT COUNT(episode_id) 
        FROM foods_episodes WHERE food_id=f.id) Episodes
FROM foods f, food_types t
WHERE f.type_id=t.id;
SELECT * FROM list;

SELECT MAX(id) from foods;

INSERT INTO foods VALUES (416, 1, 'Chocolate Bobka');

UPDATE foods SET name='CHOCOLATE BOBKA' 
WHERE name='Chocolate Bobka';
SELECT * FROM foods WHERE name LIKE 'CHOCOLATE%';

UPDATE foods SET id=11 where name='CHOCOLATE BOBKA';

CREATE TABLE contacts ( id INTEGER PRIMARY KEY,
                        name TEXT NOT NULL COLLATE NOCASE,
                        phone TEXT NOT NULL DEFAULT 'UNKNOWN',
                        UNIQUE (name,phone) );

INSERT INTO contacts (name,phone) VALUES ('Jerry','UNKNOWN');

INSERT INTO contacts (name) VALUES ('Jerry');

INSERT INTO contacts (name,phone) VALUES ('Jerry', '555-1212');

SELECT * FROM contacts;

SELECT ROWID, OID,_ROWID_,id, name, phone FROM CONTACTS;
CREATE TABLE maxed_out(id INTEGER PRIMARY KEY AUTOINCREMENT, x text);
INSERT INTO maxed_out VALUES (9223372036854775807, 'last one');
SELECT * FROM sqlite_sequence;
INSERT INTO maxed_out VALUES (NULL, 'wont work');

DROP TABLE maxed_out;
CREATE TABLE maxed_out(id INTEGER PRIMARY KEY AUTOINCREMENT, x text);
INSERT INTO maxed_out values(10, 'works');
SELECT * FROM sqlite_sequence;

INSERT INTO maxed_out values(9, 'works');
SELECT * FROM sqlite_sequence;

INSERT INTO maxed_out VALUES (9, 'fails');
PRIMARY KEY must be unique

INSERT INTO maxed_out VALUES (NULL, 'should be 11');
SELECT * FROM maxed_out;
SELECT * FROM sqlite_sequence;

CREATE TABLE pkey(x text, y text, PRIMARY KEY(x,y));
INSERT INTO pkey VALUES ('x','y');
INSERT INTO pkey VALUES ('x','x');
SELECT ROWID, x, y FROM pkey;

INSERT INTO pkey VALUES ('x','x');

INSERT INTO contacts (name) VALUES ('Jerry');
SELECT * FROM contacts;

CREATE TABLE times ( id int,
  time NOT NULL DEFAULT CURRENT_DATE
  time NOT NULL DEFAULT CURRENT_TIME,
  time NOT NULL DEFAULT CURRENT_TIMESTAMP );
INSERT INTO times(1);
INSERT INTO times(2);
SELECT * FROMS times;

INSERT INTO contacts (phone) VALUES ('555-1212');

CREATE TABLE contacts ( id INTEGER PRIMARY KEY,
                        name TEXT NOT NULL COLLATE NOCASE,
                        phone TEXT NOT NULL DEFAULT 'UNKNOWN',
                        UNIQUE (name,phone), 
                        CHECK(LENGTH(phone)>=7) );

CREATE TABLE foo( x integer, 
                  y integer CHECK(y>x),
                  z integer CHECK(z>ABS(y)) );

INSERT into foo values (-2, -1, 2);
INSERT into foo values (-2, -1, 1);

UPDATE foo SET y=-3 WHERE x=-3;

INSERT INTO contacts (name,phone) VALUES ('JERRY','555-1212');

select typeof(3.14), typeof('3.14'), 
       typeof(314), typeof(x'3142'), typeof(NULL);

DROP TABLE domain;
CREATE TABLE domain(x);
INSERT INTO domain VALUES (3.142);
INSERT INTO domain VALUES ('3.142');
INSERT INTO domain VALUES (3142);
INSERT INTO domain VALUES (x'3142');
INSERT INTO domain VALUES (NULL);
SELECT ROWID, x, typeof(x) FROM domain;

SELECT 3 < 3.142, 3.142 < '3.142', '3.142' < x'3000', 
       x'3000' < x'3001';

CREATE TABLE foo( x integer, 
                  y text, 
                  z real );

INSERT INTO foo VALUES ('1', '1', '1');
CREATE TABLE foo(x, y, z);
INSERT INTO foo VALUES ('1', '1', '1');
INSERT INTO foo VALUES (1, 1.0, x'10');

CREATE TABLE domain (x int, y varchar(2));
INSERT INTO domain VALUES ('pi', 3.14);
SELECT * FROM domain;

CREATE TABLE domain(i int, n numeric, t text, b blob);
INSERT INTO domain VALUES (3.142,3.142,3.142,3.142);
INSERT INTO domain VALUES ('3.142','3.142','3.142','3.142');
INSERT INTO domain VALUES (3142,3142,3142,3142);
INSERT INTO domain VALUES (x'3142',x'3142',x'3142',x'3142');
INSERT INTO domain VALUES (null,null,null,null);
SELECT ROWID,typeof(i),typeof(n),typeof(t),typeof(b) FROM domain;

SELECT ROWID, b, typeof(b) FROM domain ORDER BY b;

SELECT ROWID, b, typeof(b), b<1000 FROM domain ORDER BY b;

select ROWID,b,typeof(i),i>'2.9' from domain ORDER BY b;

SELECT ROWID,b,typeof(i),i>'text' FROM domain ORDER BY b;

CREATE TABLE rule2(a int, b text);
insert into rule2 values(2,'1');
insert into rule2 values(2,'text');
select a, typeof(a),b,typeof(b), a>b from rule2;

SELECT typeof(3.14), typeof(CAST(3.14 as TEXT));
select typeof(3.14) = 'text';
select typeof(3.14) = 'integer';
select typeof(3.14) = 'real';
select typeof(3) = 'integer';
select typeof('3') = 'text';
create table domain (x integer CHECK(typeof(x)='integer'));
INSERT INTO domain VALUES('1');
INSERT INTO domain VALUES(1.1);
INSERT INTO domain VALUES(1);
select x, typeof(x) from domain;

BEGIN;
DELETE FROM foods;
ROLLBACK;
SELECT COUNT(*) FROM foods;

UPDATE foods SET id=800-id;

CREATE TABLE test AS SELECT * FROM foods;
CREATE UNIQUE INDEX test_idx on test(id);
ALTER TABLE test ADD COLUMN modified text NOT NULL DEFAULT 'no';
SELECT COUNT(*) FROM test WHERE modified='no';

UPDATE OR FAIL test SET id=800-id, modified='yes';
SELECT COUNT(*) FROM test WHERE modified='yes';
DROP TABLE test;

CREATE TEMP TABLE cast(name text UNIQUE ON CONFLICT ROLLBACK);
INSERT INTO cast VALUES ('Jerry');
INSERT INTO cast VALUES ('Elaine');
INSERT INTO cast VALUES ('Kramer');

BEGIN;
INSERT INTO cast VALUES('Jerry');
COMMIT;

BEGIN;
INSERT OR REPLACE INTO cast VALUES('Jerry');
COMMIT;

SELECT f.name, ft.name, e.name
FROM foods f
INNER JOIN food_types ft on f.type_id=ft.id
INNER JOIN foods_episodes fe ON f.id=fe.food_id
INNER JOIN episodes e ON fe.episode_id=e.id;

CREATE VIEW details AS
SELECT f.name AS fd, ft.name AS tp, e.name AS ep, e.season as ssn
FROM foods f
INNER JOIN food_types ft on f.type_id=ft.id
INNER JOIN foods_episodes fe ON f.id=fe.food_id
INNER JOIN episodes e ON fe.episode_id=e.id;

SELECT fd as Food, ep as Episode 
FROM details WHERE ssn=7 AND tp like 'Drinks';

CREATE TABLE foo(a text, b text);
CREATE UNIQUE INDEX foo_idx on foo(a,b);
INSERT INTO foo VALUES ('unique', 'value');
INSERT INTO foo VALUES ('unique', 'value2');
INSERT INTO foo VALUES ('unique', 'value');

CREATE TABLE foo (a,b,c,d);
CREATE INDEX foo_idx on foo (a,b,c,d);
SELECT * FROM foo WHERE a=1 AND b=2 AND d=3
SELECT * FROM foo WHERE a>1 AND b=2 AND c=3 AND d=4
SELECT * FROM foo WHERE a=1 AND b>2 AND c=3 AND d=4

SELECT CAST(strftime('%s','now') as INTEGER)-CAST(time.start as INTEGER) time, 
        ft1.id, ft2.id, ft3.id, ft4.id
FROM food_types ft1, food_types ft2, food_types ft3, food_types ft4, 
     (SELECT strftime('%s','now') start) time;

.h on
.m col
.w 50
.echo on
CREATE TEMP TABLE log(x);

CREATE TEMP TRIGGER foods_update_log UPDATE of name ON foods
BEGIN
  INSERT INTO log VALUES('updated foods: new name=' || NEW.name);
END;

BEGIN;
UPDATE foods set name='JUJYFRUIT' where name='JujyFruit';
SELECT * FROM log;
ROLLBACK;

CREATE VIEW foods_view AS 
  SELECT f.id fid, f.name fname, t.id tid, t.name tname 
  FROM foods f, food_types t;

CREATE TRIGGER on_update_foods_view
INSTEAD OF UPDATE ON foods_view
FOR EACH ROW
BEGIN
   UPDATE foods SET name=NEW.fname WHERE id=NEW.fid;
   UPDATE food_types SET name=NEW.tname WHERE id=NEW.tid;
END;

-- Update the view within a transaction
BEGIN;
UPDATE foods_view SET fname='Whataburger', tname='Fast Food' WHERE fid=413;
-- Now view the underlying rows in the base tables:
SELECT * FROM foods f, food_types t WHERE f.type_id=t.id AND f.id=413;
-- Roll it back
ROLLBACK;
-- Now look at the original record:
SELECT * FROM foods f, food_types t WHERE f.type_id=t.id AND f.id=413;

CREATE TRIGGER foods_insert_trg
BEFORE INSERT ON foods
BEGIN
  SELECT CASE
     WHEN (SELECT id FROM food_types WHERE id=NEW.type_id) IS NULL
     THEN RAISE( ABORT,
     'Foreign Key Violation: foods.type_id is not in food_types.id')
  END;
END;

INSERT INTO foods VALUES (NULL, 20, 'Blue Bell Ice Cream');

CREATE TRIGGER foods_update_trg
BEFORE UPDATE OF type_id ON foods
BEGIN
  SELECT CASE
     WHEN (SELECT id FROM food_types WHERE id=NEW.type_id) IS NULL
     THEN RAISE(ABORT, 
    'Foreign Key Violation: foods.type_id is not in food_types.id')
  END;
END;

UPDATE foods SET type_id=20 WHERE name='Chocolate Bobka';

CREATE TRIGGER foods_delete_trg
BEFORE DELETE ON food_types
BEGIN
  SELECT CASE
     WHEN (SELECT COUNT(type_id) FROM foods WHERE type_id=OLD.id) > 0
     THEN RAISE(ABORT, 
     'Foreign Key Violation: foods rows reference row to be deleted.')
  END;
END;

DELETE FROM food_types WHERE name='Bakery';

BEGIN;
DELETE FROM foods WHERE type_id=1;
DELETE FROM food_types WHERE name='Bakery';
ROLLBACK;

ATTACH DATABASE '/tmp/db' as db2;
SELECT * FROM db2.foo;

SELECT * FROM main.foods LIMIT 2;

CREATE TEMP TABLE foo AS SELECT * FROM food_types LIMIT 3;
SELECT * FROM temp.foo;

PRAGMA cache_size;
PRAGMA cache_size=10000;
PRAGMA cache_size;
PRAGMA database_list;
CREATE INDEX foods_name_type_idx ON foods(name,type_id);
PRAGMA index_info(foods_name_type_idx);
PRAGMA index_list(foods);
PRAGMA table_info(foods);

SELECT type, name, rootpage FROM sqlite_master;
SELECT sql FROM sqlite_master WHERE name='foods_update_trg';
EXPLAIN SELECT * FROM foods;



