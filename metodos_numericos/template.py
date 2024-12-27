"""

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

x0, y0 = x[20], f(x[20])
x1, y1 = x[30], f(x[30])

xm = 0
ym = f(xm)
while(1):
    yv = ym
    
    print(f'({xm}, {ym})')

    print(er(ym, yv))
    if(er(ym, yv) < 0.00001): break

p.plot(x,y)
p.plot(xm, ym, 'ro', markersize=10)
p.show()