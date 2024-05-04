f=input('Digite uma frase: ').strip()
print('A letra A apareceu {} vezes na frase.'.format(f.upper().count('A')))
print('A primeira letra A aparece na posição {}'.format(f.upper().find('A')+1))
print('A ultima letra A apareceu na posição {}'.format(f.upper().rfind('A')+1))