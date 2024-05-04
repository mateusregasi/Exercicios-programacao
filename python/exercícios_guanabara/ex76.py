print('=' *50)
print('----------------Listagem de preços----------------')
print('=' *50)

pre = ('Lápis', 1.75, 'Borracha', 2, 'Caderno', 15.9, 'Estojo', 25, 'Transferidor', 4.2, 'Compasso', 9.99, 'Mochila', 120.32, 'Canetas', 22.3, 'Livro', 34.9)
quantpre = len(pre)
cont = 0

while True:
    print(pre[0 + cont], end='')
    print('-' * (40 - len(pre[0 + cont])), end='')
    cont += 1
    print(f'R${pre[0 + cont]:>8.2f}')
    cont += 1
    if cont == quantpre:
        break
print('=' * 50)