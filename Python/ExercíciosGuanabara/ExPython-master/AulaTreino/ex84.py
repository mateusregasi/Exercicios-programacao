resposta = ''
dados = []
pessoas = []
cont = 0
maiorpeso = 0
menorpeso = 0
maiorpesonome = []
menorpesonome = []


while True:
    dados.append(input('Digite o nome: ').strip().title())
    dados.append(float(input('Digite o peso: ')))
    pessoas.append(dados[:])
    dados.clear()
    while True:
        resposta = input('Quer continuar?: ').strip().upper()[0]
        if resposta == 'N':
            break
        elif 'SN' not in resposta:
            print('Comando inválido.')
    if resposta == 'N':
        break

total = len(pessoas)

for c in range(0, total):
    if c == 0:
        maiorpeso = menorpeso = pessoas[c][1]
    else:
        if pessoas[c][1] > maiorpeso:
            maiorpeso = pessoas[c][1]
        if pessoas[c][1] < menorpeso:
            menorpeso = pessoas[c][1]

for x in range(0, total):
    if pessoas[x][1] == maiorpeso:
        maiorpesonome.append(pessoas[x][0])
    if pessoas[x][1] == menorpeso:
        menorpesonome.append(pessoas[x][0])
print(f'Ao todo {len(pessoas)} pessoas foram registradas.')
print(f'O maior peso registrado foi {maiorpeso:.2f}Kg de {maiorpesonome}')
print(f'O menor peso registrado foi {menorpeso:.2f}Kg de {menorpesonome}')