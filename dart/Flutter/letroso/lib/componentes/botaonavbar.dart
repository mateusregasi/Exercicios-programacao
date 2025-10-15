import "package:flutter/material.dart";


class BotaoNavbar extends StatelessWidget{
  IconData icone;
  String texto;
  GestureTapCallback funcao;
  Color cor = Colors.white;
  BotaoNavbar(this.icone, this.texto, this.funcao, {super.key});

  @override
  Widget build(BuildContext context) {
    return Container(
      width: MediaQuery.of(context).size.width * 0.42,
      height: MediaQuery.of(context).size.height * 1,
      child: TextButton.icon(
        label: Text(
          texto,
          style: TextStyle(
            color: cor
          ),
        ),
        icon: Icon(
          size: 30,
          icone,
          color: cor
        ),
        onPressed: funcao,
        style: ButtonStyle(
          tapTargetSize: MaterialTapTargetSize.padded
        ),
      )
    );
    
  }
}