num = int(input('Digite um número inteiro: '))

print('Escolha uma das bases para conversão:')
print('[ 1 ] converter para BINÁRIO')
print('[ 2 ] converter para OCTAL')
print('[ 3 ] converter para HEXADECIMAL')

escolha = int(input('Sua opção: '))

if escolha == 1:
    print('{} convertido para binário é igual a {}'.format(num,bin(num)[2:]))
elif escolha == 2:
    print('{} con1vertido para OCTAL é igual a {}'.format(num,oct(num)[2:]))
elif escolha == 3:
    print('{} convertido para HEXADECIMAL é igual a {}'.format(num,hex(num)[2:]))
else:
    print('Opção inválida, tente novamente!')