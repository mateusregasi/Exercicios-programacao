------------------------ Questão nº1 ------------------------
-- Faça a previsão da entrega de um livro de acordo com o 
-- histórico de tempo de leitura (empréstimo e entrega do 
-- livro) de uma pessoa usando regressão, a função deve ter o 
-- seguinte formato:
-- 
--   prever_entrega(nome_usuário, num_páginas, grau_polinômio) 
-- 
-- O retorno da função deve ser um inteiro representando o 
-- número de dias da previsão.



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