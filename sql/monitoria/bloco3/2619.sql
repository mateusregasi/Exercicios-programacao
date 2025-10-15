-- https://judge.beecrowd.com/pt/problems/view/2619

select
    p.name, 
    pp.name,
    p.price
from products as p join providers as pp
    on (p.id_providers = pp.id)
    join categories as c
        on (p.id_categories = c.id)
where p.price > 1000 and c.name = 'Super Luxury';