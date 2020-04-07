from random import randint
from time import sleep
print('-=-'*20)
print('Vou pensar em um número entre 0 e 5, tente adivinhar...')
print('-=-'*20)
n=int(input('Em que número pensei?: '))
print('PROCESSANDO...')
sleep(2)
ne=randint(0,5)
print('O número que eu pensei foi {}'.format(ne))
if ne==n:
    print('Parabéns! Você escolheu o número correto!')
else:
    print('Aha! Ganhei! Pensei no número {}, não no {}!'.format(ne,n))
print(('-=-'*9),'FIM',('-=-'*9))