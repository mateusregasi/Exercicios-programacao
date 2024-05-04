from random import randint
from time import sleep
from funcoes import mostrarLinha

jogadores = {'Jogaror1' : 0, 'Jogador2' : 0, 'Jogador3' : 0, 'Jogador4' : 0}
for k, v in jogadores.items():
    jogadores[k] = randint(1, 6)
    print(f'O {k} tirou {jogadores[k]}')
    sleep(1)

mostrarLinha(20)
print('     RESULTADO     ')
mostrarLinha(20)

for c in range(1, 5):
    maior = -1
    for v1 in jogadores.values():
        if maior < v1:
            maior = v1
    for k1, v2 in jogadores.items():
        if v2 == maior:
            print(f'{c}º lugar {k1} com {maior} pontos')
            jogadores[k1] = -1
            sleep(1)
            break