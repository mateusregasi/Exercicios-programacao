sexo = input('Informe seu sexo: [M/F] ').strip().upper()[0]

if sexo not in 'MF':

    while sexo not in 'MF':
        sexo = input('\033[31mComando inválido. Por favor, informe seu sexo: \033[m').strip().upper()[0]

print('Sexo {} registrado.'.format(sexo))