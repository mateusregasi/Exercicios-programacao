------------------------ Banco de dados ------------------------

drop schema biblio cascade;

create SCHEMA biblio;
CREATE TABLE biblio.Autor (
    pk SERIAL,
    nome TEXT NOT NULL,
    constraint pk_autor PRIMARY KEY(pk)
);
CREATE TABLE biblio.Genero (
    pk SERIAL,
    nome TEXT NOT NULL,
    constraint pk_genero PRIMARY KEY(pk)
);
CREATE TABLE biblio.Cliente (
    pk SERIAL,
    nome TEXT NOT NULL,
    constraint pk_cliente PRIMARY KEY(pk)
);
CREATE TABLE biblio.Livro(
    pk SERIAL,
    isbn TEXT not null,
    titulo TEXT NOT NULL,
    num_paginas INTEGER NOT NULL,
    pk_genero int,
    constraint pk_livro PRIMARY KEY(pk),
    constraint fk_genero FOREIGN KEY(pk_genero) REFERENCES biblio.Genero(pk)
);
create table biblio.LivroAutor(
    pk_livro int,
    pk_autor int,
    constraint pk_livro_autor PRIMARY KEY(pk_livro, pk_autor),
    constraint fk_livro FOREIGN KEY(pk_livro) REFERENCES biblio.Livro(pk),
    constraint fk_autor FOREIGN KEY(pk_autor) REFERENCES biblio.Autor(pk)
);
CREATE TABLE biblio.Biblioteca (
    pk SERIAL,
    cidade_estado TEXT NOT NULL,
    constraint pk_biblioteca PRIMARY KEY(pk)
);
CREATE TABLE biblio.CopiaLivro (
    pk SERIAL,
    pk_livro int,
    pk_biblioteca int,
    emprestado BOOLEAN DEFAULT FALSE,
    bloqueado BOOLEAN DEFAULT FALSE,
    constraint pk_copia_livro PRIMARY KEY(pk),
    constraint fk_livro FOREIGN KEY(pk_livro) REFERENCES biblio.Livro(pk),
    constraint fk_biblioteca FOREIGN KEY(pk_biblioteca) REFERENCES biblio.Biblioteca(pk)
);
CREATE TABLE biblio.Emprestimo (
    pk SERIAL,
    pk_cliente INTEGER ,
    pk_copia_livro INTEGER,
    data_retirada DATE NOT NULL,
    data_devolucao DATE,
    data_prazo DATE not null,
    constraint pk_emprestimo PRIMARY KEY(pk),
    constraint fk_cliente FOREIGN KEY(pk_cliente) REFERENCES biblio.Cliente(pk),
    constraint fk_copia_livro FOREIGN KEY(pk_copia_livro) REFERENCES biblio.CopiaLivro(pk)
);
CREATE TABLE biblio.AgendamentoMovimentacao (
    pk SERIAL,
    pk_origem int,
    pk_destino int,
    data_sapka DATE,
    data_entrega DATE,
    entregue BOOLEAN DEFAULT FALSE,
    constraint pk_agendamento_movimentacao PRIMARY KEY(pk),
    constraint fk_origem FOREIGN KEY(pk_origem) REFERENCES biblio.Biblioteca(pk),
    constraint fk_destino FOREIGN KEY(pk_destino) REFERENCES biblio.Biblioteca(pk)
);
CREATE TABLE biblio.CopiaMovimentacao (
    pk_copia_livro int,
    pk_movimentacao int,
    constraint pk_copia_movimentacao PRIMARY KEY(pk_copia_livro, pk_movimentacao),
    constraint fk_copia_livro FOREIGN KEY(pk_copia_livro) REFERENCES biblio.CopiaLivro(pk),
    constraint fk_movimentacao FOREIGN KEY(pk_movimentacao) REFERENCES biblio.AgendamentoMovimentacao(pk)
);

