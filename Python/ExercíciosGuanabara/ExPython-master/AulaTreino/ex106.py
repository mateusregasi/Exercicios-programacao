from ex97 import titulo

titulo('SISTEMA DE AJUDA PyHELP')
while True:
    escolha = input('Função ou Biblioteca: ').strip()
    if escolha.upper() == 'SAIR':
        break
    titulo(f'Acessando o manual do comando {escolha}')
    print(help(escolha))
print('Finalizando...')