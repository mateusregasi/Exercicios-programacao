DROP SCHEMA IF EXISTS mr CASCADE;
CREATE SCHEMA mr;

drop table if exists mr.Campeonato cascade;
CREATE TABLE mr.Campeonato (
    codigo text NOT NULL,
    nome TEXT NOT NULL,
    ano integer not null,
    CONSTRAINT campeonato_pk PRIMARY KEY(codigo)
);

drop table if exists mr.Time cascade;
CREATE TABLE mr.Time (
    sigla text NOT NULL,
    nome TEXT NOT NULL,
    CONSTRAINT time_pk PRIMARY KEY(sigla)
);

drop table if exists mr.Jogo cascade;
CREATE TABLE mr.Jogo (
    campeonato text not null,
    numero integer NOT NULL,
    time1 text NOT NULL,
    time2 text NOT NULL,
    gols1 integer not null,
    gols2 integer not null,
    data_ date not null,
    CONSTRAINT jogo_pk PRIMARY KEY(campeonato,numero),
    CONSTRAINT jogo_campeonato_fk FOREIGN KEY(campeonato) REFERENCES mr.campeonato(codigo),
    CONSTRAINT jogo_time_fk1 FOREIGN KEY (time1) REFERENCES mr.Time (sigla),
    CONSTRAINT jogo_time_fk2 FOREIGN KEY(time2) REFERENCES mr.Time (sigla)
);

--------------------------------- BASE DE DADOS GERADA COM CHATGPT ---------------------------------

-- Inserir campeonatos
INSERT INTO mr.Campeonato (codigo, nome, ano) VALUES
('BR21', 'Brasileirão Série A', 2021),
('BR22', 'Brasileirão Série A', 2022),
('LIB22', 'Copa Libertadores', 2022);

-- Inserir times
INSERT INTO mr.Time (sigla, nome) VALUES
('FLA', 'Flamengo'),
('PAL', 'Palmeiras'),
('COR', 'Corinthians'),
('INT', 'Internacional'),
('GRE', 'Grêmio'),
('CAM', 'Atlético Mineiro'),
('SAO', 'São Paulo'),
('VAS', 'Vasco'),
('BOT', 'Botafogo'),
('BAH', 'Bahia');

-- Inserir jogos BR21
INSERT INTO mr.Jogo (campeonato, numero, time1, time2, gols1, gols2, data_) VALUES
('BR21', 1, 'FLA', 'PAL', 2, 1, '2021-05-01'),
('BR21', 2, 'COR', 'INT', 1, 0, '2021-05-02'),
('BR21', 3, 'GRE', 'CAM', 0, 0, '2021-05-03'),
('BR21', 4, 'SAO', 'VAS', 3, 2, '2021-05-04'),
('BR21', 5, 'BOT', 'BAH', 1, 1, '2021-05-05'),
('BR21', 6, 'PAL', 'COR', 2, 2, '2021-05-06'),
('BR21', 7, 'INT', 'GRE', 0, 1, '2021-05-07'),
('BR21', 8, 'CAM', 'SAO', 1, 1, '2021-05-08'),
('BR21', 9, 'VAS', 'FLA', 0, 2, '2021-05-09'),
('BR21', 10, 'BAH', 'PAL', 0, 3, '2021-05-10');

-- Inserir jogos BR22
INSERT INTO mr.Jogo (campeonato, numero, time1, time2, gols1, gols2, data_) VALUES
('BR22', 1, 'FLA', 'COR', 2, 0, '2022-06-01'),
('BR22', 2, 'PAL', 'GRE', 1, 0, '2022-06-02'),
('BR22', 3, 'INT', 'CAM', 2, 2, '2022-06-03'),
('BR22', 4, 'SAO', 'BOT', 0, 1, '2022-06-04'),
('BR22', 5, 'VAS', 'BAH', 3, 3, '2022-06-05'),
('BR22', 6, 'COR', 'SAO', 1, 1, '2022-06-06'),
('BR22', 7, 'GRE', 'FLA', 1, 3, '2022-06-07'),
('BR22', 8, 'CAM', 'PAL', 2, 0, '2022-06-08'),
('BR22', 9, 'BOT', 'VAS', 0, 2, '2022-06-09'),
('BR22', 10, 'BAH', 'INT', 1, 2, '2022-06-10');

