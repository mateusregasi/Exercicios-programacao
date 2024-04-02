'''print('-' * 20)
print('--CAIXA ELETRÔNICO--')
print('-' * 20)

n1 = 1
n2 = 10
n3 = 20
n4 = 50

sacar = int(input('Qual valor será sacado: R$'))
print('-' * 20)


contn4 = sacar // n4
n4sobra = sacar % n4
contn3 = n4sobra // n3
n3sobra = n4sobra % n3
contn2 = n3sobra // n2
n2sobra = n3sobra % n2
contn1 = n2sobra // n1

if contn4 >= 1:
    print(f'Total de {contn4} cédulas de R$50')
if contn3 >= 1:
    print(f'Total de {contn3} cédulas de R$20')
if contn2 >= 1:
    print(f'Total de {contn2} cédulas de R$10')
if contn1 >= 1:
    print(f'Total de {contn1} cédulas de R$1')

print('-' * 20)
print('Tenha um bom dia!')'''

print('=' * 30)
print('{:^30}'.format('Banco Cev'))
print('=' * 30)

valor = int(input('Qual valor você quer sacar? R$'))
total = valor
ced = 50
totced = 0

while True:
    if total >= ced:
        total -= ced
        totced += 1
    else:
        if totced > 0:
            print(f'Total de {totced} cédulas de R${ced}')
        if ced == 50:
            ced = 20
        elif ced == 20:
            ced = 10
        elif ced == 10:
            ced = 1
        totced = 0
        if total == 0:
                break
print('=' * 30)
print('Programa encerrado.')