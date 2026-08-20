-- https://judge.beecrowd.com/pt/problems/view/2990

CREATE TABLE empregados (
    cpf varchar(15),
    enome varchar(60),
    salario float,
    cpf_supervisor varchar(15),
    dnumero integer,
    PRIMARY KEY (cpf)
);

CREATE TABLE departamentos (
    dnumero integer,
    dnome varchar(60),
    cpf_gerente varchar(15),
    PRIMARY KEY (dnumero),
    CONSTRAINT fk_cpf FOREIGN KEY(cpf_gerente) REFERENCES empregados(cpf)
);

CREATE TABLE trabalha (
    cpf_emp varchar(15),
    pnumero integer,
    CONSTRAINT fk_cpfemp FOREIGN KEY(cpf_emp) REFERENCES empregados(cpf)
);

CREATE TABLE projetos (
    pnumero integer,
    pnome varchar(45),
    dnumero integer,
    PRIMARY KEY(pnumero),
    CONSTRAINT fk_dnum FOREIGN KEY(dnumero) REFERENCES
    departamentos(dnumero)
);

Insert Into empregados
values ('049382234322','João Silva', 2350, '2434332222', 1010);
Insert Into empregados(cpf, enome, salario, cpf_supervisor, dnumero)
values ('586733922290','Mario Silveira', 3500, '2434332222', 1010);
Insert Into empregados
values ('2434332222','Aline Barros', 2350, NULL, 1010);

Insert Into empregados
values ('1733332162','Tulio Vidal', 8350, NULL, 1020);
Insert Into empregados
values ('4244435272','Juliana Rodrigues', 3310, NULL, 1020);
Insert Into empregados
values ('1014332672','Natalia Marques', 2900, NULL, 1010);
Insert Into departamentos (dnumero, dnome, cpf_gerente)
values (1010, 'Pesquisa', '049382234322');
Insert Into departamentos
values (1020, 'Ensino', '2434332222');
Insert Into trabalha (cpf_emp, pnumero)
values ('049382234322', 2010);
Insert Into trabalha (cpf_emp, pnumero)
values ('586733922290', 2020);
Insert Into trabalha (cpf_emp, pnumero)
values ('049382234322', 2020);
Insert Into projetos (pnumero, pnome, dnumero)
values (2010,'Alpha', 1010);
Insert Into projetos (pnumero, pnome, dnumero)
values (2020,'Beta', 1020);

ALTER TABLE empregados ADD CONSTRAINT fk_danum FOREIGN KEY(dnumero)
REFERENCES departamentos(dnumero);
ALTER TABLE trabalha ADD CONSTRAINT fk_pnum FOREIGN KEY(pnumero)
REFERENCES projetos(pnumero);

select
    cpf,
    enome,
    dnome
from empregados natural join departamentos
where cpf not in (select cpf_emp from trabalha); 

DROP TABLE empregados, trabalha, departamentos, projetos CASCADE;