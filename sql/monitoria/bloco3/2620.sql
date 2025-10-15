-- https://judge.beecrowd.com/pt/problems/view/2620

select
    c.name,
    o.id
from customers as c join orders as o
    on (c.id = o.id_customers)
where extract(year from o.orders_date) = 2016 
        and extract(month from o.orders_date) <= 6;