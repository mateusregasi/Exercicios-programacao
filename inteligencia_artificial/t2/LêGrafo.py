# O objetivo desse código é enxergar a rede gerada pelo chat gpy

# Importa as bibliotecas para vizualização
import networkx as nx
import matplotlib.pyplot as pl
from random import randint

# Abre o arquivo
arquivo = 'export.txt'
edges = []
nodes = []
f = open(arquivo, 'r')
for l in f:
    if 'edge' in l:
        n = l[5:-3].split(',')
        edges.append((int(n[0]),int(n[1]),int(n[2])))
    elif l != '':
        n = l[5:-3].split(',')
        nodes.append((int(n[0]),int(n[1]),int(n[2])))
f.close()

print(edges)
print(nodes)

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