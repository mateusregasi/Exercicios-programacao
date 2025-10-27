import 'package:flutter/material.dart';
import 'package:pokedex/model/pokemon.dart';
import 'package:pokedex/utils/conf.dart';

class PokemonAlert{
  PokemonAlert({required this.pokemon});
  Pokemon pokemon;
  final double tamanhoImagem = 100;
  final double tamanhoNomePokemon = 30;
  final double tamanhoTipoPokemon = 30;
  final double tamanhoTagPokemon = 20;
  final double tamanhoEstatisticas = 20;
  final double gap = 15;

  late Map estatisticas1 = {
      "Pontos de Vida": pokemon.vida,
      "Ataque": pokemon.ataque,
      "Ataque-Especial": pokemon.ataqueEspecial,
      "Defesa-Especial": pokemon.defesaEspecial,
      "Velocidade": pokemon.velocidade,
  };
  late Map estatisticas2 = {
    "Altura": pokemon.altura,
    "Peso": pokemon.peso
  };

  Widget mostrarCadeiaEvolutiva(List<Pokemon> dados){
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
      children: dados.map(
        (elemento) => Container( 
          child: Image.network(
            elemento.spriteURL,
            fit: BoxFit.cover,
          ),
          width: tamanhoImagem * 0.4,
          height: tamanhoImagem * 0.4,
        )
      ).toList(),
    );
  }

  Widget linhaDividida(dynamic t1, dynamic t2){
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        Text(
          "${t1}:",
          style: TextStyle(
            color: Conf.nonDestachColor,
            fontSize: tamanhoEstatisticas
          )
        ),Text(
          "${t2}",
          style: TextStyle(
            color: Conf.nonDestachColor,
            fontSize: tamanhoEstatisticas
          )
        ),
      ]
    );
  }

  void chamarPokedex(BuildContext context){
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        icon: Icon(
          Icons.catching_pokemon_rounded,
          color: Conf.primaryColor,
        ),
        content: Column(
          children: [
            Column(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Container(
                  height: tamanhoImagem * 3,
                  width: tamanhoImagem * 3,
                  child: Image.network(
                    pokemon.spriteURL,
                    filterQuality: FilterQuality.none,
                    fit: BoxFit.cover,
                  ),
                ),
                Column(
                  mainAxisAlignment: MainAxisAlignment.start,
                  children: [
                    Text(
                      pokemon.nome,
                      style: TextStyle(
                        fontSize: tamanhoNomePokemon,
                        fontWeight: FontWeight.bold
                      ),
                    ),
                    Row(
                      crossAxisAlignment: CrossAxisAlignment.center,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: pokemon.tipos.map(
                        (tipo) => Padding(
                          padding: EdgeInsets.all(gap),
                          child: Text(
                            tipo,
                            style: TextStyle(
                              color: Conf.nonDestachColor,
                              fontSize: tamanhoTagPokemon
                            ),
                          ),
                        )
                      ).toList(),
                    )
                  ] + (pokemon.bebe ? [Text("(bebe)")] : []),
                ), 
              ]
            ),

            Column(
              mainAxisAlignment: MainAxisAlignment.start,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: estatisticas1.keys.map((chave){
                return Container(
                  width: MediaQuery.of(context).size.width * 0.5,
                  child: linhaDividida(chave, estatisticas1[chave]),
                );
              }).toList(),
            ),
            Padding(padding: EdgeInsets.all(gap)),
            Column(
              mainAxisAlignment: MainAxisAlignment.start,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: estatisticas2.keys.map((chave){
                return Container(
                  width: MediaQuery.of(context).size.width * 0.5,
                  child: linhaDividida(chave, estatisticas2[chave]),
                );
              }).toList(),
            ),

            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: pokemon.cadeiaEvolutiva.map(
                (poke) => Container(
                  width: tamanhoImagem * 0.8,
                  height: tamanhoImagem * 0.8,
                  child: Image.network(
                    poke.spriteURL,
                    fit: BoxFit.cover,
                    filterQuality: FilterQuality.none,
                  ),
                )
              ).toList(),
            ),

            Padding(padding: EdgeInsets.all(gap)),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Text(
                  "Lendario",
                  style: TextStyle(
                    color: pokemon.lendario ? Conf.primaryColor : Conf.primaryColor2,
                    fontWeight: pokemon.lendario ? FontWeight.bold : FontWeight.normal
                  ),
                ),
                Padding(padding: EdgeInsets.only(
                  left: gap * 0.5,
                  right: gap * 0.5,
                )),
                Text(
                  "Mítico",
                  style: TextStyle(
                    color: pokemon.mitico ? Conf.primaryColor : Conf.primaryColor2,
                    fontWeight: pokemon.mitico ? FontWeight.bold : FontWeight.normal
                  ),
                )
              ],
            )
               
          ],
        ),
        actions: [
          IconButton(
            onPressed: () => Navigator.pop(context), 
            icon: BackButtonIcon()
          )
        ],
        actionsAlignment: MainAxisAlignment.start,
        actionsOverflowDirection: VerticalDirection.up,
        actionsOverflowAlignment: OverflowBarAlignment.start,
      ),
    );
  }
}