------------------------ Inserindo valores de teste ------------------------
INSERT INTO biblio.Autor (nome) VALUES ('Machado de Assis'),('Clarice Lispector'),('George Orwell'),('J.K. Rowling'),('J.R.R. Tolkien'),('Gabriel García Márquez'),('Franz Kafka'),('Virginia Woolf'),('Cecília Meireles');
INSERT INTO biblio.Genero (nome) VALUES ('Romance'),('Ficção Científica'),('Fantasia'),('Drama'),('Poesia'),('Suspense'),('Biografia');
INSERT INTO biblio.Cliente (nome) VALUES ('João da Silva'),('Maria Oliveira'),('Carlos Souza'),('Ana Beatriz Ramos'),('Felipe Duarte'),('Lucas Martins'),('Patrícia Ferreira'),('Renata Costa');
INSERT INTO biblio.Livro (isbn, titulo, num_paginas, pk_genero) VALUES 
    ('978-85-01-00001-1', 'Dom Casmurro', 256, 1),
    ('978-85-01-00002-8', 'A Hora da Estrela', 96, 4),
    ('978-85-01-00003-5', '1984', 328, 2),
    ('978-85-01-00004-2', 'Harry Potter e a Pedra Filosofal', 223, 3),
    ('978-85-01-00005-9', 'O Senhor dos Anéis', 1178, 3),
    ('978-85-01-00006-6', 'Cem Anos de Solidão', 417, 1),
    ('978-85-01-00007-3', 'A Metamorfose', 74, 2),
    ('978-85-01-00008-0', 'Mrs. Dalloway', 224, 4),
    ('978-85-01-00009-7', 'Romanceiro da Inconfidência', 180, 4),
    ('978-85-01-00010-3', 'Assassinato no Expresso do Oriente', 256, 6),
    ('978-85-01-00011-0', 'A Vida de Steve Jobs', 656, 7);
INSERT INTO biblio.LivroAutor (pk_livro, pk_autor) VALUES (1, 1),(2, 2),(3, 3),(4, 4),(5, 5),(6, 6),(7, 7),(8, 8),(9, 9),(10, 3),(11, 2);
INSERT INTO biblio.Biblioteca (cidade_estado) VALUES ('Niterói/RJ'),('Itapevi/SP'),('Ipatinga/MG');
INSERT INTO biblio.CopiaLivro (pk_livro, pk_biblioteca, emprestado, bloqueado) VALUES 
    (1, 1, FALSE, FALSE),
    (2, 1, FALSE, FALSE),
    (3, 2, TRUE, FALSE),
    (4, 3, FALSE, TRUE),
    (4, 2, FALSE, FALSE),
    (5, 1, FALSE, FALSE),
    (6, 2, FALSE, FALSE),
    (7, 2, TRUE, FALSE),
    (8, 3, FALSE, FALSE),
    (9, 1, FALSE, FALSE),
    (10, 3, FALSE, TRUE),
    (11, 2, FALSE, FALSE);
