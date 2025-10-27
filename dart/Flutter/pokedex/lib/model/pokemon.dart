import 'package:http/http.dart';
import 'dart:convert';
import 'package:pokedex/utils/conf.dart';

class Pokemon{
  late String uri;
  late String uriEspecie;
  late Map<dynamic,dynamic> dados;
  late Map<dynamic,dynamic> dadosEspecie;

  late int numero;
  late String nome;
  Set<String> tipos = {}; 
  late String spriteURL;
  late int altura;
  late int peso;
  late bool bebe;
  late bool lendario;
  late bool mitico;
  late int vida;
  late int ataque;
  late int defesa;
  late int ataqueEspecial;
  late int defesaEspecial;
  late int velocidade;

  late List<Pokemon> cadeiaEvolutiva = [];

  Pokemon(){}

  // Pokemon.pelaURI(String uri){
  //   this.uri = uri;
  //   uri = uri.replaceAll(RegExp("pokemon"), "pokemon-species");
  //   uriEspecie = uri;
  //   print(uri + " " + uriEspecie);
  // }

  Pokemon.pelaURIEspecie(String uri) {
    uriEspecie = uri;
    uri = uri.replaceAll(RegExp("-species"), "");
    this.uri = uri;
  }

  Pokemon.peloNumero(int n){
    numero = n;
    uri = Conf.pokemonURI + "pokemon/" + n.toString();
    uri = Conf.pokemonURI + "pokemon_species/" + n.toString();
  }

  Pokemon.peloNome(String nome){
    uri = Conf.pokemonURI + "pokemon/" + nome;
    uriEspecie = Conf.pokemonURI + "pokemon-species/" + nome;
  }

  Future<Map<dynamic, dynamic>> requisicaoPokemon(String u) async{
    Response resposta = await get(Uri.parse(u));
    dados = jsonDecode(resposta.body);
    return dados;
  }
  Future<Map<dynamic, dynamic>> requisicaoEspeciePokemon(String u) async{
    Response resposta = await get(Uri.parse(u));
    dadosEspecie = jsonDecode(resposta.body);
    return dadosEspecie;
  }

  Future<Map> pegaPokemon(String u) async {
    await requisicaoEspeciePokemon(u);
    await requisicaoPokemon(u);
    return dados;
  }

  void parsePokemonSemEspecie(){
    nome = dados["name"];
    for(dynamic d in dados["types"]){
      tipos.add(d["type"]["name"]);
    }
    spriteURL = dados["sprites"]["front_default"];
    altura = dados["height"];
    peso = dados["weight"]; 
    
    Map<String,dynamic> status = {};
    for(dynamic s in dados["stats"]){
      status[s["stat"]["name"]] = s["base_stat"];
    }

    vida = status["hp"];
    ataque = status["attack"];
    defesa = status["defense"];
    ataqueEspecial = status["special-attack"];
    defesaEspecial = status["special-defense"];
    velocidade = status["speed"];
  }

  void parsePokemonComEspecie(){
    bebe = dadosEspecie["is_baby"];
    lendario = dadosEspecie["is_legendary"];
    mitico = dadosEspecie["is_mythical"];
  }

  Future parsePokemonComCadeia() async{
    parsePokemon();
    return await pegaCadeiaEvolutiva();
  }
  Future<Map> pegaPokemonComCadeia(String u) async {
    await requisicaoEspeciePokemon(u);
    u = u.replaceAll(RegExp("-species"), "");
    await requisicaoPokemon(u);
    await parsePokemonComCadeia();
    return dados;
  }

  void parsePokemon(){
    parsePokemonSemEspecie();
    parsePokemonComEspecie();
  }

  Future<List<Pokemon>> pegaCadeiaEvolutiva() async{
    final String urlCE = dadosEspecie["evolution_chain"]["url"];
    Map cadeia = jsonDecode((await get(Uri.parse(urlCE))).body)["chain"];

    while(true){
      final String name = cadeia["species"]["name"];
      final Pokemon p = Pokemon.peloNome(name);
      
      await p.requisicaoPokemon(p.uri);
      p.parsePokemonSemEspecie();

      cadeiaEvolutiva.add(p);

      if(cadeia["evolves_to"] != null && (cadeia["evolves_to"] as List).isNotEmpty){
        cadeia = cadeia["evolves_to"][0];
      } else break;
    }
    
    return cadeiaEvolutiva;
  }

}