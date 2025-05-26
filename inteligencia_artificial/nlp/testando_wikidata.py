import requests

def buscar_wikidata(term, lang='en'):
    url = f"https://www.wikidata.org/w/api.php"
    params = {
        'action': 'wbsearchentities',
        'search': term,
        'language': lang,
        'format': 'json',
    }
    response = requests.get(url, params=params)
    data = response.json()

    resultados = []
    for item in data.get('search', []):
        resultados.append({
            'id': item['id'],  # Q-code (ex: Q39629)
            'label': item.get('label'),
            'description': item.get('description'),
            'match': item.get('match', {}).get('text'),
            'url': f"https://www.wikidata.org/wiki/{item['id']}"
        })
    return resultados

resultados = buscar_wikidata("notebook")
for r in resultados:
    print(f"{r['label']} ({r['id']}): {r['description']}")