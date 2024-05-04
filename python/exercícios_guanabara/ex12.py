p=float(input('Qual é o preço do produto?R$:'))
pcd=p-(p/20)
print('O produto que custava R${:.2f}, na promoção com o desconto de 5% vai custar R${:.2f}'.format(p,pcd))