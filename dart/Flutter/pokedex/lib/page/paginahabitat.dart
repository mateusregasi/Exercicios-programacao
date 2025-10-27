import 'package:flutter/material.dart';
import 'package:http/http.dart';
import 'package:pokedex/components/pokemonbutton.dart';
import 'dart:convert';
import 'package:pokedex/utils/conf.dart';
import 'paginapesquisa.dart';

class PaginaHabitat extends StatefulWidget {
  const PaginaHabitat({super.key});

  @override
  State<PaginaHabitat> createState() => _PaginaHabitatState();
}

class _PaginaHabitatState extends State<PaginaHabitat> {
  late double tamanhoQuadrado;
  Map<String,Map> habitats = {
    "cave":{
      "nome":"Caverna",
      "cor": Colors.grey[900],
      "icon":Icons.castle
    },
    "forest":{
      "nome":"Floresta",
      "cor": Colors.green,
      "icon":Icons.forest
    },
    "grassland":{
      "nome":"Campo",
      "cor": Colors.greenAccent,
      "icon":Icons.grass
    },
    "mountain":{
      "nome":"Montanha",
      "cor": Colors.grey,
      "icon":Icons.terrain
    },
    "rare":{
      "nome":"Terreno Raro",
      "cor": Colors.purple,
      "icon":Icons.star_border_rounded
    },
    "rough-terrain":{
      "nome":"Terreno Difícil",
      "cor": Colors.grey[700],
      "icon":Icons.landslide_rounded
    },
    "sea":{
      "nome":"Oceano",
      "cor": Colors.blue,
      "icon":Icons.water_rounded
    },
    "urban":{
      "nome":"Urbano",
      "cor": Colors.blueGrey,
      "icon":Icons.location_city_rounded
    },
    "water-edge":{
      "nome":"Praia",
      "cor": Colors.yellow,
      "icon":Icons.sunny
    },
  };

  paginaPokemon(String nome_habitat, Map<dynamic, dynamic> habitat) async{
      Navigator.push(
        context,
        MaterialPageRoute(
          builder: (context) => PaginaPesquisa(
            uri:"https://pokeapi.co/api/v2/pokemon-habitat/${nome_habitat}",
            texto:"Habitat: ${habitat["nome"]}"
          )
        )
      );
    }
  
  Widget construirBotoes(){
    List<Widget> lista = [];
    List<Widget> linhas = [];
    int i = 0;
    for(String habitat in habitats.keys){
      i++;
      linhas.add(
        PokemonButton(
          icon:habitats[habitat]!["icon"],
          color:Colors.white,
          text:habitats[habitat]!["nome"],
          backgroundColor:habitats[habitat]!["cor"],
          onTap: () => paginaPokemon(habitat, habitats[habitat]!),
          tamanhoQuadrado: tamanhoQuadrado
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

    lista.add(
      Padding(
        padding: EdgeInsets.all(
          tamanhoQuadrado * 0.5
        )
      )
    );

    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
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
      child: construirBotoes()
    );
  }
}