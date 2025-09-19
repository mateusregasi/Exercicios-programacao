from ollama import chat
from pydantic import BaseModel
from typing import Literal
from deep_translator import GoogleTranslator
from json import loads

modelo = 'qwen3:14b'
modelo2 = 'qwen3:4b'
materiais = ['celular', 'notebook', 'telefone', 'corpo humano']
tradutor = GoogleTranslator(source='pt', target='en')
tradutor2 = GoogleTranslator(source='en', target='pt')

 # Pega os tipos de material e coloca em uma classe
tipos_material = (
    'small port eletronic',
    'medium port eletronic',
    'large port eletronic',
    'plastic',
    'metal',
    'organic material',
    'glass',
    'tissue',
    'forniture',
    'papers or cardboards',
    'hospital waste',
    'wood',
    'non-reciclable material'
)

class PropriedadesTipoMaterial(BaseModel):
    type: Literal[tipos_material]

class MaterialPrompt(BaseModel):
    discard: list[str]
    recycling: list[str]

class Traducao(BaseModel):
    translation: str

for m in materiais:

    pergunta = f"Translate the word '{m}' to english considering that the word may be a cognate or have a diferent semantic in portuguese. Also considere that the i want descart this material and i want that this material to be preferably eletronic."
    mensagem = [{
        'role':'user',
        'content':pergunta
    }]
    material = loads(chat(model=modelo, messages=mensagem, format=Traducao.model_json_schema())['message']['content'])['translation']
    print(material)

    #pergunta = f"Classifique o material {material} com algum dos tipos: {', '.join(tipos_material)}. A classificação deve ser feita levando em consideração as características do material. A resposta deve ser dada em um JSON com a propriedade 'tipo' e também deve constar o por quê da resposta dada. Leve em conta a maneira como o matetial é escrito originalmente."
    pergunta = f"Classify the material {material} with some of this types: {', '.join(tipos_material)}. The classefication may be using the type of material characteristics. The response may be given in JSON format, with a property named 'type'."
   
    mensagem = [{
        'role': 'user',
        'content': pergunta,
    }]

    classificacao = loads(chat(model=modelo, messages=mensagem, format=PropriedadesTipoMaterial.model_json_schema())['message']['content'])['type']
    print(classificacao)

    # Pergunta pra IA
    mensagem=[{
        'role': 'user',
        'content': f"Return a JSON file. In the JSON property disposal, I want ways to preferentially dispose of the material {material}. In the recycling property, I want creative ways to recycle the material {material}. Consider that the material is of type {classificacao}. All texts in the JSON properties should follow the characteristics of the material {material}.",
    }]
    print(mensagem)
    prompt = chat(model=modelo2, messages=mensagem, format=MaterialPrompt.model_json_schema())['message']['content']
    print(tradutor2.translate(prompt))

