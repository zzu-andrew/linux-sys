
.h on
.m c

select e.name as Episode, f.name Name, ft.name Type
from 
  foods f, food_types ft, foods_episodes fe, episodes e
where
  e.name like 'The Soup'
  and f.type_id = ft.id
  and fe.food_id = f.id and fe.episode_id = e.id
  order by f.type_id;
