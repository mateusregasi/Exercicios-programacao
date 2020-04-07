def titulo(msg):
    print('=' * 40)
    print(f'{msg:^40}')
    print('=' * 40)
def mostrarLinha():
    print('=' * 40)
def arquivoExiste(nome):
    try:
        arq = open(nome, 'r')
        arq.close()
    except FileNotFoundError:
        return False
    else:
        return True
def criarArquivo(nome):
    lista = open(nome, 'w+')
    lista.close()
def apagarArquivo(nome):
    lista = open(nome, 'w')
    lista.close()
def numLinhas():
    texto = open('nomes.txt', 'r')
    cont = 0
    for l in texto:
        cont += 1
    texto.close()
    return cont
def menuOp():
    while True:
        titulo('MENU PRINCIPAL')
        print('1 - Ver pessoas cadastradas.\n'
              '2 - Cadastrar nova pessoa.\n'
              '3 - Buscar na lista.\n'
              '4 - Apagar Lista.\n'
              '5 - Apagar pessoa da lista.\n'
              '6 - Sair do Sistema.')
        mostrarLinha()
        try:
            op = int(input('Sua opção: '))
        except:
            print('Erro! Digite uma opção válida!')
        else:
            if op != 1 and op != 2 and op != 3 and op != 4 and op != 5 and op != 6:
                print('Erro! Digite uma opção válida!')
            else:
                break
    return op
def mostrarLista():
    titulo('LISTA DE CADASTRADOS')
    lista = open('nomes.txt', 'r')
    for linha in lista:
        print(linha, end='')
    lista.close()
def adicionarLista():
    texto = open('nomes.txt', mode='a')
    titulo('NOVO CADASTRO')
    pessoa = {}
    pessoa['codigo'] = numLinhas()
    while True:
        pessoa['nome'] = str(input('Nome: ')).strip().title()
        if pessoa['nome'].istitle():
            break
        else:
            print('Valor digitado inválido!')
    while True:
        try:
            pessoa['idade'] = f'{int(input("Idade: "))} anos'
        except:
            print('Valor digitado inválido!')
        else:
            break
    print(f'Adicionando {pessoa["nome"]} a lista.')
    pessoalinha = '{:<3} {:<28} {:>7}'.format(pessoa['codigo'], pessoa['nome'], pessoa['idade'])
    texto.write(f'{pessoalinha}\n')
    texto.close()
def buscarNaLista():
    lista = open('nomes.txt')
    mostrarLinha()
    while True:
        cont = 0
        item = input('Qual nome gostaria de achar?[digite sair para sair]: ').strip().title()
        lista.seek(0)
        mostrarLinha()
        if item.isnumeric() == True or item == '':
            print('Item inválido! ')
        elif item == 'Sair':
            break
        else:
            for linha in lista:
                if item in linha:
                    print(linha, end='')
                    cont += 1
            if cont == 0:
                print('Pessoa não encontrada!')
        mostrarLinha()
    lista.close()
def apagarPessoa():
    lista = open('nomes.txt', mode='r')
    listaPessoas = lista.readlines()
    if listaPessoas == []:
        print('A lista já está vazia!')
    else:
        listaPessoasApagar = []
        mostrarLinha()
        while True:
            while True:
                try:
                    cod = int(input('Digite o código do usuário[-1 sai]: '))
                except:
                    print('O valor digitado é inválido, tente novamente!')
                else:
                    break
            cont = 0
            cont2 = 0
            cod = f'{cod:<3}'
            for linha in listaPessoas:
                if cod in linha:
                    cont += 1
                    lista.seek(cont2)
                    listaPessoasApagar.append(linha)
                cont2 += 1
            break
        if cont != 0:
            print(f'Foram apagados {cont} cadastros.')
        lista.close()
        apagarArquivo('nomes.txt')
        for c1 in listaPessoas:
            for c2 in listaPessoasApagar:
                if c1 == c2:
                    listaPessoas.remove(c2)
    lista = open('nomes.txt', mode='w')
    lista.writelines(listaPessoas)
    lista.close()
