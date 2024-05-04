def ficha_do_jogador():
    nome_do_jogador = input('Nome do Jogador: ').strip().title()
    if nome_do_jogador == '':
        nome_do_jogador = '<desconhecido>'
    num_gols = input('Número de gols: ').strip()
    if num_gols == '':
        num_gols = 0
    int(num_gols)
    return {'nome' : nome_do_jogador, 'gols' : num_gols}


jogador = ficha_do_jogador()
print(f'O jogador {jogador["nome"]} fez {jogador["gols"]} gol(s) no campeonato.')

