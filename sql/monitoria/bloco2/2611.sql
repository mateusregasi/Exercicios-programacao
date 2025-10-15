-- https://judge.beecrowd.com/pt/problems/view/2611

-- Foi aplicado uma função de projeção sobre uma seleção utilizando seleções aninhadas.
-- Foi selecionado os ids dos gêneros na tabela genres quais a descrição iniciava com 'Action'.
-- Foi selecionado os filmes da tabela movies quais tinham id_genre dentro dos gêneros achados na seleção anterior.
-- Dado esse resultado, foram projetados id e name.

select 
    id, name
from movies
where id_genres in (select 
                        id 
                    from genres 
                    where description like 'Action');