-- https://judge.beecrowd.com/pt/problems/view/2993

CREATE TABLE value_table (
    amount integer
);

insert into
value_table (amount)
values
(4),(6),(7),(1),(1),(2),(3),(2),(3),(1),(5),(6),(1),(7),(8),(9),(10),(11),(12),(4),(5),(5),(3),(6),(2),(2),(1);

select 
    amount as most_frequent_value 
from 
    value_table 
group by amount 
order by count(amount) desc 
limit 1;

DROP TABLE value_table;