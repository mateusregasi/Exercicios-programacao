def terreno():
    print('~' * 24)
    print('~~Controle de Terrenos~~')
    print('~' * 24)
    altura = float(input('Informe a altura(m): '))
    largura = float(input('Informe a largura(m): '))
    area = altura * largura
    print(f'A área de um terreno {altura}x{largura} é de {altura * largura}².')


terreno()