cont = 0
soma = 0

for c in range(1, 501, 2):
    if c % 3 == 0:
        cont += 1
        soma += c
print('Dos {} valores solicitados, a soma é {}'.format(cont, soma))