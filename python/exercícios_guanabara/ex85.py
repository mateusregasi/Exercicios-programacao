lista = []
listapar = []
listaimpar = []

for c in range(0, 7):
    num = int(input(f'Digite o {c + 1}ª valor: '))
    if num % 2 == 0:
        listapar.append(num)
    else:
        listaimpar.append(num)


listapar.sort()
listaimpar.sort()
lista.append(listapar[:])
lista.append(listaimpar[:])

print(f'Os valores impares digitados foram: {lista[1]}')
print(f'Os valores pares digitados foram: {lista[0]}')