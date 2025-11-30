-- https://judge.beecrowd.com/pt/problems/view/2743

CREATE TABLE people(
	id INTEGER PRIMARY KEY,
	name varchar(255)
);


INSERT INTO people(id, name)
VALUES 
      (1, 'Karen'),
      (2, 'Manuel'),
      (3, 'Ygor'),
      (4, 'Valentine'),
      (5, 'Jo');

select 
    name,
    CHARACTER_LENGTH(name)
from people 
order by CHARACTER_LENGTH(name) desc; 

DROP TABLE people;