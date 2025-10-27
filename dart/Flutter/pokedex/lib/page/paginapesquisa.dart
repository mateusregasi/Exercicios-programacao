import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:pokedex/utils/conf.dart';
import 'package:http/http.dart';

import 'package:pokedex/components/pokemonlisttile.dart';

class PaginaPesquisa extends StatefulWidget {
  final String uri;
  final String texto;
  const PaginaPesquisa({super.key, required this.uri, required this.texto});

  @override
  State<PaginaPesquisa> createState() => _PaginaPesquisaState();
}

class _PaginaPesquisaState extends State<PaginaPesquisa> {

  Future<Map<String, dynamic>> pegaPokemons() async {
    Uri uri = Uri.parse(widget.uri);
    Response resposta = await get(uri);
    return jsonDecode(resposta.body);
  }
  
  Widget construir(dynamic dados, Function f){
    return ListView.builder(
      itemCount: dados.length,
      itemBuilder: (context, i){
        return Container(
          height: MediaQuery.of(context).size.height * 0.1,
          child: PokemonListTile(
            uri:f(dados, i)
          ),
        );
      },
    );  
  }

  Widget construirListaPokedex(dynamic dados){
    return construir(dados, (dados, i) => dados[i]["pokemon_species"]["url"]);   
  }

  Widget construirListaTipo(dynamic dados){
    return construir(dados, (dados, i) => Conf.pokemonURI + "pokemon-species/" + dados[i]["pokemon"]["name"]);  
  }

  Widget construirListaHabitat(dynamic dados){
    return construir(dados, (dados, i) => Conf.pokemonURI + "pokemon-species/" + dados[i]["name"]);   
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Conf.primaryColor,
        foregroundColor: Colors.white,
        title: Title(
          color: Colors.white, 
          child: Text(
            widget.texto,
            style: TextStyle(
              fontWeight: FontWeight.bold,
              fontSize: 30
            ),
          )
        ),
      ),
      body: Container(
        height: MediaQuery.of(context).size.height,
        child: FutureBuilder(
          future: pegaPokemons(), 
          builder: (context, snapshot){
            if(snapshot.hasData){
              String path = widget.uri.substring(Conf.pokemonURI.length);
              if(path.contains("pokedex")){
                return construirListaPokedex(snapshot.data!["pokemon_entries"]);
              }
              else if(path.contains("type")){
                return construirListaTipo(snapshot.data!["pokemon"]);
              } else if(path.contains("habitat")){
                return construirListaHabitat(snapshot.data!["pokemon_species"]);
              }
            }
            return CircularProgressIndicator();
          }
        )
      )
    );
  }
}