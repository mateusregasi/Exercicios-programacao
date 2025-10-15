// Write a program to compute unsmoothed unigrams and bigrams.

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <list>

using namespace std;

void pre_processar(string nome);
void bpe_algoritmo(string origem, string destino, int limite);
void bpe_import(string origem);
list<string> tokenizador(string linha);
// criar_matriz_coocorrência_palavra_palavra

int main(){
    // pre_processar("fonte_pre_formatada");
    // bpe_algoritmo("fonte_pre_formatada", "vocabulario", 10000);
    return 0;
}

list<string> tokenizador(string linha){
    regex pattern ("\\b([\\wáàâãéèêíïóôõöúçñ]*)\\b");
    sregex_iterator iterador (linha.begin(), linha.end(), pattern), end;
    list<string> resultado;
    for(; iterador != end; iterador++, iterador ++){
        resultado.push_back(iterador->str());
        cout << iterador->str() << "\n";
    }
    return resultado;
}

// void tokenizador(string origem, string nome_arquivo_destino){
//     string nome_arquivo_origem = origem + ".txt", linha2;
//     char linha[1000];
//     cout << nome_arquivo_destino;

//     ifstream fr;
//     fr.open(nome_arquivo_origem);   
    
//     set<string> tokens;
//     smatch registros;
//     regex pattern ("\\b[a-zA-Záàâãéèêíïóôõöúçñ]*\\b");
//     while(fr.getline(linha, 1000)){
//         linha2 = linha;
//         regex_search(linha2, registros, pattern);
//         for(auto reg : registros){
//             cout << reg.str() + "\n";
//         }
//     }

//     fr.close();
// }

// void bpe_algoritmo(string origem, string nome_arquivo_destino, int limite){
//     string nome_arquivo_origem = origem + ".txt";
            
// }


void pre_processar(string nome){
    string  nome_arquivo = "../" + nome + ".txt", linha2;
    char linha[1000];


    smatch registro;
    // regex pattern ("(?:(.*)(?:(?:<Media omitted>)|(?:http.*)))|(?:(\\d\\d?\\/\\d\\d?\\/\\d\\d)(?:, )(\\d\\d:\\d\\d)(?: - )(.*)(?:: )(.*))");
    regex pattern ("^(\\d\\d?\\/\\d\\d?\\/\\d\\d)(?:, )(\\d\\d:\\d\\d)(?: - )(Mateus Regasi)(?:: )(.*)(?:<This message was edited>)?$");
    regex pattern_filter ("(<Media omitted>)|(http.*)");

    ifstream fr;
    ofstream fw;
    fr.open(nome_arquivo.c_str());
    fw.open("../saida.txt", ios::out);

    while(fr.getline(linha, 1000)){

        linha2 = linha;
        regex_search(linha2, registro, pattern);
        if(registro.size() >= 5 && !regex_match(registro[4].str(), pattern_filter)){
            // cout << registro[4] << "\n";
            fw << registro[4] << "\n";
        }

    }
    fr.close();
    fw.close();
}
