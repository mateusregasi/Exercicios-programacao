import 'package:flutter/material.dart';
import 'package:http/http.dart';
import 'package:pokedex/components/pokemonbutton.dart';
import 'dart:convert';

import 'package:pokedex/utils/conf.dart';
import 'paginapesquisa.dart';

class PaginaGeracao extends StatefulWidget {
  const PaginaGeracao({super.key});

  @override
  State<PaginaGeracao> createState() => _PaginaGeracaoState();
}

class _PaginaGeracaoState extends State<PaginaGeracao> {
  late double tamanhoQuadrado;

  // generation -> generation/n -> main_region url -> pokedexes[0] -> pokemon_entries
  Future<Map> pegaGeracoes() async{
    Uri uri = Uri.parse(Conf.pokemonURI + "generation");
    Response resposta = await get(uri);
    return jsonDecode(resposta.body);
  }

  paginaPokemon(String geracaoUrl, int i) async{
      Response resposta = await get(Uri.parse(geracaoUrl));
      Response resposta2 = await get(Uri.parse(jsonDecode(resposta.body)["main_region"]["url"]));
      String uri = jsonDecode(resposta2.body)["pokedexes"][0]["url"]; 
      Navigator.push(
        context,
        MaterialPageRoute(
          builder: (context) => PaginaPesquisa(
            uri:uri,
            texto:"Geração ${i+1}"
          )
        )
      );
    }
  
  Widget construirBotoes(Map<dynamic, dynamic> dados){
    List<Widget> lista = [];
    List<Widget> linhas = [];

    for(int i=0; i<dados["count"]; i++){
      linhas.add(
        PokemonButton(
          text: "Gen ${i+1}",
          color: Colors.white,
          tamanhoQuadrado: tamanhoQuadrado,
          backgroundColor: Conf.primaryColor3,
          onTap: () => paginaPokemon(dados["results"][i]["url"], i),
        )
      );
      if((i+1) % 3 == 0){
        lista.add(
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: linhas,
          )
        );
        lista.add(
          Padding(
            padding: EdgeInsets.all(
              tamanhoQuadrado * 0.1
            )
          )
        );
        linhas = [];
      } else{
        linhas.add(
          Padding(
            padding: EdgeInsets.all(
              tamanhoQuadrado * 0.1
            )
          )
        );
      }
    }

    return 
    Column(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      crossAxisAlignment: CrossAxisAlignment.center,
      children: lista,
    );
  }

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    tamanhoQuadrado = MediaQuery.of(context).size.height * 0.1;
    return Center(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          FutureBuilder<Map>(
            future: pegaGeracoes(), 
            builder: (context, snapshot){
              if(snapshot.hasData){
                return construirBotoes(snapshot.data!);
              } 
              return CircularProgressIndicator();
            }
          ),
          Padding(
            padding: EdgeInsets.all(
              tamanhoQuadrado
            )
          )
        ],
      ),
    );
  }
}