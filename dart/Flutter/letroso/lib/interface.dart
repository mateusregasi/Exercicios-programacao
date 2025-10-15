import "package:flutter/material.dart";
import "paginaconfiguracao.dart";
import "paginaranking.dart";
import 'utilidades/configuracoes.dart';
import "paginajogo.dart";
import 'componentes/botaonavbar.dart';

class Interface extends StatefulWidget{
  const Interface({super.key});
  
  @override
  State<StatefulWidget> createState() => _InterfaceState();
}
  
class _InterfaceState extends State<Interface>{
  _InterfaceState({Key? key});

  List<Widget> paginas = [
    PaginaRanking(),
    PaginaConfiguracao(),
  ];

  int paginaIndex = 1;
  late PageController controlador;
  
  void mudarTela(parametro){
    controlador.animateToPage(
      parametro, 
      duration: Duration(milliseconds: 100),
      curve: Curves.easeInCubic
    );
    paginaIndex = parametro;
    setState(() {
      
    });
  }

  void iniciarJogo(BuildContext context) {
  Navigator.push(
    context,
    MaterialPageRoute(
      builder: (context) => PaginaJogo(),
    ),
  );
}

  @override
  void initState(){
    super.initState();
    controlador = PageController(
      initialPage: this.paginaIndex
    );
  }
   

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Center(
              child: Text(
                "Letroso",
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  fontSize: 30,
                  color: Colors.white
                ),
              ),
          ),
          backgroundColor: Configuracoes.corPrincipal,
        ),
        body: PageView(
          controller: controlador,
          children: paginas,
        ),
        bottomNavigationBar: BottomAppBar(
          color: Configuracoes.corPrincipal,
          notchMargin: 5,
          shape: CircularNotchedRectangle(),
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              BotaoNavbar(
                Icons.list_alt, 
                "Ranking", 
                (){ mudarTela(0); }
              ),
              BotaoNavbar(
                Icons.menu, 
                "Configurações", 
                (){ mudarTela(1); }
              ),
            ],
          ) 
        ),
        floatingActionButton: FloatingActionButton(
          onPressed: () => iniciarJogo(context),
          backgroundColor: Configuracoes.corPrincipal,
          hoverColor: Configuracoes.corPrincipal2,
          foregroundColor: Configuracoes.corSecundaria,
          child: Icon(
            Icons.play_arrow,
            color: Colors.white,
            size: 50,
          ),
          shape: CircleBorder(),
        ),
        floatingActionButtonLocation: FloatingActionButtonLocation.centerDocked,
      );
  }
}