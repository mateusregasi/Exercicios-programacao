-- https://judge.beecrowd.com/pt/problems/view/2613

select
    id, name
from movies
where id_prices in (select
                        id
                    from prices
                    where value < 2);