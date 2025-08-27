drop schema if exists mr cascade;
create schema mr;

drop table if exists mr.movimentacao;
create table mr.movimentacao(
  id serial,
  conta integer not null,
  agencia integer not null,
  data timestamp not null,
  valor real not null,
  descricao character varying not null,
  data_manutencao timestamp not null,
  primary key(id)
);
drop table if exists mr.conta;
create table mr.conta(
    id serial,
    nome varchar(50),
    primary key(id)
);

-- Observação: entendi data_manutenção como qualquer alteração que se faça dentro de movimentação, incluindo inclusão, inserção ou alteração. Ou seja, qualquer registro de nova movimentação ou estorno.
create or replace function mr.gerar_movimentacao() returns trigger 
as $$
begin
    if tg_op = 'UPDATE' then
        insert into 
            mr.movimentacao(conta, agencia, data, valor, descricao, data_manutencao) 
        values (
            OLD.conta,
            OLD.agencia,
            now(),
            OLD.valor,
            'movimentação',
            now()
        );
    end if;
    if tg_op = 'DELETE' then
        insert into 
            mr.movimentacao(conta, agencia, data, valor, descricao, data_manutencao) 
        values(
            OLD.conta,
            OLD.agencia,
            now(),
            -OLD.valor,
            'estorno',
            now()
        );
    end if;
    return null;
end
$$ language plpgsql;

create trigger movimento 
before update or delete
on mr.movimentacao for each row
execute function mr.gerar_movimentacao();

-- TESTE
select * from mr.movimentacao;
insert into mr.conta(nome) values ('Mateus'), ('Regasi'), ('Gomes'), ('Martins');
insert into mr.movimentacao(conta, agencia, data, valor, descricao, data_manutencao) values 
(1, 1, now(), 10, 'movimentacao', now());
delete from mr.movimentacao;