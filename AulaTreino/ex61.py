print('  Gerador de Pa')
print('=-=' * 6)
n = int(input('Primeiro termo: '))
r = int(input('Razão da PA: '))
cont = 1 #troquei 1 por 0
pa = n #troquei n por 0

while cont <= 10:
    print('{} → '.format(pa), end='') #troquei pa por p
    pa += r
    cont += 1

print('FIM')
