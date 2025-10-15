import 'package:flutter/material.dart';
import 'utilidades/apidicionario.dart';
import 'utilidades/dificuldades.dart';
import 'dart:io';
import 'dart:convert';
import 'utilidades/configuracoes.dart';
import 'utilidades/gerenciador.dart';
import 'componentes/linha.dart';


class PaginaJogo extends StatefulWidget{
  const PaginaJogo({super.key});

  @override
  State<PaginaJogo> createState() => _PaginaJogoState();
}

class _PaginaJogoState extends State<PaginaJogo>{
  _PaginaJogoState({Key? key});
  Color corDeFundo = Configuracoes.corPrincipal2;

  List<Widget> extra = [];

  late Gerenciador gerenciador;
  String palavra = "";
  dif dificuldade = dif.facil;
  int numLetras = 5;
  final double margem = 20;
  List<Linha> linhas = [];
  List<GlobalKey<LinhaState>> keyLinhas = [];

  @override
  void initState() {
    super.initState();
    _inicializar();
  }

  Future<void> _inicializar() async {
    await carregar();
    await gerarPalavra();
    keyLinhas.add(GlobalKey<LinhaState>());
    linhas.add(
      Linha(
        n: palavra.length, 
        key: keyLinhas[0],
        larguraJanela: MediaQuery.of(context).size.width
      ));
    gerenciador = Gerenciador(palavra, dificuldade);
    setState(() {});
  }

  Future<void> carregar() async {
    File f = File('config');
    String conteudo = await f.readAsString();
    Map<String, dynamic> res = jsonDecode(conteudo);
    numLetras = res['numLetras'].toInt();
    dificuldade = dif.values.elementAt(res['dificuldade']);
  }

  Future<void> gerarPalavra() async {
    palavra = await DicionarioAPI.gerarPalavra(numLetras);
    print(palavra);
  }

  void chutarPalavra(){ 
    LinhaState estado = keyLinhas[gerenciador.i].currentState!;
    String palavra_chutada = estado.pegarPalavra();

    if(palavra_chutada.length == numLetras){
      gerenciador.chutar(palavra_chutada);
      estado.aplicarMascara(gerenciador.mascara);

      if(gerenciador.acertou()){
        extra.add(Text(
          "Parabéns, você ganhou!!",
          style: TextStyle(
            color: Colors.white,
            fontWeight: FontWeight.bold,
            fontSize: 20
          ),
        ));
      } else if(gerenciador.perdeu()){
        extra.add(Text(
          "Infelizmente você perdeu...",
          style: TextStyle(
            color: Colors.white,
            fontWeight: FontWeight.bold,
            fontSize: 20
          ),
        ));
      } else{
        keyLinhas.add(GlobalKey<LinhaState>());      
        linhas.add(
          Linha(
            n: numLetras, 
            key:  keyLinhas[gerenciador.i],
            larguraJanela: MediaQuery.of(context).size.width
          )
        );
      }
      setState(() {});
    }
    
    
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        backgroundColor: Configuracoes.corPrincipal2,
        appBar: AppBar(
          title: Center(
            child: Text(
              "Palavra do Dia",
              style: TextStyle(
                color: Colors.white,
                fontWeight: FontWeight.bold,
                fontSize: 30,
              ),
            ),
          ),
          backgroundColor: corDeFundo,
          leading: IconButton(
            icon: Icon(
              Icons.arrow_back_ios_rounded,
              color: Colors.white,
            ),
            onPressed: () => { Navigator.pop(context) },
          ),
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Padding(padding: EdgeInsets.all(margem)),
              SingleChildScrollView(
                child: Container(
                  height: MediaQuery.of(context).size.height * 0.6,
                  child: Column(
                    children: linhas,
                  ),
                )
              ),
              Padding(padding: EdgeInsets.all(margem)),
            ] + extra + [
              Padding(padding: EdgeInsets.all(margem)),
              SizedBox(
                width: MediaQuery.of(context).size.width * 0.8,
                height: MediaQuery.of(context).size.height * 0.05,
                child:  ElevatedButton(
                  onPressed: chutarPalavra, 
                  child: Text("Chutar"),
                  style: ButtonStyle(),
                ),
              )
                  
            ],
          )
        ),
      ),
      debugShowCheckedModeBanner: false,
    );
  }
}