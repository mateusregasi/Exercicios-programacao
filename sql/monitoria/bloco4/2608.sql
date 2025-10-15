-- https://judge.beecrowd.com/pt/problems/view/2608

-- Foi feito uma seleção em cima dos valores mínimo e máximo dos preços na tabela products por meio das funções de agregação max() e min().

select 
    max(price),
    min(price)
from products;