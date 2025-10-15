import 'package:flutter/services.dart';
import 'package:flutter/material.dart';
import 'package:letroso/utilidades/status.dart';

class Linha extends StatefulWidget {
  final int n;
  final double larguraJanela;

  const Linha({
    super.key, 
    required this.n, 
    required this.larguraJanela
  });

  @override
  State<Linha> createState() => LinhaState();
}

class LinhaState extends State<Linha> {
  List<Card> lista = [];
  List<TextEditingController> controladores = [];
  List<FocusNode> focos = [];
  String chute = "";
  int j = 0;

  double tamanhoFonte = 30;
  double tamanhoQuadrado = 42;

  void proximo(String c){
    j = (j + 1) % widget.n;
    FocusScope.of(context).requestFocus(focos[j]);
  }

  @override
  void initState() {
    super.initState();
    calculaTamanho(widget.larguraJanela);
    for(int i=0; i<widget.n; i++){
      controladores.add(
        TextEditingController()
      );
      controladores[i].addListener((){
        
      });

      focos.add(
        FocusNode()
      );

      lista.add(
        Card(
          child: SizedBox(
            width: tamanhoQuadrado,
            height: tamanhoQuadrado,
            child: Center(
              child: TextField(
                decoration: const InputDecoration(
                  counter: SizedBox.shrink(),
                  border: InputBorder.none,
                  contentPadding: EdgeInsets.all(0), 
                  isCollapsed: true,
                ),
                textAlign: TextAlign.center,
                textAlignVertical: TextAlignVertical.center,
                maxLength: 1,
                showCursor: false,
                controller: controladores[i],
                focusNode: focos[i],
                onChanged: proximo,
                onTap: () => j = i,
                style: TextStyle(
                  fontSize: tamanhoFonte,
                  height: 1.0, 
                ),
                strutStyle: const StrutStyle(
                  forceStrutHeight: true,
                  height: 1.0,
                ),
              ),
            ),
          ),
          elevation: 3,
          color: Colors.white,
          shape: BeveledRectangleBorder(
            borderRadius: BorderRadius.circular(2)
          ),
        )
      );
    }
  }

  void calculaTamanho(double size){
    tamanhoQuadrado = size / widget.n - (widget.n - 2) * 15 / widget.n;
    tamanhoFonte = size / widget.n - (widget.n - 2) * 33 / widget.n;
  }

  String pegarPalavra(){
    for(int i=0; i<widget.n; i++){
      chute += this.controladores[i].text;
    }
    return chute!.toLowerCase();
  }

  void aplicarMascara(List<Status> mascara){
    Color cor;
    for(int i=0; i<widget.n; i++){
      switch(mascara[i]){
        case Status.errou:
          cor = Colors.red[300]!;
          break;
        case Status.letra:
          cor = Colors.yellow[300]!;
          break;
        case Status.posicao:
          cor = Colors.green[300]!;
      }
      lista[i] = Card(
        child: SizedBox(
          width: tamanhoQuadrado,
          height: tamanhoQuadrado,
          child: Center(
            child: Text(
              chute.characters.elementAt(i),
              style: TextStyle(
                color: Colors.white,
                fontSize: tamanhoFonte
              ),
            ),
          ),
        ),
        elevation: 3,
        color: cor,
        shape: BeveledRectangleBorder(
          borderRadius: BorderRadius.circular(2)
        )
      );
    }
    setState(() {});
  }

  @override
  Widget build(BuildContext context){
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
      children:lista
    );
  }
}