DROP SCHEMA IF EXISTS mr CASCADE;
CREATE SCHEMA mr;

drop table if exists mr.campeonato cascade;
CREATE TABLE mr.campeonato (
    codigo text NOT NULL,
    nome TEXT NOT NULL,
    ano integer not null,
    CONSTRAINT campeonato_pk PRIMARY KEY(codigo)
);

drop table if exists mr.time_ cascade;
CREATE TABLE mr.time_ (
    sigla text NOT NULL,
    nome TEXT NOT NULL,
    CONSTRAINT time_pk PRIMARY KEY(sigla)
);

drop table if exists mr.jogo cascade;
CREATE TABLE mr.jogo (
    campeonato text not null,
    numero integer NOT NULL,
    time1 text NOT NULL,
    time2 text NOT NULL,
    gols1 integer not null,
    gols2 integer not null,
    data_ date not null,
    CONSTRAINT jogo_pk PRIMARY KEY(campeonato,numero),
    CONSTRAINT jogo_campeonato_fk FOREIGN KEY(campeonato) REFERENCES mr.campeonato(codigo),
    CONSTRAINT jogo_time_fk1 FOREIGN KEY (time1) REFERENCES mr.time_ (sigla),
    CONSTRAINT jogo_time_fk2 FOREIGN KEY(time2) REFERENCES mr.time_ (sigla)
);

--------------------------------- BASE DE DADOS GERADA COM CHATGPT ---------------------------------

-- Inserir campeonatos
INSERT INTO mr.campeonato (codigo, nome, ano) VALUES
('BR21', 'Brasileirão Série A', 2021),
('BR22', 'Brasileirão Série A', 2022),
('LIB22', 'Copa Libertadores', 2022);

-- Inserir times
INSERT INTO mr.time_ (sigla, nome) VALUES
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
INSERT INTO mr.jogo (campeonato, numero, time1, time2, gols1, gols2, data_) VALUES
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
INSERT INTO mr.jogo (campeonato, numero, time1, time2, gols1, gols2, data_) VALUES
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
INSERT INTO mr.jogo (campeonato, numero, time1, time2, gols1, gols2, data_) VALUES
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

SELECT mr.gerar_classificacao('BR22');

select j.time1 from mr.jogo as j where j.campeonato = 'LIB22' and j.gols1 > j.gols2;
select j.time2 from mr.jogo as j where j.campeonato = 'LIB22' and j.gols1 < j.gols2;
select j.time1, j.time2 from mr.jogo as j where j.campeonato = 'LIB22' and j.gols1 = j.gols2;


drop function mr.criar_classificacao;
create or replace function mr.criar_classificacao(cod text) returns table(
        time_ text,
        pontuacao int,
        vitoria int
) as $$
declare
    reg record;
    existe record;
begin

    create temp table classificacao(
        time_ text,
        pontuacao int,
        vitorias int
    ) on commit drop;
    
    for reg in select j.time1, j.time2, j.gols1, j.gols2 from mr.jogo as j where j.campeonato = cod LOOP

        if reg.gols1 > reg.gols2 then
            
            select * from classificacao as c where c.time_ = reg.time1 into existe; 
            if existe is null THEN
                insert into classificacao values (reg.time1, 3, 1);
            else
                update classificacao set pontuacao = pontuacao +3, vitorias = vitorias + 1 where time_ = reg.time1;
            end if;

        elsif reg.gols2 > reg.gols1 then

            select * from classificacao as c where c.time_ = reg.time2 into existe; 
            if existe is null THEN
                insert into classificacao values (reg.time2, 3, 1);
            else
                update classificacao set pontuacao = pontuacao+3, vitorias = vitorias + 1 where time_ = reg.time2;
            end if;

        else
            
            select * from classificacao as c where c.time_ = reg.time1 into existe; 
            if existe is null THEN
                insert into classificacao values (reg.time1, 1, 0);
            else
                update classificacao set pontuacao = pontuacao+1 where time_ = reg.time1;
            end if;

            select * from classificacao as c where c.time_ = reg.time2 into existe; 
            if existe is null THEN
                insert into classificacao values (reg.time2, 1, 0);
            else
                update classificacao set pontuacao = pontuacao+1 where time_ = reg.time2;
            end if;

        end if;

    end loop;

    return query select * from classificacao;
end
$$ language plpgsql;
create or replace function mr.gerar_classificacao(cod text, inicio int, fim int) returns table(
        time_ text,
        pontuacao int,
        vitoria int
) as $$
begin
    return query select * from mr.gerar_classificacao(cod);
end
$$ language plpgsql;

select mr.criar_classificacao('LIB22', 1, 3);