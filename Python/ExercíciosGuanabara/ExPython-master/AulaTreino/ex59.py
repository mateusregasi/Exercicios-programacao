n1 = int(input('Digite um valor: '))
n2 = int(input('Digite um segundo valor: '))
escolha = 0

while escolha != 5:
    print('''    [ 1 ] somar
    [ 2 ] multiplicar
    [ 3 ] maior
    [ 4 ] novos números
    [ 5 ] sair do programa ''')

    escolha = int(input('>>>>> Qual é sua escolha?: '))

    if escolha == 1:
        print('A soma entre {} e {} é {}'.format(n1, n2, n1 + n2))
        print('-=-' * 13)

    elif escolha == 2:
        print('O número {} vezes {} é igual a {}'.format(n1, n2, n1 * n2))
        print('-=-' * 13)

    elif escolha == 3:
        if n1 == n2:
            print('O número {} e o número {} são iguais.'.format(n1, n2))
        elif n1 > n2:
            print('Entre os números {} e {} o maior é o {}'.format(n1, n2, n1))
        else:
            print('Entre os números {} e {} o maior é {}'.format(n1, n2, n2))
        print('-=-' * 13)

    elif escolha == 4:
        print('Escolha os números novamente: ')
        n1 = int(input('Digite um valor: '))
        n2 = int(input('Digite um segundo valor: '))

    elif escolha == 5:
        print('Finalizando...')
    else:
        print('Opção inválida.')


print('Fim do programa, volte sempre!')