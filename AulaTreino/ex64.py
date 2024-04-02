'''num = 0
cont = -1
soma = 0

while num != 999:
    num = int(input('Digite um número (999 para parar): '))
    cont += 1
    soma += num
print('Você digitou {} números e a soma entre eles foi {}.'.format(cont, soma - 999))'''

num = int(input('Digite um número (999 para parar): '))
cont = 0
soma = 0

while num != 999:
    cont += 1
    soma += num
    num = int(input('Digite um número (999 para parar): '))
print('Você digitou {} números e a soma entre eles foi {}.'.format(cont, soma))