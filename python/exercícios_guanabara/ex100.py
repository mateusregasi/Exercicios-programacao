from random import randint

def somaPar(lista):
    soma_pares = 0
    for c in lista:
        if c % 2 == 0:
            soma_pares += c
    print(f'Somando os valores pares de {lista}, temos {soma_pares}')
def sorteioDeCinco():
    lista1 = []
    print('Sorteando 5 valores da lista: ', end='')
    for c in range(0, 5):
        sorteado = randint(0, 10)
        lista1.append(sorteado)
        print(sorteado, end=' ')
    print('PRONTO!')
    somaPar(lista1)

sorteioDeCinco()


