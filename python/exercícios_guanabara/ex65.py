num = 0
op = ''
contnum = 0
cont = 0
maior = num
menor = num

while op != 'N':
    num = int(input('Digite um número: '))
    op = input('Quer coninuar? [S/N]: ').upper()
    cont += 1
    contnum += num
    if num > maior:
        maior = num
    else:
        menor = num

print('Você digitou {} números e a média foi {:.2f}'.format(cont, contnum / cont))
print('O maior valor foi {} e o menor foi {}'.format(maior, menor))