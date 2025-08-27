# INTRODUÇÃO À ÁLGEBRA LINEAR
# Reginaldo J. Santos
import numpy as np

# Calcule A, A² ... A^k para
# k = 0

# a) A = [[1, 1/2], [0, 1/3]]
# A = [[1, 1/2], [0, 1/3]]
# A = np.array(A)
# print(np.linalg.matrix_power(A, k))

# b) A = [[1/2, 1/3], [0, -1/5]]
# A = [[1/2, 1/3], [0, -1/5]]
# A = np.array(A)
# print(np.linalg.matrix_power(A, k))

# Calcula as potências das matrizes dadas a seguir e encontre experimentalmente o menor inteiro k > 1 tal que 
# a) A^k = I_3 em que A = [[0, 0, 1], [1, 0, 0], [0, 1, 0]]
# k = 3
# A = np.array([[0, 0, 1], [1, 0, 0], [0, 1, 0]])
# print(np.linalg.matrix_power(A, k))

# b) A^k = I_4 em que A = [[0, 0, 0, 1], [-1, 0, 0, 0], [0, 0, 0, 1], [0, 0, 1, 0]]
# k = 1
# A = np.array([[0, 0, 0, 1], [-1, 0, 0, 0], [0, 0, 0, 1], [0, 0, 1, 0]])
# print(np.linalg.matrix_power(A, k))
# Não tem

# c) A^k = 0 em que A = [[0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1], [0, 0, 0, 0]]
# k = 1
# A = np.array([[0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1], [0, 0, 0, 0]])
# print(np.linalg.matrix_power(A, k))
# Não tem

# a) use o comando rand(4,2) para gerar 4 pontos com entradas inteiras e aleatórias entre -5 e 5. Os pontos estão armazenados nas linhas da matriz A.
 A = np.random.rand(4, 2) * 10 - 5
# print(A)

# b) Tente encontrar os coeficientes da função polinomial p(x) = a*x**3 + b*x**2 + c*x + d onde o gráfico passa pelos pontos de A.

