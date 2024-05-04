print('-=' * 20)
print('            Jogo Mega Cena')
print('-=' * 20)

from time import sleep
from random import randint
lista = []

numero_de_sorteios = int(input('Quantos quer que eu sorteie: '))
for c in range(0, numero_de_sorteios):
    for x in range(6):
        sorteados = randint(1, 60)
        while sorteados in lista:
            sorteados = randint(1, 60)
        lista.append(sorteados)
    sleep(0.5)
    lista.sort()
    print(f'Jogo {c + 1}: {lista}')
    lista.clear()

print('-=-=-=-=-=-=-=-Boa Sorte!=-=-=-=-=-=-=-=')