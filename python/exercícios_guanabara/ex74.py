from random import randint

n1 = randint(0, 1000)
n2 = randint(0, 1000)
n3 = randint(0, 1000)
n4 = randint(0, 1000)
n5 = randint(0, 1000)

sequencia = (n1, n2, n3, n4, n5)
sequenciaordem = sorted(sequencia)
maior = sequenciaordem[4]
menor = sequenciaordem[0]


print(f'A sequencia foi: ', end='')
for c, n in enumerate(sequencia):
    print(sequencia[c], end=' ')
print('')
print(f'O maior número foi {maior} e o menor número foi {menor}.')