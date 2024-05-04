lista = []
apagavel = []
par = 0

for c in range(0, 9):
    num = int(input(f'Digite um número para posição {c + 1}: '))
    if num % 2 == 0:
        par += num
    apagavel.append(num)
    lista.append(apagavel[:])
    apagavel.clear()

soma = lista[6][0] + lista[7][0] + lista[8][0]
maior = max(lista[3][0], lista[4][0], lista[5][0])

print('', lista[0], lista[1], lista[2],'\n', lista[3], lista[4], lista[5], '\n', lista[6], lista[7], lista[8])
print(f'A soma dos valores pares digitados é {par}.')
print(f'A soma dos valores da 3ª linha é {soma}.')
print(f'O maior valor da segunda linha é {maior}.')