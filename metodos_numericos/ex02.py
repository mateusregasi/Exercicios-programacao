# Três organismos portadores de doença decaem 
# exponencialmente na água salgada de acordo
# com o modelo:

# p(t) = a0e^(-1.5t) + a1e^(-0.3t) + a2e^(-0.05t) 

# Estime a concentração inicial (t = 0) de cada organismo (ou seja, todos os ai) dados as seguintes medidas

# t = [0.5, 1, 2, 3, 4, 5, 6, 7, 9]
# p(t) = [6, 4.4, 3.2, 2.7, 2, 1.9, 1.7, 1.4, 1.1]

import numpy as np
from matplotlib import pyplot

# Estabelece o set inicial
t = np.array([0.5, 1, 2, 3, 4, 5, 6, 7, 9])
p = np.array([6, 4.4, 3.2, 2.7, 2, 1.9, 1.7, 1.4, 1.1])

# Monta a matriz A à partir do modelo
def montaA(t):
    A = []
    for x in t:
        A.append([
            np.e ** (-1.5 * x), 
            np.e ** (-0.5 * x), 
            np.e ** (-0.05 * x)
        ])
    return np.array(A)

# Acha os coeficientes
A = montaA(t)
a = np.linalg.solve(np.transpose(A).dot(A), np.transpose(A).dot(p))

# Define a função
def f(t): 
    global a
    return a[0] * np.e ** (-1.5 * t) + a[1] * np.e ** (-0.5 * t) + a[2] * np.e ** (-0.05 * t)

# Marca os pontos originais
pyplot.plot(t, p, 'ro', markersize=10)

# Desenha a aproximação
x = np.linspace(0, 10, 1000)
y = f(x)
pyplot.plot(x, y, color='blue')

# Mostra o gráfico
pyplot.show()