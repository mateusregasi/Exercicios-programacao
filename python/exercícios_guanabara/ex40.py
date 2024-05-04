n1 = float(input('Primeira nota: '))
n2 = float(input('Segunda nota: '))
m = (n1 + n2) / 2
if m < 5:
    print('Poxa... Que pena... Sua média foi {:.1f}, você foi REPROVADO!'.format(m))
elif m >= 5 and m <= 6.9:
    print('Sua média é {:.1f}, e você infelizmente ficará de RECUPERAÇÃO.'.format(m))
elif m >= 7 and m < 10:
    print('Parabéns! Sua média foi excelente! Você tirou {:.1f}, APROVADO!'.format(m))
elif m == 10:
    print('MEUS PARABENS, VOCÊ TIROU A MAIOR NOTA, TOME UM NINTENDO SWITCH!')
