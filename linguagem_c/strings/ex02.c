#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Alguns números possuem uma propriedade interessante: se você recuperar seus dois
// primeiros dígitos e seus dois últimos dígitos e elevar ao quadrado a soma deles, você obter a
// a concatenação desses 4 dígitos. Por exemplo, o número 203125 possui essa propriedade, pois
// (20 + 25) = 2025. Por outro lado, o mesmo não é observado para 20326, pois (20 + 26) = 2116 6=
// 2026. Escreva um programa que informa se um número possui essa propriedade.

// Pega os dois caracteres da esquerda
int get_primeiros(int n){
    int i = 1;
    while((n / i) >= 100) i *= 10;
    return n / i;
}
// Pega os dois caracteres da direita
int get_ultimos(int n){
    return n %= 100;
}
// Transforma os dois caracteres em string
char *transforma_em_string(int n){
    char *string = (char *) malloc(sizeof(char) * 3);
    if(n >= 10) sprintf(string, "%d", n);
    else sprintf(string, "0%d", n);
    string[2] = '\0';
    return string;
}
// Transforma uma string em inteiro
int str2int(char *str){
    int num;
    sscanf(str, "%d", &num);
    return num;
}
int propriedade(int n){

    // Pega os números nos extremos
    int ultimos = get_ultimos(n), primeiros = get_primeiros(n);

    // Converte eles para caractere
    char *ultimos_string = transforma_em_string(ultimos), *primeiros_string = transforma_em_string(primeiros);

    // Cria o número resultante
    char num_final_string[5];
    strcat(num_final_string, primeiros_string);
    strcat(num_final_string, ultimos_string);

    // Converte ele para inteiro
    int num_final = str2int(num_final_string);

    // Retorna a comparação
    return (num_final == ((ultimos + primeiros) * (ultimos + primeiros))) ? 1 : 0;
}

int main(void){

    // Entrada de dados
    int numero;
    printf("Informe um número maior que 1000: ");
    scanf("%d", &numero);

    if(numero < 1000) exit(1);

    printf("O número %d %spossui essa propriedade\n", numero, (propriedade(numero)) ? "" : "não ");

}