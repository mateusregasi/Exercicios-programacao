-- https://judge.beecrowd.com/pt/problems/view/2602

-- Foi feita uma seleção e uma projeção. 
-- Projetou-se a coluna name da tabela customers.
-- Selecionou-se os registros cujo estado seja 'RS'.


select 
    name 
from customers
where state like 'RS';