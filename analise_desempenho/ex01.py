# Fazer um programa (na linguagem de sua preferência) para gerar números pseudo-aleatórios utilizando o método congruente linear. Escolha parâmetros a e M suficientemente grandes para que os números gerados sejam, de fato, pseudo-aleatórios. Gerar 1000 números entre [0, 1] e pegar apenas a primeira casa decimal, para que os valores sorteados sejam discretizados em intervalos de 0.1 em 0.1, isto é, [0:0.1; 0.1:0.2; 0.2:0.3; ... 0.9:1]). Gerar gráfico da frequência relativa dos intervalos. Usando o gerador nativo da linguagem escolhida por você, repita o processo para gerar 1000 números. Gere o gráfico comparando os resultados. Por fim, repita os dois processos, agora gerando 1000 amostras. Enviar os 4 gráficos, com a interpretação que você dá a eles, e o código fonte como resposta a essa questão.

from random import randint
import matplotlib.pyplot as plt

SEED = 234798234
MUL = 751
DEN = 51
IT = 100000

def mcl(x, a, M): return x * a % M
def f(x): return mcl(x, MUL, DEN) / DEN
def dis(x): return int(x / 0.1)

n = SEED
c = dict()
for _ in range(IT):
    n = f(n)
    v = dis(n)
    if v in c.keys():
        c[v] += 1
    else:
        c[v] = 1


plt.bar(c.keys(), c.values())
plt.show()