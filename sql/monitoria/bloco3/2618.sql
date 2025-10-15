-- https://judge.beecrowd.com/pt/problems/view/2618

select
    p.name,
    pp.name,
    c.name
from products as p join providers as pp
    on (p.id_providers = pp.id)
    join categories as c
        on (p.id_categories = c.id)
where pp.name = 'Sansul SA' and c.name = 'Imported';