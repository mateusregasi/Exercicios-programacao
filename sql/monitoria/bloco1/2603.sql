-- https://judge.beecrowd.com/pt/problems/view/2603

-- Foi feita uma seleção e uma projeção.
-- Selecionou-se os registros da tabela customers cuja cidade fosse 'Porto Alegre'.
-- Projetou-se as colunas name e street.

select
    name,
    street
from customers
where city like 'Porto Alegre';