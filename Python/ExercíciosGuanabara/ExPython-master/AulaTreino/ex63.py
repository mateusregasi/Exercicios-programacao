print('=-=' * 10)
print(' ===Sequência de Fibonacci===')
print('=-=' * 10)
print('~~~' * 10)

n0 = 0
n1 = 1
n2 = 0
cont = 0

num = int(input('Quantos termos você quer mostrar?: '))
print('0→', end='')
if num > 1:
    print('1→', end='')
    if num > 2:
        while cont <= num:
            n2 = n0 + n1
            n0 = n1
            n1 = n2
            cont += 1
            print('{}→'.format(n1), end='')


print('FIM')
print('~~~' * 10)