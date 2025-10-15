-- https://judge.beecrowd.com/pt/problems/view/2607

-- Foi feito uma projeção em cima de uma ordenação.
-- Foram projetados todas as cidades da tabela providers.
-- As cidades foram ordenadas em ordem alfabética (obs: poderia omitir o asc, pois a ordenação padrão já é ascendente).
-- O distinct elimina repetições dentro da seleção.

select distinct
    city
from providers
order by city asc;