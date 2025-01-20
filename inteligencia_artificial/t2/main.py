# Imports
from pyswip import Prolog
import networkx as nx
import matplotlib.pyplot as pl

# Variáveis importantes
origem = 1
destino = 20
arquivo = 'export.pl'

# Executa a base de dados e as regras
Prolog.consult(arquivo)
Prolog.consult('main.pl')

# Pega o resultado
resultado = list(Prolog.query(f"caminho({origem},{destino},List)"))[0]['List']

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

# Pega o arquivo original
arestas = []
vertices = []
f = open(arquivo, 'r')
for l in f:
    if 'edge' in l:
        n = l[5:-3].split(',')
        arestas.append((int(n[0]),int(n[1]),int(n[2])))
    elif l != '':
        n = l[5:-3].split(',')
        vertices.append((int(n[0]),int(n[1]),int(n[2])))
f.close()

# Cria arestas a partir do caminho
arestas_resultado = []
for i in range(len(resultado)-1):
    arestas_resultado.append((resultado[i],resultado[i+1]))

# Cria o grafo
g = nx.Graph()
for n in vertices:
    g.add_node(n[0])
    g.nodes[n[0]]['pos'] = (n[1], n[2])
for e in arestas:
    g.add_edge(e[0], e[1], peso=e[2], color='tab:blue', weight=0.5)
pos = nx.get_node_attributes(g,'pos')

# Pinta as arestas do resultado
for a in arestas_resultado:
    g.edges[(a[0],a[1])]['color'] = 'tab:red'
    g.edges[(a[0],a[1])]['weight'] = 2

cor = [g.edges[(u,v)]['color'] for u,v in g.edges]
espessuras = [g.edges[(u,v)]['weight'] for u,v in g.edges]

# Printa o custo
print(custo(resultado, arestas))

# Desenha o grafo
nx.draw(g, pos, edge_color=cor, width=espessuras, with_labels=True, node_size=200)
pl.show()