# O objetivo desse código é enxergar a rede gerada pelo chat gpy

# Importa as bibliotecas para vizualização
import networkx as nx
import matplotlib.pyplot as pl
from random import randint

# Gera o grafo
num_vertices = 20
num_arestas = 100
espaco = 100

def geraVertice(n, s):
    return (n, randint(1, s+1), randint(1, s+1))
def geraAresta(nv, n):
    n1 = n[randint(0,nv-1)]
    n2 = n1
    while n2 == n1:
        n2 = n[randint(0,nv-1)]
    return (n1[0], n2[0], int(abs((n2[1] - n1[1]) + (n2[2] - n1[2])) ** 0.5))

nodes = [geraVertice(i, espaco) for i in range(1, num_vertices+1)]
edges = [geraAresta(num_vertices, nodes) for _ in range(num_arestas)]

print(edges)

# Exporta o grafo em prolog
f = open("export.txt", 'w')
for n in nodes:
    f.write(f"node({n[0]},{n[1]},{n[2]}).\n")
for e in edges:
    f.write(f"edge({e[0]},{e[1]},{e[2]}).\n")
f.close()

# Cria o grafo
g = nx.Graph()
for n in nodes:
    g.add_node(n[0])
    g.nodes[n[0]]['pos'] = (n[1], n[2])
for e in edges:
    g.add_edge(e[0], e[1], peso=e[2])
pos = nx.get_node_attributes(g,'pos')

# Desenha o grafo
nx.draw(g, pos, with_labels=True, node_size=200)
pl.show()

print(g.edges)