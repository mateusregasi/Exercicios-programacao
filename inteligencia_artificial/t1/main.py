# -=-=-=-=-=-=-=-=-=-=-=-=-=- Importando -=-=-=-=-=-=-=-=-=-=-=-=-=-

import pandas as pd

# Importando os modelos
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import hamming_loss

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


# Database:
# https://archive.ics.uci.edu/dataset/856/higher+education+students+performance+evaluation

# -=-=-=-=-=-=-=-=-=-= Preparando base de dados -=-=-=-=-=-=-=-=-=-=

# Carregar arquivo CSV
data = pd.read_csv('data.csv', delimiter=',')

# Convertendo colunas com valores de texto usando On-Hot Encoding
categorical_cols = data.select_dtypes(include=['object']).columns
data = pd.get_dummies(data, columns=categorical_cols, drop_first=True)

# Separando os dados por feature e target
target = 'COURSE ID'
x = data.drop(columns=target)
y = data[target]  # Vai classificar só o G1

# Separando dados para treino e teste
re = 82
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=re)

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

# -=-=-=-=-=-=-=-=-=-=-=-= Usando os modelos -=-=-=-=-=-=-=-=-=-=-=-=

# Importando os modelos que serão utilizados
tree_model = DecisionTreeClassifier(random_state=re)
forest_model = RandomForestClassifier(n_estimators=100, random_state=re)
mlp_model = MLPClassifier(hidden_layer_sizes=(100,), max_iter=1000, random_state=re)

# Modelo 1: Árvore de Decisão
tree_model.fit(x_train, y_train)
y_pred_tree = tree_model.predict(x_test)
accuracy_tree = hamming_loss(y_test, y_pred_tree)
print(f"Acurácia (Decision Tree): {accuracy_tree:.2f}")

# Modelo 2: Random Forest
forest_model.fit(x_train, y_train)
y_pred_forest = forest_model.predict(x_test)
accuracy_forest = hamming_loss(y_test, y_pred_forest)
print(f"Acurácia (Random Forest): {accuracy_forest:.2f}")

# Modelo 3: Multilayer Perceptron (MLP)
mlp_model.fit(x_train, y_train)
y_pred_mlp = mlp_model.predict(x_test)
accuracy_mlp = hamming_loss(y_test, y_pred_mlp)
print(f"Acurácia (MLP): {accuracy_mlp:.2f}")

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
