from random import choice
from time import sleep

for c in range(1000000):
    print('\033[0;33;0m-=-' * 10, '\033[m')
    print(('\033[0;36;0m-' * 2), 'Pedra, Papel e tesoura!', ('-' * 2), '\033[m')
    print('\033[0;33;0m-=-' * 10, '\033[m')
    print('''Suas opções:
[ pedra ] 
[ papel ] 
[ tesoura ] ''')
    jogada = input('Qual é a sua jogada? ').strip()

    lista = ['pedra', 'papel', 'tesoura']

    print('JO')
    sleep(1)
    print('KEN')
    sleep(1)
    print('PO!!!!')
    sleep(1)

    com = choice(lista)

    print('-=-' * 10)
    if jogada == com:
        print('O computador jogou {}.'.format(com))
        print('O jogador jogou {}'.format(jogada))
        print('-=-' * 10)
        print('\033[0;33;0mDeu impate.\033[m')
    elif jogada == 'pedra' and com == 'tesoura' or jogada == 'tesoura' and com == 'papel' or jogada == 'papel' and com == 'pedra':
        print('O computador jogou {}'.format(com))
        print('O jogador jogou {}'.format(jogada))
        print('-=-' * 10)
        print('\033[0;36;0mO jogador ganhou!\033[m')
    else:
        print('O computador jogou {}'.format(com))
        print('O jogador jogou {}'.format(jogada))
        print('-=-' * 10)

        print('\033[0;31;0mO computador ganhou!\033[m')
    sleep(5)