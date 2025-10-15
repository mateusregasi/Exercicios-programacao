-- https://judge.beecrowd.com/pt/problems/view/2616

select 
    id,
    name
from customers
where id not in (select distinct
                    id_customers 
                from locations)
order by id;