-- https://judge.beecrowd.com/pt/problems/view/2622

select
    name as name
from customers
where id in (select
                id_customers
            from legal_person);