------------------------------- Enunciado -------------------------------

-- Escreva uma função PL/pgSQL para retornar um histograma da quantidade de respostas por pergunta para a pesquisa, bairros e cidades informados como parâmetros. Mais detalhadamente, você deverá construir uma função com a seguinte assinatura:
--      resultado(p_pesquisa int, p_bairros varchar[], p_cidades varchar[]).
-- O parâmetro p_pesquisa informa o número identificador da pesquisa para a qual deseja-se calcular o histograma, o parâmetro p_bairros informa uma lista de bairros onde foram feitas as entrevistas a serem computadas no histograma, o parâmetro p_cidades informa uma lista de cidades onde foram feitas as entrevistas a serem computadas no histograma. Se p_bairros ou p_cidades forem desconhecidos (contiverem o valor null), todos os bairros e cidades devem ser considerados no histograma.
-- A função deverá retornar uma tabela com o seguinte esquema (pergunta int, histograma float[]), onde pergunta é o número de uma pergunta da pesquisa informada e histograma é a quantidade percentual de cada resposta para a pergunta. Por exemplo, se uma linha de resultado for 1,’{{1,0},{2,0.6},{3,0.2},{4,0.2},{5,0}}’ significa que a resposta 1 da pergunta 1 não foi mencionada por ninguém, a resposta 2 da mesma pergunta foi mencionada por 60% (0.6) dos entrevistados, a resposta 3 da mesma pergunta foi mencionada por 20% (0.2) dos entrevistados, a resposta 4 por 20% e a resposta 5 não foi mencionada por ninguém.

------------------------------- Tabelas -------------------------------
drop schema mr cascade; 
create schema mr;

create table mr.cidade(
    numero int not null primary key,
    nome varchar not null
);
create table mr.bairro(
    numero int not null primary key,
    nome varchar not null,
    cidade int not null,
    foreign key (cidade) references mr.cidade(numero)
);
create table mr.pesquisa(
    numero int not null,
    descricao varchar not null,
    primary key (numero)
);
create table mr.pergunta(
    pesquisa int not null,
    numero int not null,
    descricao varchar not null,
    primary key (pesquisa,numero),
    foreign key (pesquisa) references mr.pesquisa(numero)
);
create table mr.resposta(
    pesquisa int not null,
    pergunta int not null,
    numero int not null,
    descricao varchar not null,
    primary key (pesquisa,pergunta,numero),
    foreign key (pesquisa,pergunta)
    references mr.pergunta(pesquisa,numero)
);
create table mr.entrevista(
    numero int not null primary key,
    data_hora timestamp not null,
    bairro int not null,
    foreign key (bairro) references mr.bairro(numero)
);
create table mr.escolha(
    entrevista int not null,
    pesquisa int not null,
    pergunta int not null,
    resposta int not null,
    primary key (entrevista,pesquisa,pergunta),
    foreign key (entrevista) references mr.entrevista (numero),
    foreign key (pesquisa,pergunta,resposta) references mr.resposta(pesquisa,pergunta,numero)
);

------------------------------- Base de dados -------------------------------

INSERT INTO mr.cidade (numero, nome) VALUES (1, 'Cidade Alpha'),(2, 'Cidade Beta');
INSERT INTO mr.bairro (numero, nome, cidade) VALUES (1, 'Centro', 1),(2, 'Zona Sul', 1),(3, 'Norte', 2);
INSERT INTO mr.pesquisa (numero, descricao) VALUES (1, 'Pesquisa de Satisfação'),(2, 'Pesquisa de Transporte Público');
INSERT INTO mr.pergunta (pesquisa, numero, descricao) VALUES (1, 1, 'Você está satisfeito com os serviços públicos?'),(1, 2, 'Você recomendaria a cidade para morar?'),(2, 1, 'Você utiliza transporte público diariamente?'),(2, 2, 'Você está satisfeito com o transporte público?');

INSERT INTO mr.resposta (pesquisa, pergunta, numero, descricao) VALUES (1, 1, 1, 'Sim'),(1, 1, 2, 'Não'),(1, 2, 1, 'Sim'),(1, 2, 2, 'Não'),(2, 1, 1, 'Sim'),(2, 1, 2, 'Não'),(2, 2, 1, 'Sim'),(2, 2, 2, 'Não');
INSERT INTO mr.entrevista (numero, data_hora, bairro) VALUES(1, '2025-04-26 10:00:00', 1),(2, '2025-04-26 11:00:00', 2),(3, '2025-04-26 12:00:00', 3);
INSERT INTO mr.escolha (entrevista, pesquisa, pergunta, resposta) VALUES
(1, 1, 1, 1),(1, 1, 2, 2),(2, 2, 1, 1),(2, 2, 2, 2),(3, 1, 1, 2),(3, 1, 2, 1);

------------------------------- Resolução -------------------------------
select * 
from 
    mr.pesquisa as pes join escolha as esc on pes.numero = esc.pesquisa
    join mr.entrevista as ent on ent.numero = esc.entrevista
    join mr.bairro as bai on bai.numero = ent.bairro
    join mr.cidade as cid on cid.numero = bai.cidade;

drop function if exists mr.resultado;
create or replace function mr.resultado(p_pesquisa int, p_bairros varchar[], p_cidades varchar[]) returns table(
    pesquisa int,
    freq float
) as $$
declare
    reg record;
    cur cursor(num int) for select * from Histograma as h where num = h.pesquisa;
    n int := 0;
    lixo int;
    where_result text;
    r1 int := array_length(p_bairros,1);
    r2 int := array_length(p_cidades,1);
begin

    create temp table Histograma(
        pesquisa int,
        fr float
    ) on commit drop;

    if r1>0 or r2>0 then
        where_result := where_result || ' where ';
    end if;

    for reg in select format('
        pes.numero as numero
    from 
        mr.pesquisa as pes join escolha as esc on pes.numero = esc.pesquisa
        join mr.entrevista as ent on ent.numero = esc.entrevista
        join mr.bairro as bai on bai.numero = ent.bairro
        join mr.cidade as cid on cid.numero = bai.cidade %s', where_result) loop
        
        open cur(reg.numero);
        fetch cur into lixo;
        if found then
            update Histograma set fr = fr + 1 where current of cur;
        else
            insert into Histograma values (reg.numero, 1);
        end if; 
        close cur;

        n := n + 1;
    end loop;

    return query select Histograma.pesquisa, (fr / n)::float as freq from Histograma;
end
$$ language plpgsql;

create or replace function mr.resultado(p_pesquisa int, p_bairros varchar[]) returns table(
    pesquisa int,
    freq float
) as $$
declare
begin
    return query select mr.resultado(p_pesquisa, p_bairros, array[]::varchar[]);
end
$$ language plpgsql;

create or replace function mr.resultado(p_pesquisa int) returns table(
    pesquisa int,
    freq float
) as $$
declare
begin
    return query select mr.resultado(p_pesquisa, array[]::varchar[], array[]::varchar[]);
end
$$ language plpgsql;

select mr.resultado(1);