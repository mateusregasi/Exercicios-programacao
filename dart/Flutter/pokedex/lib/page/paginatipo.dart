import 'package:flutter/material.dart';
import 'package:http/http.dart';
import 'package:pokedex/components/pokemonbutton.dart';
import 'dart:convert';

import 'package:pokedex/utils/conf.dart';
import 'paginapesquisa.dart';

class PaginaTipo extends StatefulWidget {
  const PaginaTipo({super.key});

  @override
  State<PaginaTipo> createState() => _PaginaTipoState();
}

class _PaginaTipoState extends State<PaginaTipo> {
  late double tamanhoQuadrado;
  Map<String,Map> tipos = {
    "normal":{
      "nome":"Normal",
      "cor":Colors.brown[100],
      "icon":Icons.circle_outlined
    },
    "fighting":{
      "nome":"Lutador",
      "cor":Colors.red[600],
      "icon":Icons.waving_hand_sharp
    },
    "flying":{
      "nome":"Voador",
      "cor":Colors.deepPurpleAccent[100],
      "icon":Icons.airplanemode_active
    },
    "poison":{
      "nome":"Venenoso",
      "cor":Colors.deepPurpleAccent[700],
      "icon":Icons.coronavirus
    },
    "ground":{
      "nome":"Terra",
      "cor": Colors.yellow[300],
      "icon":Icons.terrain
    },
    "rock":{
      "nome":"Pedra",
      "cor": Colors.amber[400],
      "icon": Icons.landslide_rounded
    },
    "bug":{
      "nome":"Inseto",
      "cor": Colors.lightGreen[400],
      "icon":Icons.bug_report_rounded
    },
    "ghost":{
      "nome":"Fantasma",
      "cor":Colors.purple[900],
      "icon":Icons.face_3_rounded
    },
    "steel":{
      "nome":"Ferro",
      "cor": Colors.grey[600],
      "icon":Icons.settings
    },
    "fire":{
      "nome":"Fogo",
      "cor": Colors.orange[600],
      "icon":Icons.whatshot
    },
    "water":{
      "nome":"Água",
      "cor":Colors.blue,
      "icon":Icons.water_drop_outlined
    },
    "grass":{
      "nome":"Grama",
      "cor": Colors.green,
      "icon":Icons.grass
    },
    "eletric":{
      "nome":"Elétrico",
      "cor": Colors.yellow,
      "icon":Icons.electric_bolt_rounded
    },
    "psychic":{
      "nome":"Psíquico",
      "cor":Colors.pink[400],
      "icon":Icons.cyclone_rounded
    },
    "ice":{
      "nome":"Gelo",
      "cor": Colors.blue[100],
      "icon":Icons.severe_cold_rounded
    },
    "dragon":{
      "nome":"Dragão",
      "cor":Colors.purple[900],
      "icon":Icons.storm
    },
    "feary":{
      "nome":"Fada",
      "cor": Colors.pink[100],
      "icon":Icons.star_purple500_rounded
    },
    "dark":{
      "nome":"Sombrio",
      "cor": Colors.grey[900],
      "icon":Icons.dark_mode_outlined
    },
  };

  paginaPokemon(String type, Map<dynamic, dynamic> tipo) async{
      Navigator.push(
        context,
        MaterialPageRoute(
          builder: (context) => PaginaPesquisa(
            uri:"https://pokeapi.co/api/v2/type/${type}",
            texto:"Tipo: ${tipo["nome"]}"
          )
        )
      );
    }
  
  Widget construirBotoes(){
    List<Widget> lista = [];
    List<Widget> linhas = [];
    int i = 0;
    for(String type in tipos.keys){
      i++;
      linhas.add(
        PokemonButton(
          icon: tipos[type]!["icon"],
          color: Colors.white,
          text: tipos[type]!["nome"],
          tamanhoQuadrado: tamanhoQuadrado,
          backgroundColor: tipos[type]!["cor"],
          onTap: () => paginaPokemon(type, tipos[type]!),
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