# 0 -> esquerda
# 1 -> centro
# 2 -> direita

# 2) Criando função que importa os dados
from tokenizer import ClassifierTokenizer
from encoder import Encoder
import torch
from conf import NUM_CLASSES, NORMALIZED_TRAIN_FILE, NORMALIZED_DEV_FILE, TRAIN_PATH, DEV_PATH, NORMALIZED_SUFIX_FILE

def import_json(path):
    from json import loads
    from os import listdir

    # Pega o nome das pastas e retira as que tem . antes
    names = list(
        filter(
            lambda x: x if not x.startswith(".") else None,
            listdir(path)
        )
    )

    # Para cada pasta abre ela e coloca o conteúdo em um dicionário, depois retorna
    data = []
    for name in names:
        file_name = f"{path}/{name}"
        text = "".join(open(file_name).readlines())
        json = loads(text)
        data.append({
            "title":json["title"],
            "content":json["content"],
            "label":json["label"],
        })
    return data

# 3) Criando função que tokeniza os dados
tokenizer = ClassifierTokenizer()

# 4) Cria a função para pegar a representação vetorial do encoder e salva em um arquivo
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
encoder = Encoder(device)

paths = [
    {
        "path": TRAIN_PATH,
        "normalized_path": NORMALIZED_TRAIN_FILE
    },
    {
        "path": DEV_PATH,
        "normalized_path": NORMALIZED_DEV_FILE
    },
]
for path in paths:
    import_path = path["path"]
    save_path = path["normalized_path"]
    data = import_json(import_path)[:4000]
    c = 0
    with torch.no_grad():
        for d in data:

            # Tokeniza os título e conteúdo 
            tokenized_title = tokenizer.tokenize(d["title"])
            tokenized_content = tokenizer.tokenize(d["content"])

            title = encoder.mean_pooling(
                encoder.encode(tokenized_title),
                tokenized_title["attention_mask"]
            ).squeeze()
            content = encoder.mean_pooling(
                encoder.encode(tokenized_content),
                tokenized_content["attention_mask"]
            ).squeeze()

            example = {
                "title":title,
                "content":content,
                "label":torch.tensor(d["label"], dtype=torch.long)
            }

            # # 5) Vou salvar tudo em um arquivo
            torch.save(
                example,
                save_path + NORMALIZED_SUFIX_FILE + str(c)
            )
            c += 1
