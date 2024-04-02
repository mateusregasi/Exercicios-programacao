from ex115b import *


while True:
    if arquivoExiste('nomes.txt') == False:
        criarArquivo('nomes.txt')
    op = menuOp()
    if op == 1:
        mostrarLista()
    elif op == 2:
        pessoa = adicionarLista()
    elif op == 3:
        buscarNaLista()
    elif op == 4:
        apagarArquivo('nomes.txt')
    elif op == 5:
        apagarPessoa()
    else:
        print('Finalizando programa!')
        exit()