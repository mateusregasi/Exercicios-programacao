----------------------------------------------------------------
-------------------------------DER------------------------------ 
-- https://app.brmodeloweb.com/#!/conceptual/68029281ce1e00f61004aaed
-- 
-- Membros:
-- Yan Souto Novaes de Souza
-- Yuti Grinberg Souza Lima 
-- Mateus Regasi Gomes Martins
-- Caio Andrade da Silva Cunha
-- 
------------------------ Banco de dados ------------------------
drop schema biblio cascade;

create SCHEMA biblio;
CREATE TABLE biblio.Autor (
    pk SERIAL,
    nome TEXT NOT NULL,
    constraint pk_autor PRIMARY KEY(pk)
);
CREATE TABLE biblio.Genero (
    pk SERIAL,
    nome TEXT NOT NULL,
    constraint pk_genero PRIMARY KEY(pk)
);
CREATE TABLE biblio.Cliente (
    pk SERIAL,
    nome TEXT NOT NULL,
    constraint pk_cliente PRIMARY KEY(pk)
);
CREATE TABLE biblio.Livro(
    pk SERIAL,
    isbn TEXT not null,
    titulo TEXT NOT NULL,
    num_paginas INTEGER NOT NULL,
    pk_genero int,
    constraint pk_livro PRIMARY KEY(pk),
    constraint fk_genero FOREIGN KEY(pk_genero) REFERENCES biblio.Genero(pk)
);
create table biblio.LivroAutor(
    pk_livro int,
    pk_autor int,
    constraint pk_livro_autor PRIMARY KEY(pk_livro, pk_autor),
    constraint fk_livro FOREIGN KEY(pk_livro) REFERENCES biblio.Livro(pk),
    constraint fk_autor FOREIGN KEY(pk_autor) REFERENCES biblio.Autor(pk)
);
CREATE TABLE biblio.Biblioteca (
    pk SERIAL,
    cidade_estado TEXT NOT NULL,
    constraint pk_biblioteca PRIMARY KEY(pk)
);
CREATE TABLE biblio.CopiaLivro (
    pk SERIAL,
    pk_livro int,
    pk_biblioteca int,
    emprestado BOOLEAN DEFAULT FALSE,
    bloqueado BOOLEAN DEFAULT FALSE,
    constraint pk_copia_livro PRIMARY KEY(pk),
    constraint fk_livro FOREIGN KEY(pk_livro) REFERENCES biblio.Livro(pk),
    constraint fk_biblioteca FOREIGN KEY(pk_biblioteca) REFERENCES biblio.Biblioteca(pk)
);
CREATE TABLE biblio.Emprestimo (
    pk SERIAL,
    pk_cliente INTEGER ,
    pk_copia_livro INTEGER,
    data_retirada DATE NOT NULL,
    data_devolucao DATE,
    data_prazo DATE not null,
    constraint pk_emprestimo PRIMARY KEY(pk),
    constraint fk_cliente FOREIGN KEY(pk_cliente) REFERENCES biblio.Cliente(pk),
    constraint fk_copia_livro FOREIGN KEY(pk_copia_livro) REFERENCES biblio.CopiaLivro(pk)
);
CREATE TABLE biblio.AgendamentoMovimentacao (
    pk SERIAL,
    pk_origem int,
    pk_destino int,
    data_sapka DATE,
    data_entrega DATE,
    entregue BOOLEAN DEFAULT FALSE,
    constraint pk_agendamento_movimentacao PRIMARY KEY(pk),
    constraint fk_origem FOREIGN KEY(pk_origem) REFERENCES biblio.Biblioteca(pk),
    constraint fk_destino FOREIGN KEY(pk_destino) REFERENCES biblio.Biblioteca(pk)
);
CREATE TABLE biblio.CopiaMovimentacao (
    pk_copia_livro int,
    pk_movimentacao int,
    constraint pk_copia_movimentacao PRIMARY KEY(pk_copia_livro, pk_movimentacao),
    constraint fk_copia_livro FOREIGN KEY(pk_copia_livro) REFERENCES biblio.CopiaLivro(pk),
    constraint fk_movimentacao FOREIGN KEY(pk_movimentacao) REFERENCES biblio.AgendamentoMovimentacao(pk)
);

