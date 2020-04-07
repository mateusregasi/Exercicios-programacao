d=float(input('Quantos dias alugados?:'))
km=float(input('Quantos KM rodados?:'))
at=(d*60)+(km*0.15)
print('O total a pagar é R${:.2f}'.format(at))