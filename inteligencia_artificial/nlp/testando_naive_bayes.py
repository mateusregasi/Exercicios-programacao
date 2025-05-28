from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
import csv

# 1. Dados de treino: palavras com suas classes
palavras_treino = []
categorias_treino = [] 
with open('data.csv') as arquivo:
    reader = csv.reader(arquivo, delimiter=';')
    for line in reader:
        palavras_treino.append(line[0])
        categorias_treino.append(line[1])

# 2. Bag of Words (BoW)
vectorizer = CountVectorizer(lowercase=True, strip_accents='ascii')
X = vectorizer.fit_transform(palavras_treino)

# 3. Treinamento com Naive Bayes
modelo = MultinomialNB()
modelo.fit(X, categorias_treino)

# 4. Classificar palavra nova
def classificar_material(palavra):
    X_novo = vectorizer.transform([palavra])
    return modelo.predict(X_novo)[0]

# Exemplo
materiais = [ 
    "corpo humano",
    "Mochila pequena velha (pochete)",
    "Cartão de crédito",
    "mousepad",
    "Óculos de sol",
    "Chapa elétrica de pão",
    "Cadeira de escritório",
    "Impressora",
    "Aspirador de pó",
    "Máquina de fazer café",
    "Liquidificador",
    'notebook',
    'celular'
]
for palavra in materiais:
    print(palavra.lower(), classificar_material(palavra))
