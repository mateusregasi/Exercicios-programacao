numextenso = ('zero', 'um', 'dois', 'tres', 'quatro', 'cinco', 'seis', 'sete', 'oito', 'nove', 'dez', 'onze', 'doze', 'treze', 'quatorze', 'quize', 'dezesseis', 'dezessete', 'dezoito', 'dezenove', 'vinte')
num = -1
while True:
    while num < 0 or num > 20:
        num = int(input('Digite um número entre 0 e 20: '))
        if num < 0 or num > 20:
            print('Tente novamente. ',end='')

    print(f'Você digitou o número {numextenso[num]}.')
    while True:
        escolha = input('Você quer continuar? [S/N]: ').strip().upper()[0]
        if escolha == 'S' or escolha == 'N':
            break
    if escolha == 'N':
        break
    escolha = ''
    num = -1