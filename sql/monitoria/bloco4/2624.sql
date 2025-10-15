-- https://judge.beecrowd.com/pt/problems/view/2624

select
    count(c.city)
from (select distinct
        city
    from customers) as c;