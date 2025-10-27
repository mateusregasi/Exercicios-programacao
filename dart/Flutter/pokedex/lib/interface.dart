import 'package:flutter/material.dart';
import "package:pokedex/page/paginanome.dart";
import "package:pokedex/page/paginatipo.dart";
import "utils/conf.dart";
import "page/paginageracao.dart";
import "page/paginahabitat.dart";

class Interface extends StatefulWidget {
  const Interface({super.key});

  @override
  State<Interface> createState() => _InterfaceState();
}

class _InterfaceState extends State<Interface> {
  int indicePagina = 0;
  late PageController controladorPagina;

  void trocarPagina(int i){
    indicePagina = i;
    controladorPagina.animateToPage(
      indicePagina, 
      duration: Duration(
        milliseconds: 100
      ), 
      curve: Curves.bounceInOut
    );
    setState((){});
  }

  @override
  void initState() {
    controladorPagina = PageController(initialPage: indicePagina);
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Conf.primaryColor,
        foregroundColor: Colors.white,
        toolbarHeight: 80,
        title: Title(
          color: Colors.white, 
          child: Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(
                  Icons.catching_pokemon_rounded,
                ),
                Text(
                  Conf.title,
                  style: TextStyle(
                    fontWeight: FontWeight.bold,
                    fontSize: 30
                  ),
                )
              ],
            ),
          )
        ),
      ),
      body: PageView(
        controller: controladorPagina,
        children: [
          PaginaGeracao(),
          PaginaTipo(),
          PaginaHabitat(),
          PaginaNome(),
        ],
      ),
      bottomNavigationBar: BottomNavigationBar(
        backgroundColor: Conf.primaryColor,
        selectedItemColor: Conf.primaryColor,
        unselectedItemColor: Conf.primaryColor2,
        currentIndex: indicePagina,
        onTap: trocarPagina,
        items: [
          BottomNavigationBarItem(
            label: "Geração",
            icon: Icon(Icons.format_list_numbered)
          ),
          BottomNavigationBarItem(
            label: "Tipo",
            icon: Icon(Icons.grass)
          ),
          BottomNavigationBarItem(
            label: "Habitat",
            icon: Icon(Icons.forest_rounded)
          ),
          BottomNavigationBarItem(
            label: "Pesquisar",
            icon: Icon(Icons.search_rounded),
          ),
        ],
      ),
    );
  }
}