-- Inserir jogos LIB22
INSERT INTO mr.Jogo (campeonato, numero, time1, time2, gols1, gols2, data_) VALUES
('LIB22', 1, 'FLA', 'CAM', 1, 1, '2022-08-01'),
('LIB22', 2, 'PAL', 'COR', 2, 0, '2022-08-02'),
('LIB22', 3, 'GRE', 'INT', 0, 0, '2022-08-03'),
('LIB22', 4, 'SAO', 'FLA', 1, 4, '2022-08-04'),
('LIB22', 5, 'VAS', 'PAL', 0, 1, '2022-08-05'),
('LIB22', 6, 'BOT', 'BAH', 2, 2, '2022-08-06'),
('LIB22', 7, 'COR', 'GRE', 1, 1, '2022-08-07'),
('LIB22', 8, 'INT', 'SAO', 0, 2, '2022-08-08'),
('LIB22', 9, 'CAM', 'VAS', 3, 0, '2022-08-09'),
('LIB22', 10, 'BAH', 'FLA', 0, 5, '2022-08-10');

--------------------------------- BASE DE DADOS GERADA COM CHATGPT ---------------------------------

-- Exercício
-- Considerando o esquema lógico do banco de dados apresentado a seguir para campeonatos de futebol, especifique uma função para computar a tabela de classificação dos campeonatos. A função deverá ter como parâmetros de entrada:
-- 1) o código do campeonato para o qual se deseja gerar a tabela de classificação, 
-- 2) a posição inicial do ranque e 
-- 3) a posição final do ranque.
-- Obs. 1: Uma vitória vale 3 pontos e um empate 1 ponto.
-- Obs. 2: A classificação é feita por ordem decrescente de pontuação.
-- Obs. 3: O critério de desempate é o número de vitórias

drop function if exists mr.gerar_classificacao;
create or replace function mr.gerar_classificacao(camp text) returns table(
    nome text,
    pontuacao int,
    vitorias int
) as $$
declare
    reg record;
begin

    -- Cria a tabela temporária
    create temp table Classificacao(
        nome text,
        pontuacao int,
        vitorias int
    ) on commit drop;

    -- Cria uma função que adiciona ou atualiza o registro
    create or replace function adicionar_registro(time_ text, pontos int) returns void as $func$
    declare
        cur cursor for select * from Classificacao where nome = time_;
    begin
        open cur;
        if found then
            update Classificacao set pontuacao = pontuacao + pontos, vitorias = vitorias + 1 where nome = time_;
        else
            insert into Classificacao values (time_, pontos, 1);
        end if;
        close cur;
    end
    $func$ language plpgsql;    

    -- Percorre todos os registros do campeonato e aplica a função de adicionar ou atualizar
    for reg in select * from mr.Jogo where campeonato = camp loop 

        if reg.gols1 > reg.gols2 then
            perform adicionar_registro(reg.time1, 3);
        elsif reg.gols2 > reg.gols1 then
            perform adicionar_registro(reg.time2, 3);
        else
            perform adicionar_registro(reg.time1, 1);
            perform adicionar_registro(reg.time2, 1);
        end if;

    end loop;

    -- Retorna a query
    return query select * from Classificacao order by pontuacao desc, vitorias desc;
end
$$ language plpgsql;

create or replace function mr.gerar_classificacao(time_ text, i int, f int) returns table(
    nome text,
    pontuacao int,
    vitorias int
) as $$
begin
    return query select * from mr.gerar_classificacao(time_) OFFSET i LIMIT f - i + 1;
end
$$ language plpgsql;

select mr.gerar_classificacao('LIB22', 3, 5);