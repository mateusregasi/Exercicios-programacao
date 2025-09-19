from ollama import chat
from pydantic import BaseModel
from typing import Literal

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

tipos_material = [
    'eletronico de pequeno porte',
    'eletronico de médio porte',
    'eletronico de grande porte',
    'pilhas ou baterias',
    'plástico',
    'alumínio',
    'material orgânico',
    'vidro',
    'tecido',
    'móveis',
    'papel ou papelão',
    'lixo hospitalar',
    'madeira',
    'material não reciclável'
]
tipos_material_string = ", ".join(tipos_material)

class PropriedadesTipoMaterial(BaseModel):
    tipo: Literal[tuple(tipos_material)]

for material in materiais:

    print(f"{f'material {material}':=^30}")
    
    messages=[{
        'role': 'user',
        'content': f"Classifique o material {material} com algum dos tipos: {tipos_material_string}. A classificação deve ser feita levando em consideração as características do material. A resposta deve ser dada em um JSON com a propriedade 'tipo'.",
    }]

    for r in chat(
                    model='qwen3:8b', 
                    messages=messages, 
                    stream=True,
                    format=PropriedadesTipoMaterial.model_json_schema()
        ):
        print(r['message']['content'], end='')
print('')