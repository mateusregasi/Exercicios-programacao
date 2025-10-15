-- https://judge.beecrowd.com/pt/problems/view/2610

-- Foi feito uma projeção sobre produtos levando em consideração função de arredondamento sobre uma função de agregação.
-- Selecionou-se a média dos preços dos produtos (note que não foi considerada a média ponderada, ou seja, não foi considerado cada produto individual mas a média dos preços nos tipos de produto).
-- Sobre a média foi aplicada uma função de arredondamento, que permitiu 2 casas decimais depois da vírgula.
-- Além disso, foi utilizado apelido na única coluna da tabela.

select
    round(avg(price),2) as price
from products;