INSERT INTO biblio.Emprestimo (pk_cliente, pk_copia_livro, data_retirada, data_devolucao, data_prazo) VALUES 
    (1, 3, '2025-04-01', '2025-04-10', '2025-04-08'),
    (2, 1, '2025-04-05', '2025-04-12', '2025-04-10'),
    (3, 7, '2025-04-07', '2025-04-15', '2025-04-12'),
    (4, 8, '2025-04-09', '2025-04-19', '2025-04-14'),
    (5, 9, '2025-04-12', '2025-04-20', '2025-04-18'),
    (1, 4, '2025-04-17', '2025-04-17', '2025-04-24'),
    (2, 5, '2025-04-18', NULL, '2025-04-25'),
    (3, 6, '2025-04-15', NULL, '2025-04-22'),
    (1, 2, '2024-11-01', '2024-11-08', '2024-11-10'),
    (1, 3, '2024-12-05', '2024-12-20', '2024-12-17'),
    (1, 5, '2025-01-10', '2025-01-15', '2025-01-15'),
    (1, 6, '2025-02-01', '2025-02-20', '2025-02-15'),
    (1, 10, '2025-04-10', NULL, '2025-04-17'),
    (2, 4, '2025-03-01', '2025-03-10', '2025-03-08'),
    (3, 5, '2025-03-05', '2025-03-15', '2025-03-12'),
    (4, 6, '2025-03-07', '2025-03-17', '2025-03-14'),
    (5, 7, '2025-03-09', '2025-03-19', '2025-03-16'),
    (6, 8, '2025-03-11', '2025-03-21', '2025-03-18'),
    (7, 9, '2025-03-13', '2025-03-23', '2025-03-20'),
    (8, 10, '2025-03-15', '2025-03-25', '2025-03-22'),
    (1, 11, '2025-03-17', '2025-03-27', '2025-03-24'),
    (2, 1, '2025-03-19', '2025-03-29', '2025-03-26'),
    (3, 2, '2025-03-21', '2025-03-31', '2025-03-28'),
    (4, 3, '2025-03-23', '2025-04-02', '2025-03-30'),
    (5, 4, '2025-03-25', '2025-04-04', '2025-04-01'),
    (6, 5, '2025-03-27', '2025-04-06', '2025-04-03'),
    (7, 6, '2025-03-29', '2025-04-08', '2025-04-05'),
    (8, 7, '2025-03-31', '2025-04-10', '2025-04-07'),
    (1, 8, '2025-04-02', '2025-04-12', '2025-04-09'),
    (2, 9, '2025-04-04', '2025-04-14', '2025-04-11'),
    (3, 10, '2025-04-06', '2025-04-16', '2025-04-13'),
    (4, 11, '2025-04-08', '2025-04-18', '2025-04-15'),
    (5, 1, '2025-04-10', '2025-04-20', '2025-04-17'),
    (6, 2, '2025-04-12', '2025-04-22', '2025-04-19'),
    (7, 3, '2025-04-14', '2025-04-24', '2025-04-21'),
    (8, 4, '2025-04-16', '2025-04-26', '2025-04-23'),
    (1, 5, '2025-04-18', '2025-04-28', '2025-04-25'),
    (2, 6, '2025-04-20', '2025-04-30', '2025-04-27'),
    (3, 7, '2025-04-22', '2025-05-02', '2025-04-29'),
    (4, 8, '2025-04-24', '2025-05-04', '2025-05-01'),
    (5, 9, '2025-04-26', '2025-05-06', '2025-05-03'),
    (6, 10, '2025-04-28', '2025-05-08', '2025-05-05'),
    (7, 11, '2025-04-30', '2025-05-10', '2025-05-07'),
    (8, 1, '2025-05-02', '2025-05-12', '2025-05-09'),
    (1, 2, '2025-05-04', '2025-05-14', '2025-05-11'),
    (2, 3, '2025-05-06', '2025-05-16', '2025-05-13'),
    (3, 4, '2025-05-08', '2025-05-18', '2025-05-15'),
    (4, 5, '2025-05-10', '2025-05-20', '2025-05-17'),
    (5, 6, '2025-05-12', '2025-05-22', '2025-05-19'),
    (6, 7, '2025-05-14', '2025-05-24', '2025-05-21'),
    (7, 8, '2025-05-16', '2025-05-26', '2025-05-23'),
    (8, 9, '2025-05-18', '2025-05-28', '2025-05-25');
INSERT INTO biblio.AgendamentoMovimentacao (pk_origem, pk_destino, data_sapka, data_entrega, entregue) VALUES 
    (1, 2, '2025-04-15', '2025-04-18', FALSE),
    (2, 3, '2025-04-10', '2025-04-14', TRUE);
INSERT INTO biblio.CopiaMovimentacao (pk_copia_livro, pk_movimentacao) VALUES (2, 1),(5, 2);


------------------------ Questão nº1 ------------------------
drop function if exists biblio.escalonamento;
CREATE OR REPLACE FUNCTION biblio.escalonamento(
    A int[],
    y double precision[]
) RETURNS double precision[] AS $$
DECLARE
    n int := array_length(y,1);
    v int;
    k INTEGER;
    factor DOUBLE PRECISION;
    x DOUBLE PRECISION[] := ARRAY[]::double precision[];
    A_ext double precision[];
    linha double precision[];
