'''num = list()

for c in range(0, 5):
    num.append(int(input('Difite um número: ')))
print('^^' * 15)

maior = max(num)
menor = min(num)

print(f'Você digitou os valores: {num}')
print(f'O maior número foi {maior} e está na/s posição/ões: ', end='')
for b, c in enumerate(num):
    if c == maior:
        print(f'...{b + 1}', end='')
print()
print(f'O menor número foi {menor} e está na/s posição/ões: ', end='')
for b, c in enumerate(num):
    if c == menor:
        print(f'...{b + 1}', end='')
print('')'''

lista = []

for c in range(1,6):
    num = int(input(f'Digite um número para posição {c}: '))
    lista.append(num)

maiornumero = max(lista)
menornumero = min(lista)
quantosmaiores = lista.count(maiornumero)
quantosmenores = lista.count(menornumero)
cont1 = 0
cont2 = 0
maiornumeromais = []
menornumeromais = []


print(f'Você digitou os valores {lista}')

if quantosmaiores == 1:
    print(f'O menor número é {maiornumero} e está na posição {lista.index(maiornumero) + 1}')
else:
    for g in lista:
        if g == maiornumero:
            cont1 += 1
            maiornumeromais.append(cont1)
        else:
            cont1 += 1
    print(f'O maior número é {maiornumero} e está nas posições {maiornumeromais}')

if quantosmenores == 1:
    print(f'O menor número é {menornumero} e está na posição {lista.index(menornumero) + 1}')
else:
    for m in lista:
        if m == menornumero:
            cont2 += 1
            menornumeromais.append(cont2)
        else:
            cont2 += 1
    print(f'O menor número é {menornumero} e está nas posições {menornumeromais}')