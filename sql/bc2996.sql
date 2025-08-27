-- https://judge.beecrowd.com/pt/problems/view/2996


drop table if exists users cascade;
create table users(
    id numeric primary key,
    name varchar(50),
    address varchar(50)
);

drop table if exists packages;
create table packages(
    id_package numeric primary key,
    id_user_sender integer,
    id_user_receiver integer,
    color varchar(50),
    year integer,
    constraint fk1 foreign key (id_user_sender) references users(id),
    constraint fk2 foreign key (id_user_receiver) references users(id)
);
insert into users(id, name, address) values 
    (1,'Edgar Codd', 'England'),
    (2,'Peter Chen', 'Taiwan'),
    (3,'Jim Gray',	'United States'),
    (4, 'Elizabeth ONeil', 'United States');
 
select * from users where users.name is not Null;

insert into packages values 
    (1, 1, 2,'blue',2015),
    (2, 1, 3,'blue',2019),
    (3, 2, 4,'red',2019),
    (4, 2, 1,'green',2018),
    (5, 3, 4,'red',2015),
    (6,4,3,'blue',2019);

select 
    p.year as year, 
    u1.name as sender, 
    u2.name as receiver 
from packages as p
    join users as u1 on (p.id_user_sender = u1.id)
    join users as u2 on (p.id_user_receiver = u2.id)
where 
    (p.color = 'blue' or p.year = 2015) and 
    (u1.address <> 'Taiwan' or u2.address <> 'Taiwan')
order by p.year desc;

-- 1) precisa mostrar com urgência o ano e o nome
-- Podemos ver pela saída que o formato de saída vai ser o seguinte: (year, sender, receiver)
-- select 
--     year as year, 
--     name as sender, 
--     name as receiver 
-- from packages;

-- 2) todos os clientes que enviaram e receberam pacotes azuis ou do ano de 2015 e também que o endereço do seu remetente ou destinatário não seja de Taiwan
-- Para validar isso, precisamos fazer junções:
-- select 
--     year as year, 
--     name as sender, 
--     name as receiver 
-- from packages as p
--     join users as u1 on (p.id_user_sender = u1.id)
--     join users as u2 on (p.id_user_receiver = u2.id);

-- Agora precisamos verificar as condições:
-- ((todos os clientes que ((enviaram e receberam) (pacotes azuis ou do ano de 2015))) e (também que o endereço do seu (remetente ou destinatário) não seja de Taiwan))
-- select 
--     year as year, 
--     name as sender, 
--     name as receiver 
-- from packages as p
--     join users as u1 on (p.id_user_sender = u1.id)
--     join users as u2 on (p.id_user_receiver = u2.id)
-- where (color = 'blue' or year 2015) and (u1.address <> 'Taiwan' or u2.address <> 'Taiwan');

-- 3) você deve ordenar o resultado pelo ano de maneira decrescente
-- Então devemos ordenar o resultado final
-- select 
--     year as year, 
--     name as sender, 
--     name as receiver 
-- from packages as p
--     join users as u1 on (p.id_user_sender = u1.id)
--     join users as u2 on (p.id_user_receiver = u2.id)
-- where (color = 'blue' or year 2015) and (u1.address <> 'Taiwan' or u2.address <> 'Taiwan')
-- order by p.year desc;

-- 4) Resta arrumar a saída
-- select 
--     p.year as year, 
--     u1.name as sender, 
--     u2.name as receiver 
-- from packages as p
--     join users as u1 on (p.id_user_sender = u1.id)
--     join users as u2 on (p.id_user_receiver = u2.id)
-- where (color = 'blue' or year 2015) and (u1.address <> 'Taiwan' or u2.address <> 'Taiwan')
-- order by p.year desc;


create table alunos(id INT PRIMARY KEY, nome text);
create table prova(id INT PRIMARY KEY, nome text);
create table nota(
    id_aluno int, 
    id_prova int, 
    nota REAL,
    constraint pk PRIMARY key (id_aluno, id_prova),
    constraint fk1 FOREIGN KEY(id_aluno) REFERENCES alunos(id),
    constraint fk2 FOREIGN KEY(id_prova) REFERENCES prova(id)
);

insert into alunos values (1, 'joão'), (2, 'pedro'), (3, 'joaquim');
insert into prova values (1, 'matemática'), (2, 'português'), (3, 'lógica');
insert into nota values 
(1, 1, 10), (1, 2, 7), (1, 3, 8),
(2, 1, 10), (2, 2, 7), (2, 3, 8),
(3, 1, 10), (3, 2, 7), (3, 3, 8);

select (alunos.nome, prova.nome, nota.nota) from nota join alunos on nota.id_aluno = alunos.id join prova on nota.id_prova = prova.id;

select (alunos.nome, sum(nota.nota)) from nota join alunos on nota.id_aluno = alunos.id join prova on nota.id_prova = prova.id
GROUP BY alunos.nome
HAVING sum(nota.nota) = 25;

select * from nota join alunos on nota.id_aluno = alunos.id join prova on nota.id_prova = prova.id group by alunos.nome;

select e.nome from empregado as e
where (e.id, numero) in (select (cod_empregado, numero) from dependente);