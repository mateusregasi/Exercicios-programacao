import "package:flutter/material.dart";
import "package:flutter/rendering.dart";
import "utilidades/configuracoes.dart";
import 'dart:io';
import "dart:convert";
import 'utilidades/dificuldades.dart';


class Botao extends StatelessWidget{
  final String dificuldade;
  final double n = 30;
  const Botao(this.dificuldade, {super.key});

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: EdgeInsets.only(left: n, right: n),
      child: Text(
        dificuldade,
        style: TextStyle(
          fontSize: 20
        )
      ),
    );
  }
}

class PaginaConfiguracao extends StatefulWidget{
  const PaginaConfiguracao({super.key});

  @override
  State<PaginaConfiguracao> createState() => _PaginaConfiguracaoState();
}

class _PaginaConfiguracaoState extends State<PaginaConfiguracao>{
  _PaginaConfiguracaoState({Key? key});

  double numLetras = 5;
  TextEditingController apelido = TextEditingController();
  dif dificuldade = dif.facil;
  String textoSlider = "";

  void mudarEstadoApelido(String str){
    apelido.text = str;
  }
  List<bool> listaBotoes = [true, false, false];
  List<dif> listaDificuladeBotoes = [dif.facil, dif.medio, dif.dificil];
  int indixeAtual = 0;
  void mudarEstadoBotao(int index){
    listaBotoes[indixeAtual] = false;
    listaBotoes[index] = true;
    dificuldade = listaDificuladeBotoes[index];
    indixeAtual = index;
    setState(() {
    });
  }
  void mudarEstadoSlider(double estado){
    numLetras = estado;
    textoSlider = '${numLetras.toInt()}';    
    setState(() {
    });
  }

  void salvar(String apelido, dif dificuldade, double numLetras){
    final registro = {
      'apelido':  apelido,
      'dificuldade': dificuldade.index,
      'numLetras': numLetras
    };
    final str = jsonEncode(registro);
    print(str);
    File('config').writeAsString(str);
  }
  void carregar(){
    File f = File('config');
    if(f.existsSync()){
      Map<String, dynamic> res = jsonDecode(f.readAsStringSync());

      numLetras = res["numLetras"];
      textoSlider = '${numLetras.toInt()}';    

      apelido.text = res["apelido"];
      
      dificuldade = dif.values.elementAt(res["dificuldade"]);
      for(int i=0; i < listaBotoes.length; i++) 
        listaBotoes[i] = false;
      listaBotoes[res["dificuldade"]] = true;
    } else{
      salvar("", dif.facil, 5);
    }
  }

  @override
  void initState() {
    carregar();
    super.initState();
  }

  @override
  Widget build(BuildContext context){
    return Center(
      child: Padding(
        padding: EdgeInsets.all(30),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Padding(
              padding: EdgeInsets.all(10) 
            ),
            Center(
              child: Image.asset(
                "img/user.png",
                width: MediaQuery.of(context).size.width * 0.4 < 300 ? MediaQuery.of(context).size.width * 0.4 : 300,
                opacity: const AlwaysStoppedAnimation(.5),
              ),
            ),
            TextField(
              keyboardType: TextInputType.name,
              decoration: InputDecoration(
                label: Text("Apelido")
              ),
              onChanged: mudarEstadoApelido,
              controller: apelido,
            ),
            Column(
              mainAxisSize: MainAxisSize.max,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  "Dificuldade",
                  textAlign: TextAlign.left,
                  style: TextStyle(
                    fontSize: 20
                  ),
                ),
                ToggleButtons(
                  isSelected: listaBotoes,
                  borderRadius: BorderRadius.all(Radius.circular(10)),
                  children: [
                    Botao("Fácil"),
                    Botao("Médio"),
                    Botao("Difícil"),
                  ],
                  onPressed: mudarEstadoBotao,
                ),
                
              ],
            ),
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  "Numero de letras",
                  textAlign: TextAlign.start,
                  style: TextStyle(
                    fontSize: 20
                  )
                ),
                Slider(
                  value: numLetras,
                  min: 5,
                  max: 10,
                  divisions: 5,
                  onChanged: mudarEstadoSlider,
                  label: textoSlider,
                )
              ],
            ),
            Container(
              child: TextButton(
                onPressed: () => salvar(apelido.text, dificuldade, numLetras), 
                child: Text(
                  "Salvar",
                  style: TextStyle(
                    fontSize: 20,
                    color: Colors.white,
                  ),
                ),
                style: ButtonStyle(
                  backgroundColor: WidgetStatePropertyAll(
                    Configuracoes.corPrincipal
                  )
                ),
              ),
              width: MediaQuery.of(context).size.width * 0.8,
              height: 50,
            ),
            Padding(
              padding: EdgeInsets.all(20) 
            )
          ],
        )
      ),
    );
  }
} 