import 'package:flutter/material.dart';
import 'dart:math';

class Home extends StatefulWidget{
  const Home({super.key});

  @override
  State<StatefulWidget> createState(){
    return _HomeState();
  }
}

class _HomeState extends State<Home>{

  void jogar(String opcao){
    int n = Random().nextInt(3);
    Map<int,String> dict = {
      0:"pedra",
      1:"papel",
      2:"tesoura"
    };
    setState(() {
      this.pc = dict[n]!;
    });
  }
  double imgsize = 80;
  String pc = "default";

  // const _HomeState({super.key});
  Widget build(BuildContext context){
    return Scaffold(
      appBar: AppBar(
        title: Text(
          "Joken Po",
          style: TextStyle(
            fontWeight: FontWeight.bold,
            color: Colors.white
          ),
        ),
        backgroundColor: Colors.blue,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
              "Escolha do App",
              style: TextStyle(
                fontWeight: FontWeight.bold
              ),
            ),
            Image.asset(
              "images/" + pc + ".png",
              width: this.imgsize * 2
            ),
            Text(
              "Escolha uma opção...",
              style: TextStyle(
                fontWeight: FontWeight.bold
              ),
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                IconButton(
                  onPressed: () =>  this.jogar('pedra'), 
                  icon: Image.asset(
                    "images/pedra.png", 
                    width: this.imgsize,
                  ),
                ),
                IconButton(
                  onPressed: () => this.jogar('papel'), 
                  icon: Image.asset(
                    "images/papel.png",
                    width: this.imgsize,
                  )
                ),
                IconButton(
                  onPressed: () => this.jogar('tesoura'), 
                  icon: Image.asset(
                    "images/tesoura.png",
                    width: this.imgsize,
                  )
                ),
              ],
            )
          ],
        ),
      ),
    );
  }
}