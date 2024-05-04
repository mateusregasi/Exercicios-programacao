from funcoes import mostrarLinha


def voce_vota():
    global idade
    from _datetime import datetime
    ano = datetime.today().year
    ano_de_nascimento = int(input('Em qual ano você nasceu?: '))
    idade = ano - ano_de_nascimento
    if idade < 16:
        situacao = 'NÃO VOTA'
    elif idade < 18 or idade > 70:
        situacao = 'VOTO OPCIONAL'
    else:
        situacao = 'VOTO OBRIGATÓRIO'
    return situacao


mostrarLinha(60)
situacao = voce_vota()
print(f'Com {idade} anos: {situacao}')
mostrarLinha(60)