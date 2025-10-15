-- https://judge.beecrowd.com/pt/problems/view/2614

select
    c.name,
    r.rentals_date
from customers as c join rentals as r
    on (r.id_customers = c.id)
where   extract(month from r.rentals_date) = 9 
        and extract(year from r.rentals_date) = 2016;