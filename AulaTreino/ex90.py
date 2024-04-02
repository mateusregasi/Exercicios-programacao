aluno = {}
aluno['Aluno'] = input('Nome do aluno: ').title()
aluno['Média'] = float(input('Média do aluno: '))
if aluno['Média'] <= 5:
    aluno['Situação'] = 'Reprovado'
elif aluno['Média'] < 7 and aluno['Média'] > 5:
    aluno['Situação'] = 'Recuperação'
else:
    aluno['Situação'] = 'Aprovado'
print(' - O nome é {}\n - A média é igual a {:.1f}\n - A situação é de {}'.format(aluno['Aluno'], aluno['Média'], aluno['Situação']))
