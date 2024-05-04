s=float(input('Qual é o salário do funcionário? R$:'))
sa=s+(s/100*15)
print('Um funcionário que ganha R${:.2f}, com 15% de aumento, passa a receber R${:.2f}'.format(s,sa))