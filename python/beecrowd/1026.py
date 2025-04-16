# https://judge.beecrowd.com/pt/problems/view/1026
from sys import stdin

# Função
def somador_errado(n1, n2):
    maior = list(n1) if len(n1) > len(n2) else list(n2)
    menor = list(n1) if len(n1) <= len(n2) else list(n2)
    d = len(maior) - len(menor)
    for i in range(len(menor)-1, -1, -1):
        if(menor[i] == maior[i+d]): maior[i+d] = '0'
        else: maior[i+d] = '1'
    return int("".join(maior), 2)


# Entrada de dados
for line in stdin:
    n1, n2 = [bin(int(n))[2:] for n in line.split()]
    
    # Saída de dados
    print(somador_errado(n1, n2))


# 4 6
# 6 9