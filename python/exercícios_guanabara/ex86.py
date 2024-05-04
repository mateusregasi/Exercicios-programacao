lista = []
apagavel = []

for c in range(0, 9):
    num = int(input(f'Digite um número para posição {c + 1}: '))
    apagavel.append(num)
    lista.append(apagavel[:])
    apagavel.clear()
print('', lista[0], lista[1], lista[2],'\n', lista[3], lista[4], lista[5], '\n', lista[6], lista[7], lista[8])