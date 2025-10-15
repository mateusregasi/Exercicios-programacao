import 'package:flutter/material.dart';
import 'utilidades/configuracoes.dart';

class PaginaRanking extends StatefulWidget{
  const PaginaRanking({super.key});

  @override
  State<PaginaRanking> createState() => _PaginaRankingState();
}

class TextoRanking extends StatelessWidget{
  final String? texto;
  const TextoRanking(this.texto, {super.key});
  

  @override
  Widget build(BuildContext context) {
    return Text(
      texto!,
      style: TextStyle(
        color: Colors.white,
        fontSize: 20
      ),
    );
  }
}

class _PaginaRankingState extends State<PaginaRanking>{
  _PaginaRankingState({Key? key});

  @override
  Widget build(BuildContext context) {
    return Center(
      child: SizedBox(
        height: MediaQuery.of(context).size.height * 0.5,
        width: MediaQuery.of(context).size.width * 0.9,
        child: Card(
          color: Configuracoes.corPrincipal2,
          child: Column(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Padding(padding: EdgeInsets.all(10)),
              Text(
                "Ranking",
                style: TextStyle(
                  fontSize: 40,
                  fontWeight: FontWeight.w900,
                  color: Colors.white,
                  decoration: TextDecoration.underline,
                  decorationColor: Colors.white
                ),
              ),
              Padding(padding: EdgeInsets.all(10)),
              TextoRanking("jogador1.........................pontuação"),
              TextoRanking("jogador2.........................pontuação"),
              TextoRanking("jogador3.........................pontuação"),
              TextoRanking("............................................................"),
              TextoRanking("............................................................"),
              TextoRanking("jogadorn+1.....................pontuação"),
              TextoRanking("jogadoratual...................pontuação"),
              TextoRanking("jogadorn-1.....................pontuação"),
              TextoRanking("............................................................"),
              TextoRanking("............................................................"),
              Padding(padding: EdgeInsets.all(30)),
            ],
          ),
        ),
      ),
    );
  }

}