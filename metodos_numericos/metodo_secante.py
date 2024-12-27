"""
Suponha que temos f(x) e um ponto único (x0, y0). A ideia do método é achar a raíz da reta tangente ao ponto e tornar o próximo x.

Queremos achar então uma função no formato f'(x0)x + b = y
Vamos analisar o ponto (x0, y0)

f'(x0)x0 + b = y0
b = y0 - f'(x0)x0

Portanto, substituindo em f'(x0)x + b = y
f'(x0)x + y0 - f'(x0)x0 = y
x = (y - y0 + f'(x0)x0) / f'(x0)

Sabemos que y tende a 0. então
x = (f'(x0)x0 - y0) / f'(x0)
"""

import matplotlib.pyplot as p
import numpy as np

def f(x):
    return 16*x**3 - 9*x**2 + 4*x - 5
def df(x):
    return 48*x**2 - 18*x + 4
def er(x1, x0):
    if x1 == 0: return 0
    return abs((x1 - x0) / x1)

x = np.linspace(-5, 5, 50)
y = f(x)

xm = 0
ym = f(xm)
while(1):
    yv = ym
    xm = (df(xm)*xm - ym) / df(xm)
    ym = f(xm)
    
    print(f'({xm}, {ym})')

    print(er(ym, yv))
    if(er(ym, yv) < 0.00001): break

p.plot(x,y)
p.plot(xm, ym, 'ro', markersize=10)
p.show()