# https://judge.beecrowd.com/pt/problems/view/2209

# Traduzindo o problema:
# Você é um agente secreto que precisa acabar com Association of Chaos and Mischief (ACM). Ela funciona por meio de células (grupos), que controlam outros grupos. Como você vai acabar com a ACM? Tomando controle de células que controlem as outras. Precisamos encontrar o menor número de células que, ao serem controladas, possa acabar com a ACM.

# Entrada:
# n -> número de células da ACM
# matriz NxN onde cada posição ij significa que j controla i

# Saída:
# Case n: num a0 ... anum
# Onde n é o número de casos, num é o numero de células que vão ser infiltradas e a0 ... anum são as células que serão infiltradas.

# from array import array 
# from sys import stdin

# it = 0
# for l in stdin:
#     it += 1
    
#     # Lê a matriz
#     n = int(l)
#     mat = ([array('h', [0 for _ in range(n)]) for _ in range(n)])
#     for i in range(n):
#         line = input()
#         for j in range(len(line)):
#             mat[i][j] = int(line[j])

#     valores_achados = set()
#     linhas_usadas = []

#     # Enquanto o número de colunas achadas nao for igual a n
#     while len(valores_achados) != n:

#         # 1) Acha a linha com mais valores nao preenchidos
#         # Obs: pula as colunas ja achadas
#         # Obs: pula as linhas já achadas
#         maior = 0
#         linha_maior = 0
#         for i in range(n):
#             if i in linhas_usadas: continue

#             # Soma os valores que não foram compreendidos ainda 
#             s = 0
#             for j in range(n):
#                 if mat[i][j] == 0 or j in valores_achados: continue
#                 s += 1
            
#             # Atualiza o maior pegando a primeiro ocorrência
#             if s > maior:
#                 maior = s
#                 linha_maior = i
        
#         # 3) Adiciona as linhas e colunas em linhas usadas e valores achados
#         linhas_usadas.append(linha_maior)
#         valores_achados.add(linha_maior)
#         for j in range(n):
#             if mat[linha_maior][j] == 1: valores_achados.add(j)
        
#     # Saída de dados
#     linhas_usadas.sort()
#     print(f'Case {it}: {len(linhas_usadas)}', *map(lambda a : a+1, linhas_usadas), sep=" ")

from sys import stdin
from array import array

it = 0
for line in stdin:
    it += 1
    
    # Leitura de dados
    n = int(line)
    sets = [{i} for i in range(n)]
    for i in range(n):
        line = input()
        for j in range(len(line)):
            if line[j] == '1': sets[i].add(j)     

    # Usando fila: Adiciona (dominados_pelo_agente, dominados_total)
    # Puxa o primeiro elemento, cria as ramificações
    # Se uma ramificação atende ao requisito, ela é a resposta, se não continua procurando
    res = None
    queue = [(set(),set())]
    while True:
        # Pega o primeiro elemento na fila
        item = queue.pop(0)

        for

    # Saída de dados
    print(f'Case {it}: {len(res)}', *map(lambda a : a+1, res), sep=" ")






# 2
# 00
# 10
# 3
# 010
# 001
# 100
# 5
# 01000
# 00011
# 11001
# 10100
# 10010