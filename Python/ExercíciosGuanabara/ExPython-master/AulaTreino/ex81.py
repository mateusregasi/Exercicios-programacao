lista = []
cont = 0
escolha = ''

while True:
    add = lista.append(int(input('Digite um valor: ')))
    cont += 1
    while True:
        escolha = input('Quer continuar? [S/N]: ').strip().upper()[0]
        if escolha == 'N':
            break
        if escolha == 'S':
            break
    if escolha == 'N':
        break

print(f'Foram digitados ao todo {cont} números.')
lista.sort(reverse = True)
print(f'A lista em ordem decrescente: {lista}')
if 5 in lista:
    print(f'O número 5  foi digitado.')
else:
    print('O número 5 não foi digitado.')