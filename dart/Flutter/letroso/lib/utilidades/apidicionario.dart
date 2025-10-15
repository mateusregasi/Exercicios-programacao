// import 'dart:convert';
import 'dart:math';
// import 'package:http/http.dart' as http;

class DicionarioAPI{
  static Uri uri = Uri.http("api.dicionario-aberto.net", "random");
  static Map<int, List<String>> palavras = {
    5: ["sonho", "brisa", "fruta", "navio", "verde"], 
    6: ["escola", "camisa", "pessoa", "viagem"],
    7: ["planeta", "desenho", "amizade", "destino", "brincar"],
    8: ["caminhão", "natureza"],
    9: ["esperança", "chocolate"],
    10: ["computador", "identidade", "importante", "brasileiro"]
  };   

  // static gerarPalavra(int n) async{
  //   String palavra = "";
  //   await http.get(uri).then((value){
  //     palavra = jsonDecode(value.body)['word'];
  //   });
  //   return palavra;
  // }

  static gerarPalavra(int n){
    int i = Random().nextInt(palavras[n]!.length);
    return palavras[n]!.elementAt(i);
  }
}