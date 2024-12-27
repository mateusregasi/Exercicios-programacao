"""
Divisão binária em intervalo real. Resumindo é isso.
"""

import matplotlib.pyplot as p
import numpy as np

def f(x):
    return 16*x**3 - 9*x**2 + 4*x - 5
def er(x1, x0):
    if x1 == 0: return 0
    return abs((x1 - x0) / x1)

x = np.linspace(-5, 5, 50)
y = f(x)

x0 = x[20]
x1 = x[30]

ym = 0
while(1):
    yv = ym
    xm = (x1 + x0) / 2
    ym = f(xm)

    print(f'({xm}, {ym})')


    if ym > 0: x1 = xm
    else: x0 = xm

    print(er(ym, yv))
    if(er(ym, yv) < 0.00001): break


p.plot(x,y)
p.plot(xm, ym, 'ro', markersize=10)

p.show()