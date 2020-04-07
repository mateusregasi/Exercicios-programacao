from utilidadesCeV.moeda import *


n = leiaDinheiro('R$')
a = int(input('Por quanto você quer aumentar? [%]'))
d = int(input('Por quanto você quer diminuir? [%]'))
print(f'O dobro de R${moeda(n)} é R${moeda(dobro(n))}.\n'
      f'A metade de {moeda(n)} é {moeda(metade(n))}.\n'
      f'Aumentando {a}% de R${moeda(n)}, temos R${moeda(aumentar(n, a))}.\n'
      f'Diminuindo {d}% de R${moeda(n)}, temos R${moeda(diminuir(n, d))}.')
print(moeda(n, text=True))