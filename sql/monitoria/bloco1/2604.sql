-- https://judge.beecrowd.com/pt/problems/view/2604

-- Foi feita uma seleção e uma projeção.
-- Selecionou-se os registros da tabela products que tivessem um registro que atendesse a seguinte condição: o preço tem que ser menor que 10 ou o preço tem que ser maior que 100.
-- Projetou-se as colunas id e name.

select
    id, 
    name
from products
where price > 100 or price < 10;