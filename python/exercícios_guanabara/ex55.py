maior = 0
menor = 0

for c in range(1, 6):
    peso = int(input('Peso da {}ª pessoa: '.format(c)))
    if c == 1:
        maior = peso
        menor = peso
    else:
        if peso > maior:
            maior = peso
        elif peso < menor:
            menor = peso

print('O maior peso lido foi {:.1f}kg.'.format(maior))
print('O menor peso lido foi {:.1f}kg.'.format(menor))