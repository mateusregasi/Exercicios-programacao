"""
O método da falsa posição é um método intervalar para descobrir 0 de funções. A proposta dele é a seguinte:

1) Definir o intervalo o qual suspeita-se que possúi raiz, isso pode ser feito observando o gráfico da função.
2) Defina a reta entre os dois pontos.
3) Tendo sido traçado a reta, encontre a intersecção dela com o eixo horizontal e torne esse ponto uma nova extremidade do intervalo

Suponha então que temos o ponto (x0, y0) e (x1, y1). Vamos traçar a reta:

Sabemo que a função terá formato: ax + b = y

â -> ângulo da reta
tg(â) = ((y1 - y0) / (x1 - x0))

Então tg(â)x + b = y

Vamos escolher um ponto de exemplo, (x0, y0) -> tg(â)x0 + b = y0 -> b = (y0 - tg(â)x0)
Portanto temos que tg(â)x + y0 - tg(â)x0 = y. 
Queremos que y seja 0, portanto tg(â)x + y0 - tg(â)x0 = 0 -> tg(â)x = tg(â)x0 - y0 -> x = (tg(â)x0 - y0)/tg(â)

Agora substituindo tg(â) = ((y1 - y0) / (x1 - x0))
x = (((y1 - y0) / (x1 - x0))x0 - y0)/((y1 - y0) / (x1 - x0))
x = (y1x0 - y0x1) / (y1-y0)

Agora temos uma equação para descobrir a raiz da reta que intersecta dois pontos na função original

Agora vamos tentar resolver a função sin(x) + x**3/3 - 5x + e**(-x)

"""

import numpy as np
import matplotlib.pyplot as m

def f(x):
    return 16*x**3 - 9*x**2 + 4*x - 5
def er(x1, x0):
    if x1 == 0: return 0
    return abs((x1 - x0) / x1)

x = np.linspace(-5, 5, 50)
y = np.array(f(x))

x0, y0 = x[20], f(x[20])
x1, y1 = x[30], f(x[30])

ym = 0
while(1):
    print(f"({x0}, {y0})-({x1}, {y1})")
    yv = ym
    xm = (y1*x0 - y0*x1) / (y1 - y0)
    ym = f(xm)

    print(f'({xm}, {ym})')

    if ym > 0: 
        y1 = ym
        x1 = xm
    else:
        y0 = ym
        x0 = xm
    
    print(er(ym, yv))
    if(er(ym, yv) < 0.00001): break

m.plot(x, y, color='blue')
m.plot(xm, ym, 'ro', markersize=10)

m.show()