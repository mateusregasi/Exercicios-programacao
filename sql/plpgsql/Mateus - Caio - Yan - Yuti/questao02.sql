CREATE OR REPLACE FUNCTION biblio.livros_maiores_janelas_ocupacao(
    percentual NUMERIC  -- ex: 0.8 para 80%
)
RETURNS TABLE (
    title TEXT,
    janela INT,
    total_copias INT,
    emprestadas INT
) AS $$
DECLARE
    rec_livro RECORD;
    rec_evento RECORD;
    v_emprestadas INT := 0;
    v_total INT;
    v_titulo TEXT;
    v_pk_livro INT;
    v_data_anterior DATE;
    v_data_atual DATE;
    v_delta INT;
    v_janela INT;
    v_copias_utilizadas INT;
    v_maior_janela INT;
    v_menor_copias INT;
BEGIN
    -- Loop sobre todos os livros com suas contagens de cópias
    FOR rec_livro IN
        SELECT 
            l.pk AS pk_livro,
            l.titulo,
            COUNT(DISTINCT cl.pk) AS total
        FROM biblio.Livro l
        JOIN biblio.CopiaLivro cl ON cl.pk_livro = l.pk
        GROUP BY l.pk, l.titulo
    LOOP
        v_pk_livro := rec_livro.pk_livro;
        v_titulo := rec_livro.titulo;
        v_total := rec_livro.total;

        v_emprestadas := 0;
        v_maior_janela := 0;
        v_menor_copias := NULL;
        v_data_anterior := NULL;

        -- Percorrer os eventos ordenados (retiradas e devoluções)
        FOR rec_evento IN
            SELECT * FROM (
                SELECT 
                    e.data_retirada AS data_evento,
                    1 AS delta
                FROM biblio.CopiaLivro cl
                JOIN biblio.Emprestimo e ON e.pk_copia_livro = cl.pk
                WHERE cl.pk_livro = v_pk_livro

                UNION ALL

                SELECT 
                    COALESCE(e.data_entrega, CURRENT_DATE + 1) AS data_evento,
                    -1 AS delta
                FROM biblio.CopiaLivro cl
                JOIN biblio.Emprestimo e ON e.pk_copia_livro = cl.pk
                WHERE cl.pk_livro = v_pk_livro
            ) AS eventos
            ORDER BY data_evento, delta DESC
        LOOP
            v_data_atual := rec_evento.data_evento;
            v_delta := rec_evento.delta;

            -- Avalia a janela anterior
            IF v_data_anterior IS NOT NULL THEN
                v_janela := v_data_atual - v_data_anterior;
                IF v_emprestadas >= CEIL(v_total * percentual) THEN
                    IF v_janela > v_maior_janela THEN
                        v_maior_janela := v_janela;
                        v_menor_copias := v_emprestadas;
                    ELSIF v_janela = v_maior_janela AND v_emprestadas < v_menor_copias THEN
                        v_menor_copias := v_emprestadas;
                    END IF;
                END IF;
            END IF;

            -- Atualiza o contador de cópias emprestadas
            v_emprestadas := v_emprestadas + v_delta;
            v_data_anterior := v_data_atual;
        END LOOP;

        -- Retorna o resultado para o livro atual
        title := v_titulo;
        janela := COALESCE(v_maior_janela, 0);
        total_copias := v_total;
        emprestadas := COALESCE(v_menor_copias, 0);
        RETURN NEXT;
    END LOOP;

    RETURN;
END;
$$ LANGUAGE plpgsql;

SELECT * 
FROM biblio.livros_maiores_janelas_ocupacao(0.8)
ORDER BY 
    janela DESC, 
    emprestadas DESC;