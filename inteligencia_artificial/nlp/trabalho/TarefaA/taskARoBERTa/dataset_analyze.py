from os import listdir
from conf import NORMALIZED_TRAIN_FILE
import torch

c = 0
avg = [0,0,0]
files = listdir(NORMALIZED_TRAIN_FILE)
# for file in files:
#     data = torch.load(f'{NORMALIZED_TRAIN_FILE}/{file}')
#     avg[0] += data["label"][0]
#     avg[1] += data["label"][1]
#     avg[2] += data["label"][2]
#     c += 1

print(f'Número de registros: {c}')
print(f'Número de registros em ordem (esquerda, centro e direita): {avg}')

data = torch.load(f'{NORMALIZED_TRAIN_FILE}/{files[0]}')
print(f"Formato da entrada: {data["feature"].shape}")
print(f"Formato da saída: {data["label"].shape}")
