# A viscosidade dinâmica da água u em
# mili-Newton-Segundo por metro quadrado
# é relacionada à temperatura T em
# graus Celsius da seguinte maneira

# T = [0, 5, 10, 20, 30, 40]
# u = [1.787, 1.519, 1.307, 1.002, 0.7975, 0.6529]

# a) Plote estes dados
import numpy as np
from matplotlib import pyplot

# Definindo os dados
Y = T = [0, 5, 10, 20, 30, 40]
X = u = [1.787, 1.519, 1.307, 1.002, 0.7975, 0.6529]

# Plotando os dados
pyplot.plot(u, T, "ro", markersize=10)
# pyplot.show()

# b) Use interpolação linear para estimar u com T = 7.5

# Vamos usar Newton
def F(xi, xj):
    global X, Y
    if xi == xj: return Y[xi]
    else: return (F(xi+1, xj) - F(xi, xj-1)) / (X[xj] - X[xi])

# Calcula os coeficientes
n = len(u)                   # Grau do polinômio

# Define  afunção
def p(x):
    global n, X, Y
    s = 0
    for i in range(n):
        a = F(0, i)
        for j in range(i):
            a *= (x - X[j])
        s += a
    return s

# Plota um intervalo
x = np.linspace(0, 2, 100)
y = p(x)
# y = np.vectorize(p)(x)

pyplot.plot(x, y)
pyplot.show()
