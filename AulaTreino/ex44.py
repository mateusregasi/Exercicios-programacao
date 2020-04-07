print(('\033[0;36;0m_=_'*5),'LOJAS MATEUSZINHO',('_=_'*5),'\033[m')
preço = float(input('Preço das compras: R$'))
print('''FORMAS DE PAGAMENTO
[ 1 ] à vista dinheiro/cheque
[ 2 ] à vista cartão
[ 3 ] 2x no cartão
[ 4 ] 3x ou mais no cartão''')
op = int(input('Qual é a opção? '))

if op == 1:
    print('Suas compras de R${:.2f} agora vão passar a ser R${:.2f}'.format(preço,preço - (preço / 10)))
elif op == 2:
    print('Suas compras de R${:.2f} agora vão passar a ser R${:.2f}'.format(preço,preço-(preço / 20)))
elif op == 3:
    print('Você pagará duas parcelas de R${:.2f}, ao todo ficarão {:.2f}'.format(preço,preço / 2))
elif op == 4:
    par = int(input('Quantas parcelas?: '))
    print('Sua compra será parcelada em {}x de R${:.2f} com juros'.format(par,(preço + (preço / 5)) / par))
    print('Sua compra de R${:.2f} vai custar R${:.2f} no final.'.format(preço,preço + (preço / 5)))
else:
    print('\033[0;31;0mOpção inválida. Tente novamente\033[m')