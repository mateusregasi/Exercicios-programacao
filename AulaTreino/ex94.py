from funcoes import mostrarLinha

cont = 0
soma_idade = 0
lista_de_pessoas = []
mulheres = []

while True:

    pessoa = {}
    while True:
        pessoa['nome'] = input('Nome: ').strip().title()
        if pessoa['nome'].isalpha() == True:
            break
        else:
            print("Erro! Digite corretamente!")
    while True:
        pessoa['sexo'] = input('Sexo[M ou F]: ')[0].upper()
        if pessoa['sexo'] == 'F' or pessoa['sexo'] == 'M':
            break
        else:
            print("Erro! Digite corretamente!")
    while True:
        pessoa['idade'] = int(input('Idade: '))
        if pessoa['idade'] > 0:
            break
        else:
            print("Erro! Digite corretamente!")

    lista_de_pessoas.append(pessoa)
    cont += 1
    soma_idade += pessoa['idade']
    if pessoa['sexo'] == 'F':
        mulheres.append(pessoa['nome'])

    while True:
        escolha = input('Quer continuar?[S/N]: ')[0].upper()
        if escolha == 'S' or escolha == 'N':
            break
        else:
            print("Erro! Digite corretamente!")
    if escolha == 'N':
        break
cont2 = 0
mostrarLinha(40)

print(f'A) Ao todo temos {cont} pessoas cadastradas.')

media = soma_idade / cont
print('B) A média de idade é de {:.2f}'.format(media))

if mulheres == []:
    print('C) Não houve nenhuma mulher cadastrada.')
else:
    print('C) As mulheres cadastradas foram: ', end='')
    for c in mulheres:
        if cont2 == 0:
            print(f'{c}', end='')
        else:
            print(f', {c}', end='')
        cont2 += 1
print('')

print('D) Lista das pessoas que estão acima da média de idade: ')
for p in lista_de_pessoas:
    if p['idade'] > media:
        for k, v in p.items():
            print(f' {k} = {v}', end=';')
        print('')

print('Encerrado!!!')