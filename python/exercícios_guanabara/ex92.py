from funcoes import mostrarLinha
from datetime import date

ano = date.today().year

dados = {}

dados['nome'] = input("Nome: ").strip().title()
dados['idade'] = ano - (int(input('Ano de nascimento: ')))
dados['ctps'] = int(input('Carteira de trabalho[0 se não tiver]: '))
if dados['ctps'] > 0:
    ano_de_contratacao = int(input('Ano de contratação: '))
    dados['salário'] = float(input('Salário: R$'))
    dados['aposentadoria'] = dados['idade'] + ((ano_de_contratacao + 35) - ano)
mostrarLinha(30)

for k, v in dados.items():
    print(f' - {k} tem valor {v}')