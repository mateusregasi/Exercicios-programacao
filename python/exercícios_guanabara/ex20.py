from random import shuffle
a1=input('Primeiro aluno:')
a2=input('Segundo aluno:')
a3=input('Terceiro aluno:')
a4=input('Quarto aluno:')
o=[a1,a2,a3,a4]
shuffle(o)
print('A ordem se apresentação será: {}'.format(o))