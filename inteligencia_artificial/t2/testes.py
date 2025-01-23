# Imports
from pyswip import Prolog
import networkx as nx
import matplotlib.pyplot as pl
from time import time
from random import randint

# Variáveis importantes
num_testes = 3
arquivo = 'export.pl'
num_vertices = 100
num_arestas = 150
espaco = 100

# Define função de custo
def custo(resultado, arestas):
        c = 0
        for i in range(len(resultado)-1):
            x = resultado[i]
            y = resultado[i+1]
            for a in arestas:
                if x == a[0] and y == a[1]:
                    c += a[2]
                    break
        return c

# Gera o grafo
def geraVertice(n, s):
    return (n, randint(1, s+1), randint(1, s+1))
def geraAresta(nv, n):
    n1 = n[randint(0,nv-1)]
    n2 = n1
    while n2 == n1:
        n2 = n[randint(0,nv-1)]
    return (n1[0], n2[0], int(abs((n2[1] - n1[1]) + (n2[2] - n1[2])) ** 0.5))

vertices = [geraVertice(i, espaco) for i in range(1, num_vertices+1)]
arestas = set()
while(len(arestas) != 2*num_arestas): 
    aresta = geraAresta(num_vertices, vertices)
    arestas.add(aresta)
    arestas.add((aresta[1], aresta[0], aresta[2]))

# Exporta o grafo em prolog
f = open(arquivo, 'w')
for n in vertices:
    f.write(f"node({n[0]},{n[1]},{n[2]}).\n")
for e in arestas:
    f.write(f"edge({e[0]},{e[1]},{e[2]}).\n")
f.close()

# Executa a base de dados e as regras
Prolog.consult(arquivo)
Prolog.consult('main.pl')
Prolog.consult('busca_profunda.pl')

# Cria a base de dados para os testes
def geraTeste(nv, n):
    n1 = n[randint(0,nv-1)]
    n2 = n1
    while n2 == n1:
        n2 = n[randint(0,nv-1)]
    return (n1[0], n2[0])

teste = set()
while(len(teste) != num_testes): 
    teste.add(geraTeste(num_vertices, vertices))

media_tempo_as = 0
media_tempo_bp = 0
media_custo_as = 0
media_custo_bp = 0
for i in range(len(teste)):

    # Define origem e destino
    t = teste.pop()
    origem = t[0]
    destino = t[1]

    # Pega o resultado do A-Star
    inicio_as = time()
    resultado_as = list(Prolog.query(f"caminho({origem},{destino},List)"))[0]['List']
    fim_as = time()

    # Pega o resultado do A-Star
    inicio_bp = time()
    resultado_bp = list(Prolog.query(f"caminho_bp({origem},{destino},List)"))[0]['List']
    fim_bp = time()

    #  Calcula resultados
    tempo_as = fim_as - inicio_as
    tempo_bp = fim_bp - inicio_bp
    custo_as = custo(resultado_as, arestas)
    custo_bp = custo(resultado_bp, arestas)
    media_tempo_as += tempo_as
    media_tempo_bp += tempo_bp
    media_custo_as += custo_as
    media_custo_bp += custo_bp

    # Printa o e o tempo de execução
    # print('-' * 20)
    # print("A-Star:")
    # print("Caminho percorrido: ", resultado_as)
    # print("Distância percorrida: ", custo_as)
    # print(f"Tempo de execução do algoritmo: {tempo_as:.10f}")
    # print("Busca-Profunda:")
    # print("Caminho percorrido: ", resultado_bp)
    # print("Distância percorrida: ", custo_bp)
    # print(f"Tempo de execução do algoritmo: {tempo_bp:.10f}")
    # print('-' * 20)
media_tempo_as /= num_testes
media_tempo_bp /= num_testes
media_custo_as /= num_testes
media_custo_bp /= num_testes

# Mostra o resultado
print(f"Foram feitas {num_testes} iterações com {num_vertices} vértices e {num_arestas}, aqui está o resultado:")
print("Média do custo (AS): ", media_custo_as)
print(f"Média do rempo (AS): {media_tempo_as:.10f}")
print("Média do custo (BP): ", media_custo_bp)
print(f"Média do rempo (BP): {media_tempo_bp:.10f}")