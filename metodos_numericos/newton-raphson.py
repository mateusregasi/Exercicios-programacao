"""
Consiste na manipulação da série de taylor de primeira ordem
y = f(x0) + f'(x0)(x - x0)
x = (y - f(x0)) / f'(x0) + x0

Como queremos que y = 0 então
x = x0 - f(x0) / f'(x0)
"""

import matplotlib.pyplot as p
import numpy as np

def f(x):
    return 16*x**3 - 9*x**2 + 4*x - 5
def df(x):
    return 48*x**2 - 18*x + 4
def er(x1, x0):
    if x1 == 0: return 0
    return abs(x1 - x0) / x1

x = np.linspace(-5, 5, 50)
y = f(x)

xm = 10
ym = f(xm)
while(1):
    yv = ym
    xm = xm - f(xm) / df(xm)
    ym = f(xm)

    print(f'({xm}, {ym})')

    print(er(ym, yv))
    if(er(ym, yv) < 0.00001): break

p.plot(x,y)
p.plot(xm, ym, 'ro', markersize=10)
p.show()