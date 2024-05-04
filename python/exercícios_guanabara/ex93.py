from funcoes import mostrarLinha

lista = {}
gols = []
total = 0
lista['nome'] = input('Nome do jogador: ').strip().title()
partidas = int(input(f'Quantas partidas {lista["nome"]} jogou?: '))

for c in range(1, partidas + 1):
    gol = int(input(f'Quantos gols na partida {c}?: '))
    gols.append(gol)
    total += gol
lista['gols'] = gols
lista['total'] = total

mostrarLinha(40)
print(lista.items())
mostrarLinha(40)

print(f'O jogador {lista["nome"]} jogou {partidas} partidas.')
for c2 in range(1, partidas + 1):
    print(f'  =>  Na partida {c2} fez {lista["gols"][c2 - 1]} gols.')
print(f'Foi um total de {lista["total"]} gols.')