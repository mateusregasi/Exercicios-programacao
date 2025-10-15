-- https://judge.beecrowd.com/pt/problems/view/2609

-- Foi feita uma projeção sobre uma seleção sobre uma junção utilizando funções de agregação sum() para fazer a contagem dos produtos.
-- Foi feita junção entre products e categories pela categoria do produto. Note que foi utilizado um apelido (alias) para tornar a referência à tabela mais curta.
-- Note também que o resultado dessa junção foi agrupado por nome. Como é necessário fazer algo com os atributos que não estão no group by, foi utilizado soma sobre amount, ou seja, foi somado a quantidade de produtos que pertencem àquela categoria.
-- Foi projetado tanto o nome do produto bem como a soma de suas quantidades.

select
    c.name,
    sum(p.amount)
from products as p join categories as c 
    on (p.id_categories = c.id)
group by c.name;