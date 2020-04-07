media = 0
idademaior = 0
homemmaior = 0
contmeninas = 0

for c in range(1, 5):
    print('----- {} PESSOA -----'.format(c))
    nome = input('Nome: ').capitalize().strip()
    idade = int(input('Idade: '))
    sexo = input('Sexo [M/F]: ')
    media += idade

    if sexo in 'Mm':
        if c == 1:
            idademaior = idade
            homemmaior = nome
        else:
            if idade > idademaior:
                idademaior = idade
                homemmaior = nome

    if sexo in 'Ff' and idade < 20:
        contmeninas += 1

mediadogrupo = media / 4

print('A média de idade do grupo é de {} anos'.format(mediadogrupo))
print('O homem mais velho tem {} anos e se chama {}.'.format(idademaior, homemmaior))
print('Ao todo são {} mulheres com menos de 20 anos.'.format(contmeninas))