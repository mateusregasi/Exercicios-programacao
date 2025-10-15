import 'dificuldades.dart';
import 'status.dart';

class Gerenciador{
  int i = 0;
  int n = 0;
  List<String> palavras = [];
  Set<String> letras = Set();
  List<Status> mascara = [];
  List<List<Status>> mascaras = [];

  late String palavra;
  late dif dificuldade;
  late int maximo = 0;

  Gerenciador(this.palavra, this.dificuldade){
    for(int i=0; i<palavra.length; i++){
      mascara.insert(0, Status.errou);
      letras.add(palavra[i]);
    }
    switch(dificuldade){
      case dif.facil:
        maximo = 10;
        break;
      case dif.medio:
        maximo = 7;
        break;
      case dif.dificil:
        maximo = 4;
        break;  
    }
  }

  bool chutar(String palavra){
    bool f = true;
    for(int i=0; i<palavra.length; i++){
      if(this.palavra[i] == palavra[i]){
        mascara[i] = Status.posicao;
      } else if(letras.contains(palavra[i])){
        mascara[i] = Status.letra;
        f = false;
      } else{
        mascara[i] = Status.errou;
        f = false;
      }
    }
    palavras.add(palavra.toString());
    mascaras.add(mascara.toList());
    i += 1;
    return f;
  }

  List<Status> getMascara() => mascara.toList();
  List<List<Status>> getMascaras() => mascaras.toList();
  bool acertou() => palavras[i-1] == palavra;
  bool perdeu() => (i >= maximo);  
}