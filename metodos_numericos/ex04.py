# Funções de Bessel são bastante utilizadas em análises avançadas de engenharia, por exemplo nos estudos de campos elétricos e transporte escalar. A tabela abaixo apresenta alguns valores selecionados para a função de Bessel de ordem zero e de primeiro tipo:

# X = [1.8, 2.0, 2.2, 2.4, 2.6]
# Y = [0.5815, 0.5767, 0.5560, 0.5202, 0.4708]

# Estime J(2, 1) usando polinômios interpolantes de primeira, segunda, terceira, quarta e quinta ordem.

import numpy as np
from matplotlib import pyplot

# Conjunto de dados
X = [1.8, 2.0, 2.2, 2.4, 2.6]
Y = [0.5815, 0.5767, 0.5560, 0.5202, 0.4708]

# Criando o polinômio
def p(x, n):
    global X, Y
    s = 0
    for i in range(n):
        a = Y[i]
        for j in range(n):
            if i != j: a *= (x - X[j])/(X[i] - X[j])
        s += a
    return s

# Coloca os pontos
pyplot.plot(X,Y,"ro", markersize=10)

# Plota a reta
x = np.linspace(1.5, 3, 100)
cores = ['blue', 'green', 'yellow', 'purple', 'pink']
for i in range(2,6): pyplot.plot(x, p(x, i), cores[i-1])

pyplot.show()