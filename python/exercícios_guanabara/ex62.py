print('   Gerador de PA')
print('=-=' * 10)

op = 1
primeiro = int(input('Primeiro termo: '))
razao = int(input('Razão da PA: '))
termo = primeiro
cont = 1
num = 10
antes = 0

while op != 0:

    while cont <= num + op - 1:
        print('{} → '.format(termo), end="")
        termo += razao
        cont += 1
        antes = op
    print('PAUSA')
    op += int(input('Quantos termos você quer mostrar a mais?: '))
    if op == antes:
        op = 0
    print('Progressão finalizada com {} números mostrados.'.format(cont - 1))