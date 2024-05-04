def aumentar(n, p):
    n += (n / 100 * p)
    return n
def diminuir(n, p):
    n -= (n / 100 * p)
    return n
def dobro(n):
    n *= 2
    return n
def metade(n):
    n /= 2
    return n
def moeda(n, m='R$', text=False):
    n = float(f'{n:.2f}')
    if text == True:
        n = f'{m}{n}'.replace('.', ',')
    return n
    def leiaDinheiro(moedatipo='R$',formatar=False):
    while True:
        n = str(input(f'Informe o valor: {moedatipo}').strip())
        if n.isalnum() == False or n.isalpha() == False or n.isspace() == False:
            break
        print('Número inválido, digite novamente')
    if formatar == True:
        moeda(n)
    return n