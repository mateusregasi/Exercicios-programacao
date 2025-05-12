------------------------ Questão nº2 ------------------------
-- Faça uma função que analisa os padrões de empréstimo para 
-- identificar o maior período para cada livro em que X% das 
-- cópias desses estão sendo emprestadas simultaneamente e 
-- retornando ordenadamente do maior período ao menor período.

drop function if exists biblio.livros_maiores_janelas_ocupacao;
CREATE OR REPLACE FUNCTION biblio.livros_maiores_janelas_ocupacao(
    percentual NUMERIC  -- ex: 0.8 para 80%
)
RETURNS TABLE (
    title TEXT,
    janela INT,
    total_copias INT,
    emprestadas INT
) AS $$
BEGIN
    RETURN QUERY
    WITH emprestimos_raw AS (
        SELECT 
            l.pk AS pk_livro,
            l.titulo,
            cl.pk AS pk_copia_livro,
            e.data_retirada,
            COALESCE(e.data_devolucao, CURRENT_DATE + 1) AS data_devolucao
        FROM biblio.Livro l
        JOIN biblio.CopiaLivro cl ON cl.pk_livro = l.pk
        LEFT JOIN biblio.Emprestimo e ON e.pk_copia_livro = cl.pk
    ),
    total_copias_por_livro AS (
        SELECT pk_livro, MAX(titulo) AS titulo, COUNT(DISTINCT pk_copia_livro) AS total
        FROM emprestimos_raw
        GROUP BY pk_livro
    ),
    eventos AS (
        SELECT 
            e.pk_livro,
            e.titulo,
            tr.total,
            e.data_retirada AS data_evento,
            1 AS delta
        FROM emprestimos_raw e
        JOIN total_copias_por_livro tr ON e.pk_livro = tr.pk_livro
        UNION ALL
        SELECT 
            e.pk_livro,
            e.titulo,
            tr.total,
            e.data_devolucao AS data_evento,
            -1 AS delta
        FROM emprestimos_raw e
        JOIN total_copias_por_livro tr ON e.pk_livro = tr.pk_livro
    ),
    eventos_ordenados AS (
        SELECT 
            pk_livro,
            titulo,
            total,
            data_evento,
            delta,
            SUM(delta) OVER (PARTITION BY pk_livro ORDER BY data_evento, delta DESC) AS emprestadas_atuais
        FROM eventos
    ),
    intervalos_ocupados AS (
        SELECT 
            pk_livro,
            titulo,
            total,
            data_evento AS inicio,
            LEAD(data_evento) OVER (PARTITION BY pk_livro ORDER BY data_evento, delta DESC) AS fim,
            emprestadas_atuais
        FROM eventos_ordenados
    ),
    janelas_validas AS (
        SELECT 
            pk_livro,
            titulo,
            total,
            inicio,
            fim,
            emprestadas_atuais,
            (fim - inicio) AS duracao
        FROM intervalos_ocupados
        WHERE fim IS NOT NULL
          AND emprestadas_atuais >= CEIL(total * percentual)::INT
    ),
    janela_maxima_por_livro AS (
        SELECT 
            pk_livro,
            MAX(duracao) AS dias_janela,
            MIN(emprestadas_atuais) AS copias_utilizadas
        FROM janelas_validas
        GROUP BY pk_livro
    )
    SELECT 
        tc.titulo,
        COALESCE(jmp.dias_janela, 0)::INT AS janela,
        tc.total::INT AS total_copias,
        COALESCE(jmp.copias_utilizadas, 0)::INT AS emprestadas
    FROM total_copias_por_livro tc
    LEFT JOIN janela_maxima_por_livro jmp ON jmp.pk_livro = tc.pk_livro
    ORDER BY janela DESC, copias_utilizadas DESC;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM biblio.livros_maiores_janelas_ocupacao(0.8);