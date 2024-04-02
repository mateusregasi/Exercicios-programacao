listapar = []
listaimpar = []
lista = []
escolha = ''

while True:
    n = int(input('Digite um valor: '))
    if n % 2 == 0:
        listapar.append(n)
        lista.append(n)
    if n % 2 == 1:
        listaimpar.append(n)
        lista.append(n)
    while True:
        escolha = input('Quer continuar? [S/N]: ').upper().strip()[0]
        if escolha == 'N':
            break
        if escolha == 'S':
            break
    if escolha == 'N':
        break

print(f'A lista foi: {lista}')
print(f'A lista de números pares é: {listapar}')
print(f'A lista de números impares é {listaimpar}')