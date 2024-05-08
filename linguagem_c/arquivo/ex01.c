#include <stdio.h>

// Faça um programa que recebe o nome de um arquivo e conta o total de letras, vogais,
// consoantes, espaços em branco, palavras e o total de linhas encontradas no arquivo.
// Considere que uma palavra é separada de outra por um espaço em branco ou um fim de linha.

int verificar_letra(char c){
    if(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) return 1;
    return 0;
}
int verificar_vogal(char c){
    char vet[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    for(int i=0; i<10; i++)
        if(c == vet[i]) return 1;
    return 0;
}
int verificar_consoante(char c){
    if((verificar_letra(c)) && (!verificar_vogal(c))) return 1;
    return 0;
}

int main(void){

    // Ponteiro para file
    FILE *f = fopen("arquivo", "r");
    char caracter, anterior;
    int contador_letras = 0, contador_vogais = 0, contador_consoantes = 0, contador_espaco_branco = 0, contador_palavras = 0, contador_linhas = 0;
    int i = 0;

    // Lê um caractere
    do{
        caracter = getc(f);

        if(caracter == ' ') contador_espaco_branco++;
        if((caracter == '\n')) contador_linhas++;
        if(verificar_letra(caracter)){

            contador_letras++;
            if(verificar_vogal(caracter)) contador_vogais++;
            if(verificar_consoante(caracter)) contador_consoantes++;
        }

        if(i != 0){
            if((anterior == ' ') && (caracter != ' ')) contador_palavras++;
            if((i == 1) && (anterior != ' ')) contador_palavras++;
        }
        anterior = caracter;

        i++;
    } while(caracter != EOF);
    contador_linhas++;
    
    printf("%d %d %d %d %d %d\n", contador_letras, contador_vogais, contador_consoantes, contador_espaco_branco, contador_palavras, contador_linhas);

    fclose(f);

    return 0;
}
