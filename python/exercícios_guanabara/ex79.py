num = []
escolha = ''

while escolha != 'N':
    g = int(input('Escolha um número: '))
    if g in num:
        print('Valor duplicado! não vou adicionar...')
    else:
        num.append(g)
        print('Valor adicionado com sucesso...')
    escolha = input('Quer continuar? [S/N]: ').upper().strip()[0]

num.sort()
print(f'Você digitou os valores: {num}')