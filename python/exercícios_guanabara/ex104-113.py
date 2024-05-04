"""def leiaInt(msg):
    negativo = False
    while True:
        n = input(msg)
        if n[0] == '-':
            negativo = True
            n = n[1:]
        if n.isnumeric() == True:
            break
        else:
            print('O valor digitado é inválido! Tente novamente!')
    n = int(n)
    if negativo == True:
        n = -n
    return n"""
def leiaInt(msg):
    while True:
        try:
            n = int(input(msg))
        except Exception as ex:
            if str(ex) == "invalid literal for int() with base 10: ''":
                print('O usuário preferiu não indicar o valor.')
                n = 0
                break
            else:
                print('O número digitado é inválido')
        else:
            break
    return n
def leiaFloat(msg):
    while True:
        try:
            n = float(input(msg))
        except Exception as ex:
            if str(ex) == 'could not convert string to float: ':
                print('O usuário preferiu não indicar o valor.')
                n = 0
                break
            else:
                print('O número digitado é inválido!')
        else:
            break
    return n


i = leiaInt('Digite um número inteiro: ')
r = leiaFloat('Digite um número real: ')
print(f'Você digitou o número inteiro {i} e o real {r}.')
