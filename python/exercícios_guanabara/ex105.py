def notas(*nota, sit=False):
    notas_tupla = nota
    cont = 0
    soma = 0
    for c in notas_tupla:
        if cont == 0:
            maior = menor = c
        else:
            if maior < c:
                maior = c
            if menor > c:
                menor = c
        soma += c
        cont += 1
    media = soma / cont
    dicio_notas = {}
    dicio_notas['total'] = cont
    dicio_notas['maior'] = maior
    dicio_notas['menor'] = menor
    dicio_notas['media'] = media
    if sit == True:
        if media < 5:
            dicio_notas['situação'] = 'RUIM'
        elif media < 7:
            dicio_notas['situação'] = 'RAZOÁVEL'
        else:
            dicio_notas['situação'] = 'BOA'
        return dicio_notas


resposta = notas(5.5, 2.5, 10, 6.5, sit=True)
print(resposta)