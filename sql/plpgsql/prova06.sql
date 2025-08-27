-- Os pedidos de refeição em uma rede de restaurantes são armazenados em um banco de dados cuja  especificação (em PostgreSQL) encontra-se a seguir. Os preços dos pratos podem variar de uma loja para  outra e nem todos os restaurantes oferecem os mesmos pratos. Além disso, cada pedido deve ser feito a  somente um único restaurante. Escreva, utilizando triggers PostgreSQL, a implementação da restrição de  integridade que garante a consistência dos pedidos no que se refere somente a unicidade de restaurante do  pedido. 
-- Atenção! Lembre-se que devem ser tratados todos os pontos de potencial violação de integridade, do  contrário sua solução não será considerada. 
drop schema if exists mr CASCADE;
create schema mr;
create table mr.restaurante (
  cnpj integer not null, 
  endereco character varying not null,  
  constraint rest_pk primary key(cnpj)
);
create table mr.prato ( 
  prato_id integer not null, 
  nome character varying not null,  
  constraint prato_pk primary key(prato_id)
);
create table mr.pedido ( 
  pedido_id integer not null, 
  cnpj integer not null, 
  constraint pedido_pk primary key(pedido_id), 
  constraint pedido_rest_fk foreign key(cnpj) references mr.restaurante (cnpj)
);
create table mr.menu ( 
  cnpj integer not null, 
  prato_id integer not null, 
  preco real not null, 
  constraint menu_pk primary key(cnpj,prato_id), 
  constraint menu_rest_fk foreign key(cnpj) references mr.restaurante(cnpj),  
  constraint menu_prato_fk foreign key(prato_id) references mr.prato(prato_id)
); 
create table mr.item_pedido ( 
  pedido_id integer not null, 
  item integer not null, 
  cnpj integer not null, 
  prato_id integer not null, 
  qtd integer not null, 
  constraint item_pk primary key(pedido_id,item),
  constraint item_pedido_fk foreign key(pedido_id) references mr.pedido(pedido_id), 
  constraint item_menu_fk foreign key(cnpj,prato_id) references mr.menu(cnpj,prato_id)
 );

 -- Criando base de dados
INSERT INTO mr.restaurante (cnpj, endereco) VALUES
(1001, 'Rua das Flores, 123'),
(1002, 'Av. Central, 456'),
(1003, 'Rua dos Limoeiros, 789'),
(1004, 'Av. Paulista, 1500'),
(1005, 'Rua XV de Novembro, 321');

INSERT INTO mr.prato (prato_id, nome) VALUES
(1, 'Feijoada'),
(2, 'Lasanha'),
(3, 'Hamburguer'),
(4, 'Pizza Margherita'),
(5, 'Risoto de Camarão'),
(6, 'Estrogonofe'),
(7, 'Taco Mexicano'),
(8, 'Yakissoba'),
(9, 'Churrasco'),
(10, 'Salada Caesar');

INSERT INTO mr.menu (cnpj, prato_id, preco) VALUES
(1001, 1, 30.0), (1001, 2, 25.0), (1001, 3, 20.0), (1001, 4, 99.0),
(1002, 4, 35.0), (1002, 5, 40.0), (1002, 6, 27.5),
(1003, 7, 22.0), (1003, 8, 26.0), (1003, 9, 45.0),
(1004, 1, 32.0), (1004, 10, 18.0), (1004, 6, 26.0),
(1005, 3, 19.0), (1005, 4, 33.0), (1005, 9, 50.0);

INSERT INTO mr.pedido (pedido_id, cnpj) VALUES
(2001, 1001), (2002, 1001), (2003, 1002),
(2004, 1003), (2005, 1003), (2006, 1004),
(2007, 1005), (2008, 1005), (2009, 1002),
(2010, 1001);

INSERT INTO mr.item_pedido (pedido_id, item, cnpj, prato_id, qtd) VALUES
(2001, 1, 1001, 1, 2),
(2001, 2, 1001, 2, 1),
(2002, 1, 1001, 3, 3),
(2003, 1, 1002, 4, 2),
(2003, 2, 1002, 6, 1),
(2004, 1, 1003, 7, 1),
(2004, 2, 1003, 9, 2),
(2005, 1, 1003, 8, 1),
(2006, 1, 1004, 1, 2),
(2006, 2, 1004, 10, 1),
(2007, 1, 1005, 4, 1),
(2007, 2, 1005, 9, 2),
(2008, 1, 1005, 3, 1),
(2009, 1, 1002, 5, 1),
(2009, 2, 1002, 6, 1),
(2010, 1, 1001, 1, 1),
(2010, 2, 1001, 2, 2),
(2010, 3, 1001, 3, 1);

 ------------------------
 
-- 1) Os preços dos pratos podem variar de uma loja para outra
-- 2) Nem todos os restaurantes oferecem os mesmos pratos. 
-- 3) Além disso, cada pedido deve ser feito a somente um único restaurante. 

-- Todo item_pedido que for adicionado deve verificar se o prato_id tem no menu daquele restaurante
drop function if exists mr.garantir CASCADE;
create or replace function mr.garantir() returns trigger 
as $$
declare
  n integer := 0;
begin
    if tg_op = 'INSERT' then
        select count(*) from mr.menu 
        where 
            prato_id = new.prato_id 
            and cnpj = new.cnpj
        into n;
        if n = 0 then
            raise exception 'Prato inválido!';
        else
            return new;
        end if;
    end if;
    if tg_op = 'UPDATE' then
        if
            new.pedido_id = old.pedido_id and
            new.item = old.item and
            new.cnpj = old.cnpj and
            new.prato_id = old.prato_id
        then
            return new;
        else
            return null;
        end if;
    end if;
    
    return null;
end
$$ language plpgsql;

create trigger garantir_integridade_pedido
before insert or update on mr.item_pedido 
for each row
execute function mr.garantir();

-- Teste
INSERT INTO mr.item_pedido (pedido_id, item, cnpj, prato_id, qtd) VALUES (2010, 4, 1001, 4, 2);
update mr.item_pedido set qtd = 1 where pedido_id = 2010 and item = 4 and cnpj = 1001 and prato_id = 4;
select qtd from mr.item_pedido where pedido_id = 2010 and item = 4 and cnpj = 1001 and prato_id = 4;