palavras = ('APRENDER', 'PROGRAMAR', 'LINGUAGEM', 'PYTHON', 'CURSO', 'GRATIS', 'ESTUDAR', 'PRATICAR', 'TRABALHAR', 'MERCADO', 'PROGRAMADOR', 'FUTURO')
contp = 0
cont = 0
ttpal = len(palavras)

while True:
    if ttpal == contp:
        break
    print(f'Na palavra {palavras[contp]} nós temos: ', end=' ')
    pal = palavras[contp]
    lpal = len(pal)
    while cont < lpal:
        if pal[cont] in 'AEIOU':
            print(pal[cont], end=' ')
            cont += 1
        else:
            cont += 1
    print('')

    cont = 0
    contp += 1
