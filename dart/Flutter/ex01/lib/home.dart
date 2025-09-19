import 'package:flutter/material.dart';

class Home extends StatefulWidget{
  const Home({super.key});

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home>{
  String _texto = "Clique abaixo para gerar uma nova frase.";
  List<String> frases = [
    "Opa",
    "parpiaoisaoi",
    "skodhaiosdhao"
  ];

  @override
  Widget build(BuildContext context){
    return Scaffold(
        appBar:AppBar(
          title: Text(
            "Frases aleatórias", 
            style: TextStyle(
              color: Colors.white,
              fontWeight: FontWeight.bold
            ) 
          ),
          backgroundColor: Colors.blue,
        ),
        body:Center(
          child: Column(
            children: [
              Image.asset("images/img.png"),
              Text(
                this._texto
              ),
              ElevatedButton(
                child: Text("Nova Frase"),
                onPressed: (){
                  
                }
              )
            ]
          )
        )
      );
  }
}