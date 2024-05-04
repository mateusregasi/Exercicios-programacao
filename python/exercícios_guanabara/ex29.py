velocidade=float(input('Qual é a velocidade atual do carro?: '))
if velocidade >80:
    vp=(velocidade-80)*7
    print('MULTADO! Você ultrapassou o limite de velocidade que é 80km/h')
    print('Você deverá pagar uma multa de R${:.2f}'.format(vp))
print('Tenha um bom dia! Dirija com segurança!')
