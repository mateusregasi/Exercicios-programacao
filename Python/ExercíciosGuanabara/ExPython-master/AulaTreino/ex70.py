escolha = ''
total = 0
cont = 0
menor = 0
cont1 = 0
menornome = ''

print('-' * 30)
print('======Loja Super Baraton======')
print('-' * 30)

while True:
    cont1 += 1
    escolha = ''
    nome = input('Nome do produto: ')
    pre = float(input('Preço do produto: R$'))
    total += pre

    if pre > 1000:
        cont += 1

    if cont1 == 1 or pre < menor:
        menor = pre
        menornome = nome
    while escolha != 'S':
        escolha = input('Quer continuar? (S/N): ').upper().strip()[0]
        if escolha == 'N':
            break
        elif escolha != 'S':
            print('Comando inválido. Tente novamente.')
    if escolha == 'N':
        break
print('------- FIM DO PROGRAMA -------')
print(f'O total da compra foi de R${total:.2f}')
print(f'Ao todo {cont} produtos tiveram o preço acima de R$1000.00')
print(f'O produto mais barato foi {menornome} custou R${menor:.2f}')
