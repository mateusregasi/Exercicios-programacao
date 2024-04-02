num=input('Informe um número de 0 a 9999: ').strip()
u=num//1%10
d=num//10%10
c=num//100%10
um=num//1000%10
print('Analizando o número {}'.format(num))
print('Unidade: {}'.format(u))
print('Dezena: {}'.format(d))
print('Centena: {}'.format(c))
print('Unidade de milhar: '.format(um))