BEGIN

    -- Cria matriz estendida [A | y]
    v := 0;
    for i in 1..n loop
        for j in 1..n loop
                A_ext := array_append(A_ext, A[(i-1)*n+j]);
            if j = n then
                A_ext := array_append(A_ext, y[i]);
            end if;
        end loop;
    end loop;

    -- Escalonamento (eliminação de Gauss)
    FOR i IN 1..n LOOP

        IF a_ext[(i-1)*(n+1)+i] = 0 THEN
            RAISE EXCEPTION 'Pivô zero encontrado na linha %, impossível continuar sem pivotamento', i;
        END IF;

        -- Zerar elementos abaixo do pivô
        FOR j IN i+1..n LOOP
            factor := a_ext[(j-1)*(n+1)+i] / a_ext[(i-1)*(n+1)+i];
            FOR k IN i..n+1 LOOP
                a_ext[(j-1)*(n+1)+k] := a_ext[(j-1)*(n+1)+k] - factor * a_ext[(i-1)*(n+1)+k];
            END LOOP;
        END LOOP;
    END LOOP;

    -- Substituição regressiva
    x := array_fill(0.0, ARRAY[n]);
    FOR i IN REVERSE n..1 LOOP
        x[i] := a_ext[(i)*(n+1)];
        FOR j IN i+1..n LOOP
            x[i] := x[i] - a_ext[(i-1)*(n+1)+j] * x[j];
        END LOOP;
        x[i] := x[i] / a_ext[(i-1)*(n+1)+i];
    END LOOP;

    RETURN x;
END;
$$ LANGUAGE plpgsql;
drop function if exists biblio.prever_entrega;
create or replace function biblio.prever_entrega(nome_usuario text, num_paginas int, grau_polinomio int) returns double precision as $$
declare
    mat int[];
    v double precision[];
    y double precision[];
    x double precision[] = '{}';
    aux double precision;
    res double precision;
    n int default 0;
    reg record;
begin
    -- Percorre todos os livros lidos pelo cliente e adiciona em um vetor
    for reg in select
        (emp.data_devolucao - emp.data_retirada + 1) / liv.num_paginas::float as dias
    from biblio.Cliente as cli 
        join biblio.Emprestimo as emp on cli.pk = emp.pk_cliente
        join biblio.Livro as liv on emp.pk_copia_livro = liv.pk
    where emp.data_devolucao is not null and cli.nome = nome_usuario
    order by emp.data_retirada desc loop
        v := array_append(v, reg.dias);
        n := n + 1;

        -- Sai do loop quando atinge o número de pontos necessários
        exit when n = grau_polinomio;
    end loop;

    -- Se a quantidade de elementos for menor do que o necessário pelo polinômio passado dá erro
    if n < grau_polinomio then
        raise exception 'Grau do polinômio grande demais para base de dados';
    end if;

    -- Monta o vetor y
    for i in 1..grau_polinomio loop
        aux := 0;
        for j in 1..grau_polinomio loop
            aux := aux + v[j] * power(j, i-1);
        end loop;
        y := array_append(y, aux);
    end loop;

    -- Monta a matriz A
    for i in 1..grau_polinomio loop
        for j in 1..grau_polinomio loop
            aux := 0;
            for k in 1..grau_polinomio loop
                aux := aux + power(k, i+j-2);
            end loop;
            mat := array_append(mat, aux);
        end loop;
    end loop;

    -- Executa o escalonamento
    x := biblio.escalonamento(mat, y);

    -- Retorna o resultado
    res := 0;
    for i in 1..grau_polinomio loop
        res := res + power(n+1, i-1) * x[i];
    end loop;
    res := res * num_paginas;

    if res < 0 then 
        return 0;
    else 
        return res;
    end if;
end
$$ language plpgsql;

select biblio.prever_entrega('João da Silva', 100, 3);
select biblio.prever_entrega('Maria Oliveira', 100, 3);
select biblio.prever_entrega('Ana Beatriz Ramos', 100, 3);
select biblio.escalonamento(array[1,2,3,-5], array[5,4]);
select * from biblio.Cliente;

-- Retorna a função com um casting para inteiro


------------------------ Questão nº2 ------------------------
------------------------ Questão nº3 ------------------------
------------------------ Questão nº4 ------------------------
drop function biblio.treinar_regressao_logistica_cliente;
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