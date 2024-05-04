'''lista = []
for c in range(1, 6):
    n = int(input('Digite um valor: '))
    if c == 1 or n > lista[-1]:
        lista.append(n)
        print(f'O valor {n} foi colocado ultima posição da lista.')
    else:
        pos = 0
        while pos < len(lista):
            if n <= lista[pos]:
                lista.insert(pos, n)
                print(f'O número {n} foi colocado na posição {pos + 1} da lista.')
                break
            pos += 1
print('-=' * 20)
print(f'Os valores digitados em ordem foram {lista}')'''


num = []
for c in range(1, 6):
    n = int(input('Digite um número: '))
    if c == 1 or n > num[-1]:
        num.append(n)
        print(f'O número {n} foi adicionado no final da lista.')
    else:
        pos = 0
        while pos < len(num):
            if n <= num[pos]:
                num.insert(pos, n)
                print(f'O número {n} foi adicionado na posição {pos + 1}')
                break
            pos += 1
print('-=' * 20)
print(f'A lista dos números digitados em seguência é {num}')