------------------------ Inserindo valores de teste ------------------------
INSERT INTO biblio.Autor (nome) VALUES ('Machado de Assis'),('Clarice Lispector'),('George Orwell'),('J.K. Rowling'),('J.R.R. Tolkien'),('Gabriel García Márquez'),('Franz Kafka'),('Virginia Woolf'),('Cecília Meireles');
INSERT INTO biblio.Genero (nome) VALUES ('Romance'),('Ficção Científica'),('Fantasia'),('Drama'),('Poesia'),('Suspense'),('Biografia');
INSERT INTO biblio.Cliente (nome) VALUES ('João da Silva'),('Maria Oliveira'),('Carlos Souza'),('Ana Beatriz Ramos'),('Felipe Duarte'),('Lucas Martins'),('Patrícia Ferreira'),('Renata Costa');
INSERT INTO biblio.Livro (isbn, titulo, num_paginas, pk_genero) VALUES 
    ('978-85-01-00001-1', 'Dom Casmurro', 256, 1),
    ('978-85-01-00002-8', 'A Hora da Estrela', 96, 4),
    ('978-85-01-00003-5', '1984', 328, 2),
    ('978-85-01-00004-2', 'Harry Potter e a Pedra Filosofal', 223, 3),
    ('978-85-01-00005-9', 'O Senhor dos Anéis', 1178, 3),
    ('978-85-01-00006-6', 'Cem Anos de Solidão', 417, 1),
    ('978-85-01-00007-3', 'A Metamorfose', 74, 2),
    ('978-85-01-00008-0', 'Mrs. Dalloway', 224, 4),
    ('978-85-01-00009-7', 'Romanceiro da Inconfidência', 180, 4),
    ('978-85-01-00010-3', 'Assassinato no Expresso do Oriente', 256, 6),
    ('978-85-01-00011-0', 'A Vida de Steve Jobs', 656, 7);
INSERT INTO biblio.LivroAutor (pk_livro, pk_autor) VALUES (1, 1),(2, 2),(3, 3),(4, 4),(5, 5),(6, 6),(7, 7),(8, 8),(9, 9),(10, 3),(11, 2);
INSERT INTO biblio.Biblioteca (cidade_estado) VALUES ('Niterói/RJ'),('Itapevi/SP'),('Ipatinga/MG');
INSERT INTO biblio.CopiaLivro (pk_livro, pk_biblioteca, emprestado, bloqueado) VALUES 
    (1, 1, FALSE, FALSE),
    (2, 1, FALSE, FALSE),
    (3, 2, TRUE, FALSE),
    (4, 3, FALSE, TRUE),
    (4, 2, FALSE, FALSE),
    (5, 1, FALSE, FALSE),
    (6, 2, FALSE, FALSE),
    (7, 2, TRUE, FALSE),
    (8, 3, FALSE, FALSE),
    (9, 1, FALSE, FALSE),
    (10, 3, FALSE, TRUE),
    (11, 2, FALSE, FALSE);
