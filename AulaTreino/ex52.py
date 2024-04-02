num = int(input('Digite um número: '))
cont = 0

for c in range(1, num + 1):
    if num % c == 0:
        print('\033[36m',c ,'\033[m', end=' ')
        cont += 1
    else:
        print('\033[31m', c,'\033[m', end=' ')
if cont == 2:
    print('')
    print('O número {} foi divisível {} vezes, portanto \033[36mé primo\033[m!'.format(num, cont))
elif cont > 2:
    print('')
    print('O número {} foi divisível {} vezes, portanto \033[31mnão é primo\033[m!'.format(num, cont))
else:
    print('')
    print('O número 1 foi divisivel uma vez, portanto \033[31mnão é primo\033[m!')