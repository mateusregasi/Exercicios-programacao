from math import hypot
o=float(input('Comprimento do cateto oposto:'))
a=float(input('Comprimento do cateto adjacente:'))
h=hypot(o,a)
print("A hipotenusa vai medir: {:.2f}".format(h))