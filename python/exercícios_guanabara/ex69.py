cont18 = 0
conth = 0
contm20 = 0
escolha = ''
sexo = ''

while True:
    print('-' * 20)
    print('Cadastre uma pessoa:')
    print('-' * 20)
    idade = int(input('Idade: '))
    sexo = ''
    escolha = ''
    while sexo != 'M' and sexo != 'F':
        sexo = input('Sexo (M/F): ').upper().strip()[0]
        if sexo != 'M' and sexo != 'F':
            print('Comando inválido. Tente novamente.')
    print('-' * 20)

    if idade > 18:
        cont18 += 1
    elif sexo == 'M':
        conth += 1
    elif sexo == 'F' and idade < 20:
        contm20 += 1

    while escolha != 'S':
        escolha = input('Quer continuar? [S/N]: ').upper().strip()[0]
        if escolha == 'N':
            break
        if escolha != 'S':
            print('Comando inválido. Tente novamente.')
    if escolha == 'N':
        break

print(f'Foram listados {cont18} pessoas com mais de 18 anos.')
print(f'{conth} homens foram cadastrados.')
print(f'Foram listadas também {contm20} mulheres menores de 20 anos.')