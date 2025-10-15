-- https://judge.beecrowd.com/pt/problems/view/2606

-- Foi feita uma seleção e projeção sobre consultas aninhadas.
-- A consulta da categoria foi feita para retornar a única categoria que iniciem com o nome 'super'.
-- A seleção sobre products foi feita para pegar apenas os registros cuja id_category seja uma das que inicie com super.
-- A projeção sobre products foi feita para pegar apenas o id e o nome, nessa ordem

select
    id as id,
    name as name
from products
where id_categories in (select 
                id 
            from categories 
            where name like 'super%');