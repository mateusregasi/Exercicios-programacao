import fasttext, csv

# Carregar o modelo pré-treinado
modelo = fasttext.load_model('cc.pt.300.bin')
# modelo = fasttext.train_supervised('cbow_s50.txt')

categorias = dict()
with open('data.csv') as arquivo:
    reader = csv.reader(arquivo, delimiter=';')
    for line in reader:
        if line[1] in categorias.keys(): categorias[line[1]].append(line[0])
        else: categorias[line[1]] = []

import numpy as np

# vetores_categorias = {}
# for categoria, palavras in categorias.items():
    # vetores = [modelo.get_word_vector(palavra) for palavra in palavras]
    # vetor_medio = np.mean(vetores, axis=0)
    # vetores_categorias[categoria] = vetor_medio

from numpy.linalg import norm

# def classificar_palavra(palavra):
    # vetor_palavra = modelo.get_word_vector(palavra)
    # similaridades = {}
    # for categoria, vetor_categoria in vetores_categorias.items():
    #     similaridade = np.dot(vetor_palavra, vetor_categoria) / (norm(vetor_palavra) * norm(vetor_categoria))
    #     similaridades[categoria] = similaridade
    # print(similaridade)
    # categoria_mais_proxima = max(similaridades, key=similaridades.get)
    # return categoria_mais_proxima


# Exemplo de uso
def classificar_palavra(palavra):
    mais_similar = 0
    maior_categoria = ''
    maior_palavra = ''
    vetor_palavra = modelo.get_word_vector(palavra)
    for categoria, lista_palavras in categorias.items():
        for p in lista_palavras:
            vetor_palavra_teste = modelo.get_word_vector(p)
            similaridade =  np.dot(vetor_palavra, vetor_palavra_teste) / (norm(vetor_palavra) * norm(vetor_palavra_teste))
            if similaridade > mais_similar: 
                mais_similar = similaridade
                maior_categoria = categoria
                maior_palavra = p
    print(f'A palavra mais similar para {palavra} foi a palvra {maior_palavra} da categoria {maior_categoria} com similaridade {similaridade}.')
    return maior_categoria

materiais = [ 
    "corpo humano",
    "Mochila pequena velha (pochete)",
    "Cartão de crédito",
    "Mousepad",
    "Óculos de sol",
    "Chapa elétrica de pão",
    "Cadeira de escritório",
    "Impressora",
    "Aspirador de pó",
    "⁠Máquina de fazer café",
    "Liquidificador"
]
for palavra in materiais:
    categoria = classificar_palavra(palavra)
    print(f'A palavra "{palavra}" foi classificada como: {categoria}\n')