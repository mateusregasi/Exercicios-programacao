lista = []

expressao = input('Digite uma expressão: ')

for c in expressao:
    if c == '(':
        lista.append('(')
    elif c == ')':
        lista.append(')')

parentesestotal = len(lista)
invalido = False

if parentesestotal % 2 == 0:
    for c in range(0, parentesestotal, 2):
        if c == ')':
            invalido = True
            break
    for i in range(1, parentesestotal, 2):
        if i == '(':
            invalido = True
            break
else:
    invalido = True

if invalido == True:
    print('Expressão inválida.')
else:
    print('Expressão válida.')