casa = float(input('Valor da casa: R$'))
sal = float(input('Salário do comprador: R$'))
anos = int(input('Quantos anos de financiamento?: '))
pres = casa / anos / 12
salt = sal / 100 * 30
pagar = pres - salt
print('Para pagar uma casa de R${:.2f} em {} anos a prestação será de R${:.2f}'.format(casa,anos,pres))
if pagar > 0:
    print('Empréstimo NEGADO!')
else:
    print('Empréstimo pode ser concedido!')