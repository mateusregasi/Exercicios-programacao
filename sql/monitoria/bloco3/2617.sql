-- https://judge.beecrowd.com/pt/problems/view/2617

select 
    pp.name,
    p.name
from providers as p join products as pp
    on (pp.id_providers = p.id)
where p.name = 'Ajax SA';