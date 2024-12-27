# O volume específico de um vapor superaquecido 
# é listado em tabelas com alta precisão para 
# várias temperaturas. Por exemplo, para uma
# pressão de 3000 lb/in²

# T = [370, 382, 394, 506, 418]
# v = [5.9313, 7.5838, 8.8428, 9.796, 10.5311]

# Determine v para T = 400

from matplotlib import pyplot
import numpy as np

# Set de dados inicial
X = [370, 382, 394, 406, 418]
Y = [5.9313, 7.5838, 8.8428, 9.796, 10.5311]

# Monta a matriz A
def montaA(x):
    A = []
    for i in range(len(x)):
        A.append(
            [1, x[i], x[i]**2] 
        )
    return np.array(A)
A = montaA(X)

# Acha os coeficientes
a = np.linalg.solve(np.transpose(A).dot(A), np.transpose(A).dot(Y))

# Função da regressão
def f(x): 
    global a
    return a[0] + a[1] * x + a[2] * x ** 2

# Plota os pontos originais
pyplot.plot(X, Y, "ro", markersize=10)

# Plota a função
x = np.linspace(350, 450, 100)
y = f(x)
pyplot.plot(x,y)

pyplot.plot(400, f(400), 'o', color='black', markersize=10)

pyplot.show()