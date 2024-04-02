from datetime import date
ano = int(input('Ano de nascimento: '))
atual = date.today().year
idade = atual - ano

if idade == 17:
    print('Você poderá se alistar daqui a 1 ano, em {}.'.format(atual+1))
elif idade <17:
    print('Você poderá se alistar daqui a {} anos, em {}.'.format(18-idade,atual+(18-idade)))
elif idade == 18:
    print('Você ja pode se alistar esse ano!')
elif idade == 19:
    print('Você poderia se alistar desde o ano passado, ou seja em {}.'.format(atual-1))
elif idade > 19:
    print('Você ja poderia ter se alistado a {} anos, em {}.'.format(idade-18, atual-(idade-18)))