INSERT INTO biblio.Emprestimo (pk_cliente, pk_copia_livro, data_retirada, data_devolucao, data_prazo) VALUES 
    (1, 3, '2025-04-01', '2025-04-10', '2025-04-08'),
    (2, 1, '2025-04-05', '2025-04-12', '2025-04-10'),
    (3, 7, '2025-04-07', '2025-04-15', '2025-04-12'),
    (4, 8, '2025-04-09', '2025-04-19', '2025-04-14'),
    (5, 9, '2025-04-12', '2025-04-20', '2025-04-18'),
    (1, 4, '2025-04-17', '2025-04-17', '2025-04-24'),
    (2, 5, '2025-04-18', NULL, '2025-04-25'),
    (3, 6, '2025-04-15', NULL, '2025-04-22'),
    (1, 2, '2024-11-01', '2024-11-08', '2024-11-10'),
    (1, 3, '2024-12-05', '2024-12-20', '2024-12-17'),
    (1, 5, '2025-01-10', '2025-01-15', '2025-01-15'),
    (1, 6, '2025-02-01', '2025-02-20', '2025-02-15'),
    (1, 10, '2025-04-10', NULL, '2025-04-17'),
    (2, 4, '2025-03-01', '2025-03-10', '2025-03-08'),
    (3, 5, '2025-03-05', '2025-03-15', '2025-03-12'),
    (4, 6, '2025-03-07', '2025-03-17', '2025-03-14'),
    (5, 7, '2025-03-09', '2025-03-19', '2025-03-16'),
    (6, 8, '2025-03-11', '2025-03-21', '2025-03-18'),
    (7, 9, '2025-03-13', '2025-03-23', '2025-03-20'),
    (8, 10, '2025-03-15', '2025-03-25', '2025-03-22'),
    (1, 11, '2025-03-17', '2025-03-27', '2025-03-24'),
    (2, 1, '2025-03-19', '2025-03-29', '2025-03-26'),
    (3, 2, '2025-03-21', '2025-03-31', '2025-03-28'),
    (4, 3, '2025-03-23', '2025-04-02', '2025-03-30'),
    (5, 4, '2025-03-25', '2025-04-04', '2025-04-01'),
    (6, 5, '2025-03-27', '2025-04-06', '2025-04-03'),
    (7, 6, '2025-03-29', '2025-04-08', '2025-04-05'),
    (8, 7, '2025-03-31', '2025-04-10', '2025-04-07'),
    (1, 8, '2025-04-02', '2025-04-12', '2025-04-09'),
    (2, 9, '2025-04-04', '2025-04-14', '2025-04-11'),
    (3, 10, '2025-04-06', '2025-04-16', '2025-04-13'),
    (4, 11, '2025-04-08', '2025-04-18', '2025-04-15'),
    (5, 1, '2025-04-10', '2025-04-20', '2025-04-17'),
    (6, 2, '2025-04-12', '2025-04-22', '2025-04-19'),
    (7, 3, '2025-04-14', '2025-04-24', '2025-04-21'),
    (8, 4, '2025-04-16', '2025-04-26', '2025-04-23'),
    (1, 5, '2025-04-18', '2025-04-28', '2025-04-25'),
    (2, 6, '2025-04-20', '2025-04-30', '2025-04-27'),
    (3, 7, '2025-04-22', '2025-05-02', '2025-04-29'),
    (4, 8, '2025-04-24', '2025-05-04', '2025-05-01'),
    (5, 9, '2025-04-26', '2025-05-06', '2025-05-03'),
    (6, 10, '2025-04-28', '2025-05-08', '2025-05-05'),
    (7, 11, '2025-04-30', '2025-05-10', '2025-05-07'),
    (8, 1, '2025-05-02', '2025-05-12', '2025-05-09'),
    (1, 2, '2025-05-04', '2025-05-14', '2025-05-11'),
    (2, 3, '2025-05-06', '2025-05-16', '2025-05-13'),
    (3, 4, '2025-05-08', '2025-05-18', '2025-05-15'),
    (4, 5, '2025-05-10', '2025-05-20', '2025-05-17'),
    (5, 6, '2025-05-12', '2025-05-22', '2025-05-19'),
    (6, 7, '2025-05-14', '2025-05-24', '2025-05-21'),
    (7, 8, '2025-05-16', '2025-05-26', '2025-05-23'),
    (8, 9, '2025-05-18', '2025-05-28', '2025-05-25');
INSERT INTO biblio.AgendamentoMovimentacao (pk_origem, pk_destino, data_sapka, data_entrega, entregue) VALUES 
    (1, 2, '2025-04-15', '2025-04-18', FALSE),
    (2, 3, '2025-04-10', '2025-04-14', TRUE);
INSERT INTO biblio.CopiaMovimentacao (pk_copia_livro, pk_movimentacao) VALUES (2, 1),(5, 2);
