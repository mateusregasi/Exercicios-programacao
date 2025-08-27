from ollama import chat
from pydantic import BaseModel
from typing import Literal

modelo = 'gemma3n:e4b'
materiais = {'celular':'eletronico pequeno porte', 'notebook':'eletronico medio porte', 'telefone':'eletronico medio porte', 'pilha':'eletronico pequeno porte'}

class MaterialPrompt(BaseModel):
    descarte: list[str]
    reciclagem: list[str]

for k, v in materiais.items():

    pergunta = f"Me dê maneiras adequadas de se descartar o material {k} levando em consideração que ele é um {v}. Quero também ideias criativas de se fazer reciclagem com esse material. Retorne em um arquivo JSON com as propriedades 'descarte' e 'reciclagem'."
    print(pergunta)

    mensagem = [{
        'role': 'user',
        'content': pergunta,
    }]

    prompt = chat(model=modelo, messages=mensagem, format=MaterialPrompt.model_json_schema(), options={
        'temperature':1
    })['message']['content']
    print(prompt)