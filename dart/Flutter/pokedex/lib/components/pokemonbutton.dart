import 'package:flutter/material.dart';

class PokemonButton extends StatefulWidget {
  final double tamanhoQuadrado;
  final Color color;
  final Color backgroundColor;
  IconData? icon;
  String? text;
  int? fontSize;
  GestureTapCallback onTap;

  PokemonButton({
    super.key, 
    this.icon, 
    this.text,
    required this.color,
    required this.backgroundColor,
    this.fontSize,
    required this.onTap,
    required this.tamanhoQuadrado
  });

  @override
  State<PokemonButton> createState() => PokemonButtonState();
}

class PokemonButtonState extends State<PokemonButton> {
  @override
  Widget build(BuildContext context) {
    List<Widget> conteudo = [];
    if(widget.icon != null) conteudo.add(
      Icon(
        widget.icon!,
        color: Colors.white
      )
    );
    if(widget.text != null) conteudo.add(
      Text(
        widget.text!,
        style: TextStyle(
          color: widget.color,
          fontWeight: FontWeight.bold
        )
      )
    );

    return GestureDetector(
      child: Container(
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: conteudo
          ) 
          
        ),
        width: widget.tamanhoQuadrado,
        height: widget.tamanhoQuadrado,
        decoration: BoxDecoration(
          color: widget.backgroundColor,
          borderRadius: BorderRadius.all(
            const Radius.circular(20.0)
          ),
          boxShadow: [
            BoxShadow(
              color: Colors.black.withAlpha(50),
              spreadRadius: 1,
              blurRadius: 3,
              offset: Offset(0, 3)
            )
          ]
        ),
      ),
      onTap: widget.onTap,
    );
  }
}