n1 = int(input('Digite um valor(de 1 a 10): '))
n2 = int(input('Digite outro valor: '))
n3 = int(input('Digite outro valor: '))
n4 = int(input('Digite mais um valor: '))

lista = (n1, n2, n3 ,n4)
soma = 0
cont = 0
cont1 = 0
soma1 = 0

while True:
    if soma == 4:
        break
    else:
        if lista[soma] == 9:
            cont += 1
            soma += 1
        else:
            soma += 1

cond = False

for s in range(0, 4):
    if lista[s] == 3:
        cond = True
        break
    else:
        cond = False

print(f'Você digitou os valores {lista}')
print(f'O valor 9 apareceu {cont} vezes.')

if cond == True:
    print(f'O valor 3 apareceu na {lista.index(3) + 1}ª posição.')
else:
    print('O valor não foi digitado em nenhuma posição.')

while cont1 != 4:
    if lista[cont1] % 2 == 0:
        soma1 += 1
        cont1 += 1
    else:
        cont1 += 1

print(f'Os valores pares digitados foram {soma1}')