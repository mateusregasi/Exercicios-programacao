'''from random import randint
from time import sleep
numpc = randint(0, 10)
cont = 1

print('Sou seu computador...')
sleep(1)
print('Acabei de pensar em um número entre 0 e 10.')
sleep(1)
print('Será que você consegue adivinhar qual foi?')
sleep(1)
numjg = int(input('Qual é o seu palpite? '))

if numjg == numpc:
    print('Que sorte! Você adivinhou o número em uma tentativa!')
else:
    while numpc != numjg:
        if numpc > numjg:
            numjg = int(input('Mais... tente novamente: '))
            cont += 1
        else:
            numjg = int(input('Menos... Tente novamente: '))
            cont += 1
    print('Acertou em {} tentativas!'.format(cont))'''

from random import randint
from time import sleep
numpc = randint(0, 10)
cont = 0
acertou = False

print('Sou seu computador...')
sleep(1)
print('Acabei de pensar em um número entre 0 e 10.')
sleep(1)
print('Será que você consegue adivinhar qual foi?')
sleep(1)

while not acertou:
    numjg = int(input('Qual é o seu palpite? '))
    cont += 1
    if numpc == numjg:
        acertou = True
    else:
        if numpc > numjg:
            print('Mais... Tente mais uma vez.', end='')
        elif numpc < numjg:
            print('Menos... Tente mais uma vez.', end='')
print('Você acertou com {} tentativas. Parabéns!'.format(cont))