import 'package:flutter/material.dart';
import 'package:pokedex/components/pokemonalert.dart';
import 'package:pokedex/model/pokemon.dart';

class PokemonListTile extends StatefulWidget {
  final String uri;
  const PokemonListTile({super.key, required this.uri});

  @override
  State<PokemonListTile> createState() => PokemonListTileState();
}

class PokemonListTileState extends State<PokemonListTile> {
  final double tamanhoImagem = 100;
  late Pokemon pokemon;

  @override
  void initState() {
    pokemon = Pokemon.pelaURIEspecie(widget.uri);
    super.initState();
  }
  
  @override
  Widget build(BuildContext context) {
    return FutureBuilder(
      future: pokemon.pegaPokemonComCadeia(widget.uri), 
      builder: (context, snapshot){
        if(snapshot.hasData){
          return Container(
            child: ElevatedButton(
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                children: [
                  Container(
                    child: Image.network(
                      pokemon.spriteURL,
                      fit: BoxFit.contain,
                      filterQuality: FilterQuality.none,
                    ),
                    height: tamanhoImagem,
                    width: tamanhoImagem,
                  ),
                  Text(
                    "${pokemon.nome}",
                    style: TextStyle(
                      fontSize: 30,
                      color: Colors.black
                    ),
                  ),
                  Icon(Icons.visibility_rounded)
                ],
              ),
              style: ElevatedButton.styleFrom(
                side: BorderSide(width: 0, color: Colors.white),
                elevation: 1,
                iconColor: Colors.black,
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.all(Radius.zero)
                )
              ),
              onPressed: () => PokemonAlert(pokemon: pokemon).chamarPokedex(context),
            )
          );
        }
        return CircularProgressIndicator();
      }
    );
    
    
    
  }
}