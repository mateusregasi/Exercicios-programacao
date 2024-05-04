from funcoes import mostrarLinha

lista_de_jogadores = []

while True:
    jogador = {}

    while True:
        jogador['nome'] = input('Nome do jogador: ').strip().title()
        if jogador['nome'].isalpha() == True:
            break
        else:
            print('Nome inválido! Digite novamente!')

    totalgols = 0
    gols = []
    quantaspartidas = int(input(f'Quantas partidas {jogador["nome"]} jogou?: '))
    for c in range(1, quantaspartidas + 1):
        gol = int(input(f'Quantos gols na partida {c}?: '))
        totalgols += gol
        if gol > 0:
            gols.append(gol)
    jogador['gols'] = gols
    jogador['total'] = totalgols

    lista_de_jogadores.append(jogador)

    while True:
        continuar = input('Quer continuar?[S/N]: ')[0].strip().upper()
        if continuar == 'N' or continuar == 'S':
            break
    mostrarLinha(65)
    if continuar == 'N':
        break

mostrarLinha(65)
print(f'cod  nome                          gols                     ')
mostrarLinha(65)
cont = 0
for c1 in lista_de_jogadores:
    cont += 1
    print('{:3}  {:<28}  {}  Total: {}'.format(cont, c1["nome"], c1["gols"], c1["total"]))
mostrarLinha(65)
