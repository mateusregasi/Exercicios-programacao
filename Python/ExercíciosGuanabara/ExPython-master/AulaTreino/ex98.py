def linha():
    print('-=' * 30)
def contagem(inicio, fim, passo):
    print(f'Contagem e {inicio} até {fim} de {passo} em {passo}')
    if inicio > fim:
        for c in range(inicio, fim - 1, -passo):
            print(c, end=' ')
        print('FIM!')
    else:
        for c in range(inicio, fim + 1, passo):
            print(c, end=' ')
        print('FIM!')


linha()
contagem(1, 10, 1)
linha()
contagem(10, 0, 2)
linha()
print('Agora é sua vez de personalizar a contagem!')
inicio = int(input('Início: '))
fim = int(input('Fim: '))
passo = int(input('Passo: '))
linha()
contagem(inicio, fim, passo)