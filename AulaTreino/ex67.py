cont = 0

print('-=' * 20)
print('========AQUELA TABUADINHA 10/10========')
print('-=' * 20)

while True:

    num = int(input('Digite um número para ver sua tabuada: '))
    print('=-=' * 13)
    if num < 0:
        break
    while cont + 1 <= 10:
        cont += 1
        print(f'{num} x {cont} = {num * cont}')
    cont = 0
    print('=-=' * 13)
print('Programa de tabuada encerrado.')