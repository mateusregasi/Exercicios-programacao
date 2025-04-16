# Entrada de dados
n = int(input())
vet = tuple([int(v) for v in input().split()])

# Processamento
vd = [0 for _ in range(n)]
md = 0

# Verificando os da direita 
for i in range(n-1, -1, -1):
    if vet[i] > md: md = vet[i]
    else: md += 1
    vd[i] = md

# Definindo o maior
maior = 0
for i in range(n-1):
    v = vet[i] + vd[i]
    if(maior < v): maior = v

# Saída de dados
print(maior)

# 14
# 2 3 1 6 4 3 7 5 6 4 5 3 1 1

# 6
# 1 1 4 3 1 2

# 2
# 1 1