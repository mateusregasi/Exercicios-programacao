from random import randint

print('-=-' * 10)
print('------Jogo: PAR ou IMPAR------')
print('-=-' * 10)

ganhou = 0
perdeu = False

while perdeu != True:
    while True:
        escolha = input('Escolha PAR ou IMPAR: ').upper().strip()
        if escolha == 'PAR':
            jogador = 'PAR'
            pc = 'IMPAR'
            break
        elif escolha == 'IMPAR':
            jogador = 'IMPAR'
            pc = 'PAR'
            break
        else:
            print('\033[31mEscolha inválida. Tente novamente.\033[m')

    numjg = int(input('Escolha seu número: '))
    numpc = randint(0, 10)

    soma = numjg + numpc
    if soma % 2 == 0:
        resultado = 'PAR'
    else:
        resultado = 'IMPAR'

    print('-' * 20)
    print(f'Você jogou {numjg} e o computador {numpc}. Total de {soma} deu {resultado}')
    print('-' * 20)

    if jogador == resultado:
        ganhou += 1
        print('\033[36mVocê venceu! Vamos jogar novamente...', '\033[m')
    else:
        print('\033[31mQue pena... Você perdeu... \033[m ')
        perdeu = True
    print('-' * 20)

print(f'\033[31mGame over!\033[m \033[33mVocê ganhou \033[m\033[36m{ganhou}\033[m\033[33m vezes.\033[m')
