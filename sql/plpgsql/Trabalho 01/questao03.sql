------------------------ Questão nº3 ------------------------
-- Faça uma função que estime a chance de um livro ser devolvido 
-- com atraso, considerando o histórico do usuário, o tipo de 
-- livro (gênero) e o número de páginas. A função deve utilizar 
-- classificação binária (por exemplo, regressão logística) e 
-- ter o seguinte formato:
-- 
--     probabilidade_atraso(nome_usuário, gênero, num_páginas)
-- 
-- A saída deve ser um valor entre 0 e 1 representando a chance 
-- estimada de atraso.

drop function if exists biblio.treinar_regressao_logistica_cliente;
CREATE OR REPLACE FUNCTION biblio.treinar_regressao_logistica_cliente(
    cliente_id INTEGER,
    genero_destaque TEXT,
    pag_destaque INTEGER,
    OUT beta0 DOUBLE PRECISION,
    OUT beta1 DOUBLE PRECISION
)
LANGUAGE plpgsql
AS $$
DECLARE
    total_registros INTEGER;
    alpha DOUBLE PRECISION := 0.005;
    peso_base_genero DOUBLE PRECISION := 1.5;
    x_raw DOUBLE PRECISION;
    y INTEGER;
    genero_nome TEXT;
    peso_genero DOUBLE PRECISION;
    peso_paginas DOUBLE PRECISION;
    peso_total DOUBLE PRECISION;
    pred DOUBLE PRECISION;
    error DOUBLE PRECISION;
    counter INTEGER := 0;
BEGIN
    SELECT COUNT(*) INTO total_registros
    FROM biblio.Emprestimo e
    JOIN biblio.CopiaLivro c ON e.pk_copia_livro = c.pk
    JOIN biblio.Livro l ON c.pk_livro = l.pk
    WHERE e.pk_cliente = cliente_id
      AND e.data_devolucao IS NOT NULL;

    beta0 := 0.0;
    beta1 := 0.0;
    IF total_registros = 0 THEN
        RAISE NOTICE 'Nenhum registro encontrado para o cliente %', cliente_id;
    ELSE
      FOR x_raw, y, genero_nome IN
          SELECT l.num_paginas,
                 CASE WHEN e.data_devolucao <= e.data_prazo THEN 1 ELSE 0 END,
                 g.nome
          FROM biblio.Emprestimo e
          JOIN biblio.CopiaLivro c ON e.pk_copia_livro = c.pk
          JOIN biblio.Livro l ON c.pk_livro = l.pk
          JOIN biblio.Genero g ON l.pk_genero = g.pk
          WHERE e.pk_cliente = cliente_id
            AND e.data_devolucao IS NOT NULL
        LOOP
          peso_genero := CASE WHEN genero_nome = genero_destaque THEN peso_base_genero ELSE 1.0 END;
          peso_paginas := (LEAST(pag_destaque, x_raw) / GREATEST(pag_destaque, x_raw)) * 0.5 + 0.5;
          peso_total := peso_genero * peso_paginas;
  
          pred := 1.0 / (1.0 + EXP(-(beta0 + beta1 * peso_paginas)));
          error := y - pred;
          
          IF counter > 0 THEN
            beta0 := (beta0*counter + alpha * peso_genero * error) / counter;
            beta1 := (beta1*counter + alpha * peso_total * error) / counter;
          ELSE
            beta0 := beta0 + alpha * peso_genero * error;
            beta1 := beta1 + alpha * peso_total * error;
          END IF;
          counter := counter +1;
      END LOOP;
    END IF;
END;
$$;


CREATE OR REPLACE FUNCTION biblio.prever_entrega_cliente(
    cliente_id INTEGER,
    genero_destaque TEXT,
    numero_paginas INTEGER
)
RETURNS NUMERIC
LANGUAGE plpgsql
AS $$
DECLARE
    beta0 DOUBLE PRECISION;
    beta1 DOUBLE PRECISION;
    probabilidade DOUBLE PRECISION;
BEGIN
    SELECT * 
INTO beta0, beta1
FROM biblio.treinar_regressao_logistica_cliente(cliente_id, genero_destaque, numero_paginas);

    probabilidade := 1.0 / (1.0 + EXP(-(beta0 + beta1 * numero_paginas)));

    RETURN probabilidade;
END;
$$;

select biblio.prever_entrega_cliente(101, 'Romance', 100);

select * from biblio.genero;
select * from biblio.cliente;