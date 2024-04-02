'''from math import factorial
num = int(input('Digite um número para calcular seu Fatorial: '))
fac = factorial(num)

print('Calculando {}! = '.format(num), end='')

for c in range(0, num):
    conta = num - c
    if c == num - 1:
        print(conta, end='= ')
    else:
        print(conta, end=' x ')

print(fac)'''


'''from math import factorial
n = int(input('Digite um número para calcular seu Fatorial: '))
f = factorial(n)
print('O fatorial de {} é {}'.format(n, f))'''


n = int(input('Digite um número para calcular se Fatorial: '))
c = n
f = 1

print('Calculando {}! = '.format(n), end='')
while c > 0:
    print('{}'.format(c), end='')
    print(' x ' if c > 1 else '= ', end='')
    f *= c
    c -= 1
print(f)
