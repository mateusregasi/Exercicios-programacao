import json

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

dev_data = import_json("dev_json/")
train_data = import_json("train_json/")

with open("json_dev_data.json", "w") as f:
    json.dump(dev_data, f)
with open("json_train_data.json", "w") as f:
    json.dump(dev_data, f)