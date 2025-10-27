import 'package:flutter/material.dart';
import 'package:pokedex/components/pokemonalert.dart';
import 'package:pokedex/model/pokemon.dart';
import 'package:pokedex/utils/conf.dart';
import 'dart:convert';

class PaginaNome extends StatefulWidget {
  const PaginaNome({super.key});

  @override
  State<PaginaNome> createState() => _PaginaNomeState();
}

class _PaginaNomeState extends State<PaginaNome> {
  TextEditingController nomePokemon = TextEditingController();
  
  paginaPokemon(String nome) async{
    nome = utf8.decode(utf8.encode(nome.toLowerCase()));
    String uri = "https://pokeapi.co/api/v2/pokemon-species/${nome}";
    Pokemon pokemon = Pokemon.pelaURIEspecie(uri);
    await pokemon.pegaPokemonComCadeia(uri);
    PokemonAlert(pokemon: pokemon).chamarPokedex(context);
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.end,
      crossAxisAlignment: CrossAxisAlignment.center,
      children: [
        Container(
          child: Image.asset("img/forest.png"),
        ),
        Padding(padding: EdgeInsets.all(MediaQuery.of(context).size.height * 0.1)),
        Container(
          child: TextField(
            style: TextStyle(
              color: Colors.white,
            ),
            controller: nomePokemon,
            onSubmitted: paginaPokemon,
            decoration: InputDecoration(
              hintText: "Digite um pokemon...",
              hintStyle: TextStyle(
                color: Colors.white,
                fontWeight: FontWeight.normal
              ),
              border: OutlineInputBorder(
                borderRadius: BorderRadius.all(Radius.circular(30)),
                borderSide: BorderSide(
                  width: 0,
                  style: BorderStyle.none
                )
              ),
              filled: true,
              contentPadding: EdgeInsets.all(20),
              fillColor: Conf.nonDestachColor2
            ),
          ),
          width: MediaQuery.of(context).size.width * 0.9,
          color: Colors.transparent,
        ),
        Padding(padding: EdgeInsets.all(30))
      ],
    );
  }
}