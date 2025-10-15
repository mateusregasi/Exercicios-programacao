-- https://judge.beecrowd.com/pt/problems/view/2605

-- Foi feita uma operação de junção, uma operação de seleção e uma operação de projeção.
-- Foi feita uma junção entre products e providers.
-- Foi feita uma seleção dos registros de produtos que tivessem categoria de id 6.
-- Foi feita uma projeção dos nomes dos produtos e nomes dos provedores.
-- Obs: note que a ordem importa. 

-- select
--     products.name,
--     providers.name
-- from 
--     products,
--     providers
-- where products.id_providers = providers.id and id_categories = 6;

-- A forma mais usada para seleção está a seguir.

select
    products.name,
    providers.name
from 
    products join providers 
        on (products.id_providers = providers.id)
where id_categories = 6;