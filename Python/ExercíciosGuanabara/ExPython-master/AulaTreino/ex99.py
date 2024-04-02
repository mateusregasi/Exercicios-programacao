from time import sleep


def analise(*num):
    numero_de_num = len(num)
    print('Analisando os valores passados...')
    cont = 0
    for c in num:
        print(c, end=' ')
        if cont == 0:
            maior = c
        elif maior < c:
            maior = c
        cont += 1
        sleep()

    print(f'Foram informados {cont} valores ao todo.')
    print(f'O maior valor informado foi {maior}')


analise(2, 9, 4, 5, 7, 1)



