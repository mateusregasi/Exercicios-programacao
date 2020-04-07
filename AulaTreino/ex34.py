s = float(input('Qual é o salario do funcionário?: R$'))
if s <= 1250:
    a = s/100*15 + s
else:
    a = s/10 + s
print('Quem ganhava R${:.2f} passou a ganhar R${:.2f}'.format(s,a))