-- https://judge.beecrowd.com/pt/problems/view/2741

CREATE TABLE students(
  id INTEGER PRIMARY KEY,
  name VARCHAR(255),
  grade double
);

INSERT INTO students(id, name, grade)
VALUES (1, 'Terry B. Padilla',7.3),
       (2, 'William S. Ray',0.6),
       (3, 'Barbara A. Gongora',5.2),
       (4, 'Julie B. Manzer', 6.7),
       (5, 'Teresa J. Axtell', 4.6),
       (6, 'Ben M. Dantzler', 9.6);

select
    concat('Approved: ', name) as name,
    grade
from 
    students
where grade >= 7
order by grade desc;

DROP TABLE students;