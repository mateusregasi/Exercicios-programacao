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
drop schema if exists biblio cascade;

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
    constraint pk_copia_livro PRIMARY KEY(pk),
    constraint fk_livro FOREIGN KEY(pk_livro) REFERENCES biblio.Livro(pk),
    constraint fk_biblioteca FOREIGN KEY(pk_biblioteca) REFERENCES biblio.Biblioteca(pk)
);
CREATE TABLE biblio.Emprestimo (
    pk SERIAL,
    pk_cliente INTEGER ,
    pk_copia_livro INTEGER,
    data_retirada DATE NOT NULL,
    data_entrega DATE,
    data_prevista DATE not null,
    constraint pk_emprestimo PRIMARY KEY(pk),
    constraint fk_cliente FOREIGN KEY(pk_cliente) REFERENCES biblio.Cliente(pk),
    constraint fk_copia_livro FOREIGN KEY(pk_copia_livro) REFERENCES biblio.CopiaLivro(pk)
);
CREATE TABLE biblio.AgendamentoMovimentacao (
    pk SERIAL,
    pk_origem int,
    pk_destino int,
    data_saida DATE,
    data_entrega DATE,
    data_prevista DATE,
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
-- Inserir Autores
INSERT INTO biblio.Autor (nome) VALUES 
('J.K. Rowling'),
('George R.R. Martin'),
('J.R.R. Tolkien'),
('Agatha Christie');

-- Inserir Gêneros
INSERT INTO biblio.Genero (nome) VALUES 
('Fantasia'),
('Mistério'),
('Aventura'),
('Ficção Científica');

-- Inserir Clientes
INSERT INTO biblio.Cliente (nome) VALUES 
('Ana Silva'),
('Bruno Costa'),
('Carlos Souza');

-- Inserir Bibliotecas
INSERT INTO biblio.Biblioteca (cidade_estado) VALUES 
('São Paulo - SP'),
('Rio de Janeiro - RJ'),
('Curitiba - PR');

-- Inserir Livros
INSERT INTO biblio.Livro (isbn, titulo, num_paginas, pk_genero) VALUES 
('9780747532743', 'Harry Potter e a Pedra Filosofal', 223, 1),
('9780553103540', 'A Guerra dos Tronos', 694, 1),
('9780261103573', 'O Senhor dos Anéis', 1178, 3),
('9780007119356', 'Assassinato no Expresso do Oriente', 256, 2);

-- Inserir LivroAutor
INSERT INTO biblio.LivroAutor (pk_livro, pk_autor) VALUES 
(1, 1), -- Harry Potter -> Rowling
(2, 2), -- Guerra dos Tronos -> Martin
(3, 3), -- Senhor dos Anéis -> Tolkien
(4, 4); -- Expresso Oriente -> Christie

-- Inserir Cópias de Livros nas Bibliotecas
INSERT INTO biblio.CopiaLivro (pk_livro, pk_biblioteca) VALUES 
(1, 1),
(2, 1),
(3, 2),
(4, 3),
(1, 2),
(2, 3);

-- Inserir Empréstimos
INSERT INTO biblio.Emprestimo (pk_cliente, pk_copia_livro, data_retirada, data_prevista, data_entrega) VALUES 
(1, 1, '2025-05-01', '2025-05-15', '2025-05-10'),
(2, 2, '2025-05-03', '2025-05-17', NULL),
(3, 3, '2025-04-25', '2025-05-09', '2025-05-08');

-- Inserir Agendamento de Movimentações
INSERT INTO biblio.AgendamentoMovimentacao (pk_origem, pk_destino, data_saida, data_prevista, data_entrega) VALUES 
(1, 2, '2025-05-01', '2025-05-03', '2025-05-02'),
(3, 1, '2025-05-05', '2025-05-08', NULL);

-- Inserir Cópias nas Movimentações
INSERT INTO biblio.CopiaMovimentacao (pk_copia_livro, pk_movimentacao) VALUES 
(5, 1), -- Cópia do livro 1 de SP para RJ
(6, 2); -- Cópia do livro 2 de Curitiba para SP
-- Mais Autores
INSERT INTO biblio.Autor (nome) VALUES 
('Clarice Lispector'),
('Machado de Assis'),
('Cecília Meireles'),
('Monteiro Lobato'),
('Paulo Coelho');

-- Mais Gêneros
INSERT INTO biblio.Genero (nome) VALUES 
('Drama'),
('Romance'),
('Infantil'),
('História'),
('Biografia');

-- Mais Clientes
INSERT INTO biblio.Cliente (nome) VALUES 
('Eduarda Martins'),
('Fernanda Lima'),
('Gustavo Andrade'),
('Helena Rocha'),
('Igor Vasconcelos');

-- Mais Bibliotecas
INSERT INTO biblio.Biblioteca (cidade_estado) VALUES 
('Belo Horizonte - MG'),
('Porto Alegre - RS');

-- Mais Livros
INSERT INTO biblio.Livro (isbn, titulo, num_paginas, pk_genero) VALUES 
('9788535914849', 'O Alquimista', 208, 6),
('9788595081512', 'Dom Casmurro', 256, 7),
('9788535902778', 'A Hora da Estrela', 87, 6),
('9788516075651', 'Reinações de Narizinho', 240, 8),
('9788525058524', 'Memórias de um Sargento de Milícias', 192, 7);

-- LivroAutor extra
INSERT INTO biblio.LivroAutor (pk_livro, pk_autor) VALUES 
(5, 5), -- O Alquimista -> Paulo Coelho
(6, 6), -- Dom Casmurro -> Machado de Assis
(7, 1), -- A Hora da Estrela -> Clarice Lispector
(8, 8), -- Reinações -> Monteiro Lobato
(9, 6); -- Memórias de um Sargento -> Machado de Assis

-- Cópias adicionais
INSERT INTO biblio.CopiaLivro (pk_livro, pk_biblioteca) VALUES 
(5, 4),
(6, 5),
(7, 5),
(8, 4),
(9, 2);

-- Movimentações adicionais
INSERT INTO biblio.AgendamentoMovimentacao (pk_origem, pk_destino, data_saida, data_prevista, data_entrega, entregue) VALUES 
(2, 5, '2025-05-01', '2025-05-03', '2025-05-02', TRUE),
(4, 3, '2025-05-06', '2025-05-08', NULL, FALSE);
-- Mais livros adicionados com diferentes gêneros
INSERT INTO biblio.Livro (isbn, titulo, num_paginas, pk_genero) VALUES 
('9780143127741', '1984', 328, 4),  -- Ficção Científica
('9780061122415', 'O Sol é para Todos', 336, 5),  -- Biografia
('9788520922592', 'Quincas Borba', 220, 7), -- Romance
('9788580442314', 'Os Miseráveis', 1463, 6), -- Drama
('9788574067309', 'O Pequeno Príncipe', 96, 9); -- Infantil

-- Associando autores aos novos livros
INSERT INTO biblio.Autor (nome) VALUES 
('George Orwell'),
('Harper Lee'),
('Victor Hugo');

-- Observar o último autor inserido já existente: Machado de Assis = (id: 6, usado em Quincas Borba)
-- Supondo que os novos IDs sejam consecutivos
INSERT INTO biblio.LivroAutor (pk_livro, pk_autor) VALUES 
(10, 10), -- 1984 -> Orwell
(11, 11), -- O Sol é para Todos -> Harper Lee
(12, 6),  -- Quincas Borba -> Machado
(13, 12), -- Os Miseráveis -> Victor Hugo
(14, 8);  -- O Pequeno Príncipe -> Saint-Exupéry (associado como autor fictício 8)

-- Adicionando bibliotecas em outras cidades
INSERT INTO biblio.Biblioteca (cidade_estado) VALUES 
('Fortaleza - CE'),
('Manaus - AM');

-- Inserindo cópias dos livros recém-adicionados em diferentes bibliotecas
INSERT INTO biblio.CopiaLivro (pk_livro, pk_biblioteca) VALUES 
(10, 6), -- 1984 em Porto Alegre
(11, 4), -- O Sol é para Todos em BH
(12, 1), -- Quincas Borba em SP
(13, 2), -- Os Miseráveis em Fortaleza
(14, 1); -- O Pequeno Príncipe em Manaus

-- Clientes adicionais
INSERT INTO biblio.Cliente (nome) VALUES 
('Joana Prado'),
('Luiz Felipe'),
('Mariana Ribeiro'),
('Nicolas Torres'),
('Patrícia Almeida');

-- Empréstimos de livros recém-adicionados
INSERT INTO biblio.Emprestimo (pk_cliente, pk_copia_livro, data_retirada, data_prevista, data_entrega) VALUES 
(4, 7, '2025-05-10', '2025-05-24', NULL), -- Carlos empresta 1984
(5, 8, '2025-05-12', '2025-05-26', '2025-05-22'), -- Eduarda empresta O Sol é para Todos
(6, 9, '2025-05-08', '2025-05-22', NULL), -- Fernanda empresta Quincas Borba
(7, 10, '2025-05-15', '2025-05-29', NULL), -- Gustavo empresta Os Miseráveis
(8, 11, '2025-05-14', '2025-05-28', NULL); -- Helena empresta O Pequeno Príncipe

-- Movimentações das novas cópias
INSERT INTO biblio.AgendamentoMovimentacao (pk_origem, pk_destino, data_saida, data_prevista, data_entrega, entregue) VALUES 
(6, 3, '2025-05-10', '2025-05-12', '2025-05-12', TRUE),
(7, 1, '2025-05-14', '2025-05-16', NULL, FALSE);

    -- Relacionando cópias com movimentações
INSERT INTO biblio.CopiaMovimentacao (pk_copia_livro, pk_movimentacao) VALUES 
(10, 3), -- 1984 (PA → Curitiba)
(11, 4); -- O Sol é para Todos (Fortaleza → SP)

INSERT INTO biblio.Emprestimo (pk_cliente, pk_copia_livro, data_retirada, data_prevista, data_entrega) VALUES
(1, 1, '2025-05-04', '2025-05-18', NULL),
(2, 2, '2025-05-06', '2025-05-20', NULL),
(3, 3, '2025-05-08', '2025-05-22', '2025-05-21'),
(4, 4, '2025-05-10', '2025-05-24', NULL),
(5, 5, '2025-05-11', '2025-05-25', '2025-05-20'),
(6, 6, '2025-05-12', '2025-05-26', NULL),
(7, 7, '2025-05-13', '2025-05-27', NULL),
(8, 8, '2025-05-14', '2025-05-28', NULL),
(9, 9, '2025-05-15', '2025-05-29', NULL),
(10, 10, '2025-05-16', '2025-05-30', NULL),
(11, 11, '2025-05-17', '2025-05-31', NULL),
(12, 12, '2025-05-18', '2025-06-01', NULL),
(13, 13, '2025-05-19', '2025-06-02', NULL),
(1, 2, '2025-05-05', '2025-05-19', '2025-05-18'),
(2, 3, '2025-05-06', '2025-05-20', NULL),
(3, 4, '2025-05-07', '2025-05-21', '2025-05-17'),
(4, 5, '2025-05-08', '2025-05-22', NULL),
(5, 6, '2025-05-09', '2025-05-23', NULL),
(6, 7, '2025-05-10', '2025-05-24', NULL),
(7, 8, '2025-05-11', '2025-05-25', NULL),
(8, 9, '2025-05-12', '2025-05-26', NULL),
(9, 10, '2025-05-13', '2025-05-27', NULL),
(10, 11, '2025-05-14', '2025-05-28', NULL),
(11, 12, '2025-05-15', '2025-05-29', NULL),
(12, 13, '2025-05-16', '2025-05-30', NULL),
(13, 1, '2025-05-17', '2025-05-31', NULL),
(1, 3, '2025-05-04', '2025-05-18', '2025-05-14'),
(2, 4, '2025-05-05', '2025-05-19', '2025-05-18'),
(3, 5, '2025-05-06', '2025-05-20', NULL),
(4, 6, '2025-05-07', '2025-05-21', NULL),
(5, 7, '2025-05-08', '2025-05-22', NULL),
(6, 8, '2025-05-09', '2025-05-23', NULL),
(7, 9, '2025-05-10', '2025-05-24', NULL),
(8, 10, '2025-05-11', '2025-05-25', NULL),
(9, 11, '2025-05-12', '2025-05-26', NULL),
(10, 12, '2025-05-13', '2025-05-27', NULL),
(11, 13, '2025-05-14', '2025-05-28', NULL),
(12, 1, '2025-05-15', '2025-05-29', NULL),
(13, 2, '2025-05-16', '2025-05-30', NULL),
(1, 4, '2025-05-03', '2025-05-17', '2025-05-10'),
(2, 5, '2025-05-04', '2025-05-18', NULL),
(3, 6, '2025-05-05', '2025-05-19', NULL),
(4, 7, '2025-05-06', '2025-05-20', NULL),
(5, 8, '2025-05-07', '2025-05-21', NULL),
(6, 9, '2025-05-08', '2025-05-22', NULL),
(7, 10, '2025-05-09', '2025-05-23', NULL),
(8, 11, '2025-05-10', '2025-05-24', NULL),
(9, 12, '2025-05-11', '2025-05-25', NULL),
(10, 13, '2025-05-12', '2025-05-26', NULL);
