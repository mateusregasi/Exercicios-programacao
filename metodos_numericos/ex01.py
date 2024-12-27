from matplotlib import pyplot
import numpy as np

# Considere o seguinte sistema de equações não-lineares:
# x0 + x0x1 = 10
# x1 + 3x0x1² = 57

# a) Escreva como o formato de zero de funções
def f1(x0, x1): return x0 + x0*x1 - 10
def f2(x0, x1): return x1 + 3 * x0 * x1 ** 2 - 57
def montajacobiana(x0, x1):
    return np.array([[1 + x1, x0], [3 * x1**2, 1 + 6 * x0 * x1]])

# Partindo do chute inicial [1, 1], encontre a solução aproximada
# após dois passos do método de Newton-Raphson sem utilizar
# a matriz Jacobiana inversa.

# Chute inicial
xi = np.array([1, 1])

# Dois passos
for i in range(2):
    J = montajacobiana(xi[0], xi[1])
    f = np.array([f1(xi[0], xi[1]), f2(xi[0], xi[1])])
    varx = np.linalg.solve(J, -f)
    xi = xi + varx

# Printa o resultado
print(xi)