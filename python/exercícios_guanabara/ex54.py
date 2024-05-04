from datetime import date
data = date.today().year
contmaior = 0
contmenor = 0

for c in range(1, 8):
    ano = int(input('Em que ano a {}ª pessoa nasceu?: '.format(c)))
    idade = data - ano
    if idade >= 18:
        contmaior += 1
    else:
        contmenor += 1

print('Ao todo tivemos {} pessoas de maior idade.'.format(contmaior))
print('Também tivemos {} pessoas de menor idade.'.format(contmenor))