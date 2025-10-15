-- https://judge.beecrowd.com/pt/problems/view/2621

select
    p.name
from products as p join providers as pp
    on (p.id_providers = pp.id)
where 10 <= p.amount and p.amount <= 20 and pp.name like 'P%';