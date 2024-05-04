d=float(input('Qual é a distancia da sua viagem?: '))
print('Você está prestes a começar uma viagem de {:.1f}km.'.format(d))
if d >200:
    print('O preço de sua passagem será de R${:.2f}'.format(d*0.45))
else:
    print('O preço da sua passagem será de R${:.2f}'.format(d*0.5))
'''print('O preço de sua passagem será de R${}'.format(d*0.45 if d >200 else d*0.5))'''