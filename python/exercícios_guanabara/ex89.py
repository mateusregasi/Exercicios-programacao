pessoa = []
todos = []


while True:
    nome = str(input('Nome do aluno: ')).title().strip()
    nota1 = float(input('Primeira nota do aluno: '))
    nota2 = float(input('Segunda nota do aluno: '))
    pessoa.append(nome)
    pessoa.append(nota1)
    pessoa.append(nota2)
    todos.append(pessoa[:])
    pessoa.clear()

    while True:
        resposta = str(input('Quer continuar? [S/N] ')).strip().upper()[0]
        if resposta == 'S' or resposta == 'N':
            break
    if resposta == 'N':
        break

print('_' * 30)
print('Nª Nome:          Média:')
cont = 0
for c in todos:
    print('{}  {: <15}{: <15}'.format(cont, c[0], c[1] + c[2] // 2))
    cont += 1
print('_' * 30)

nome = 0

while nome != -1:
    nome = int(input('Digite o número do aluno para saber suas notas(digite -1 para parar): '))
    if nome != -1:
        print(f'O aluno {todos[nome][0]} teve as notas: {todos[nome][1]:.2f} e {todos[nome][2]:.2f}')