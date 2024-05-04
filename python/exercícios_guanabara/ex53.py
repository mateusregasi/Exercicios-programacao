'''frase = input('Digite uma frase: ').strip().upper().replace(' ','')
frasei = frase[:: -1]
print('O inverso de {} é {}'.format(frase, frasei))
if frasei == frase:
    print('A frase digitada é um palíndromo!')
else:
    print('A frase digitada não é um palíndromo!')'''

frase = input('Digite uma frase: ').strip().upper().split()
junto = ''.join(frase)
inverso = ''

for c in range(len(junto)-1, -1, -1):
    inverso += junto[c]
print('O inverso de {} é {}'.format(junto, inverso))
if junto == inverso:
    print('A frase digitada é um palíndromo!')
else:
    print('A frase digitada não é um palíndromo!')