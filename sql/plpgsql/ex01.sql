-- 1) Escreva uma função em PL/pgSQL para criar uma tabela com uma quantidade N de números aleatórios entre 0 e 99, onde N é um valor informado como parâmetro.
-- 2) Escreva uma função em PL/pgSQL para calcular um histograma dos números gerados no item anterior.
-- Obs. 1: Um histograma é uma tabela (matriz) onde a primeira coluna contém os números criados no item 1) e a segunda coluna é a frequência relativa de cada número.
-- Obs. 2: Frequência relativa de um número n (freq_rel(n)) é a quantidade percentual de vezes que um número foi gerado dentre os N números gerados, isso é, por exemplo, freq_rel(9) = quantidade de 9s gerados / N.

DROP SCHEMA IF EXISTS mateusregasi CASCADE;
CREATE SCHEMA mateusregasi;

DROP TABLE IF EXISTS mateusregasi.Numeros;
CREATE TABLE mateusregasi.Numeros(
    num INTEGER
);

DROP FUNCTION IF EXISTS mateusregasi.random_numbers;
    CREATE OR REPLACE FUNCTION mateusregasi.random_numbers(n INTEGER) RETURNS TABLE (num INTEGER) AS $$
BEGIN
    FOR i IN 1 .. n LOOP
        INSERT INTO mateusregasi.Numeros VALUES ((random() * 100)::INTEGER);
    END LOOP;

    RETURN QUERY SELECT * FROM mateusregasi.Numeros;
END;
$$ LANGUAGE plpgsql;

DROP FUNCTION IF EXISTS mateusregasi.freq_rel;
CREATE OR REPLACE FUNCTION mateusregasi.freq_rel() RETURNS TABLE(frequencia FLOAT, numero INTEGER) AS $$
DECLARE
    n INTEGER;
BEGIN
    SELECT COUNT(*) INTO n FROM mateusregasi.Numeros;
    RETURN QUERY SELECT count(*)::FLOAT / n AS frequencia, num FROM mateusregasi.Numeros GROUP BY mateusregasi.Numeros.num;
END;
$$ LANGUAGE plpgsql;


SELECT mateusregasi.random_numbers(10000);
SELECT * from mateusregasi.freq_rel();
SELECT ((count(*) / 10)::FLOAT, num) FROM mateusregasi.Numeros GROUP BY num;