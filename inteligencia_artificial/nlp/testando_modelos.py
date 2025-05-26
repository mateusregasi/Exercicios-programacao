from ollama import chat
from pydantic import BaseModel
from typing import Literal

modelo = 'qwen3:14b'
materiais = ['celular', 'notebook', 'telefone', 'corpo humano']

 # Pega os tipos de material e coloca em uma classe
tipos_material = (
    'eletronico grande porte',
    'eletronico medio porte',
    'eletronico pequeno porte',
    'pilhas ou baterias',
    'plastico',
    'metal',
    'material organico',
    'vidro',
    'tecido',
    'moveis',
    'papel ou papelao',
    'lixo hospitalar',
    'madeira',
    'material nao reciclavel'
)

class PropriedadesTipoMaterial(BaseModel):
    tipo: Literal[tipos_material]

for material in materiais:

    pergunta = f"Classifique o material {material} com algum dos tipos: {', '.join(tipos_material)}. A classificação deve ser feita levando em consideração as características do material. A resposta deve ser dada em formato JSON com a propriedade 'tipo'."
    print(pergunta)

    mensagem = [{
        'role': 'user',
        'content': pergunta,
    }]

    prompt = chat(model=modelo, messages=mensagem, format=PropriedadesTipoMaterial.model_json_schema(), options={
        'temperature':1
    })['message']['content']
    print(prompt)