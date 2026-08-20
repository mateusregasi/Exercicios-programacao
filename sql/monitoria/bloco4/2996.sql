-- https://judge.beecrowd.com/pt/problems/view/2996

CREATE TABLE users (
    id integer PRIMARY KEY,
    name varchar(50),
    address varchar(50)
);

CREATE TABLE packages (
    id_package integer PRIMARY KEY,
    id_user_sender integer,
    id_user_receiver integer,
    color varchar(50),
    year integer,
    FOREIGN KEY (id_user_sender) REFERENCES users(id),
    FOREIGN KEY (id_user_receiver) REFERENCES users(id)
);

insert into users (id,name,address) values
(1,'Edgar Codd','England'),
(2,'Peter Chen','Taiwan'),
(3,'Jim Gray','United States'),
(4,'Elizabeth ONeil','United States');

insert into packages (id_package,id_user_sender,id_user_receiver,color,year) values
(1,1,2,'blue',2015),
(2,1,3,'blue',2019),
(3,2,4,'red',2019),
(4,2,1,'green',2018),
(5,3,4,'red',2015),
(6,4,3,'blue',2019);

select
    u1.name,
    u2.name,
    p.year
from
    packages as p join users as u1 
        on (u1.id = p.id_user_sender)
     join users as u2
        on (u2.id = p.id_user_receiver)
where (p.color = "blue" or year = 2015) and (u1.address != "Taiwan" and u2.address != "Taiwan")
order by p.year desc;

DROP TABLE packages;
DROP TABLE users;