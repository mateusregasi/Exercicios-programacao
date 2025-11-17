-- https://judge.beecrowd.com/pt/problems/view/2614

CREATE TABLE customers (
  id numeric PRIMARY KEY,
  name varchar(50),
  street varchar(50),
  city varchar(50)
);

CREATE TABLE rentals (
  id numeric PRIMARY KEY,
  rentals_date date,
  id_customers numeric REFERENCES customers (id)
);

INSERT INTO customers (id, name, street, city)
VALUES
  (1,	'Giovanna Goncalves Oliveira',	'Rua Mato Grosso',	'Canoas'),
  (2,	'Kauã Azevedo Ribeiro',	'Travessa Ibiá',	'Uberlândia'),
  (3,	'Rebeca Barbosa Santos',	'Rua Observatório Meteorológico',	'Salvador'),
  (4,	'Sarah Carvalho Correia',	'Rua Antônio Carlos da Silva',	'Apucarana'),
  (5,	'João Almeida Lima',	'Rua Rio Taiuva',	'Ponta Grossa'),
  (6,	'Diogo Melo Dias',	'Rua Duzentos e Cinqüenta',	'Várzea Grande');

INSERT INTO rentals (id, rentals_date, id_customers)
VALUES
  (1,	'2016-09-10',	3),
  (2,	'2016-02-09',	1),
  (3,	'2016-02-08',	4),
  (4,	'2015-02-09',	2),
  (5,	'2016-02-03',	6),
  (6,	'2016-04-04',	4);
  

select
    c.name,
    r.rentals_date
from customers as c join rentals as r
    on (r.id_customers = c.id)
where   extract(month from r.rentals_date) = 9 
        and extract(year from r.rentals_date) = 2016;

DROP TABLE rentals, customers;