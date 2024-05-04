#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 10

// Funções auxiliares
void imp_arqb(char *nome);
void ver_arqb(char *nome);
int len_arqb(FILE *f);
int len_arqb_na(char *nome);
void vet2arqb(void *v, int n, char *nome);
char **arqb2vet(char *nome);
void imp_vet(char **vet, int n);

// (Q1) Escreva um programa em C que leia dois arquivos binários “a.bin” e “b.bin” contendo palavras distintas descritas por 10 caracteres e produza um terceiro arquivo c.bin. No arquivo “c.bin”, cada um de seus registros contém um par ordenado de palavras, onde a primeira palavra é proveniente de “a.bin” e a segunda de “b.bin”. Como resultado do processamento, o arquivo “c.bin” deve conter todos os pares ordenados formados por palavras dos dois arquivos de entrada (o resultado é o produto cartesiano dos dois conjuntos). Obs.: todo processamento deve ser feito em memória secundária.

// Função do exercício
void prod_cart_arqb(char *arq1, char *arq2, char *arq3);

int main(void){

    // Criando os dois arquivos
    char palavras1[10][11] = {"Copo", "Celular", "Caderno", "Rua", "Chinelo", "Caneta", "Chave", "Post-it", "Mouse", "Teclado"},
         palavras2[10][11] = {"Opaco", "Gelado", "Sujo", "Verde", "Molhado", "Ríspido", "Salgado", "Brilhante", "Bonito", "Frágil"};
    vet2arqb(palavras1, 10, "a.bin");
    vet2arqb(palavras2, 10, "b.bin");

    // Printa os dois arquivos
    printf("a.bin\n");
    imp_arqb("a.bin");
    printf("\n\nb.bin\n");
    imp_arqb("b.bin");
    printf("\n\na.bin + b.bin = c.bin\n\n");
    
    // Produto cartesiano
    prod_cart_arqb("a.bin", "b.bin", "c.bin");

    // Printa o terceiro arquivo
    imp_arqb("c.bin");
    printf("\n");

    return 0;
}

// Funções auxiliares
void ver_arqb(char *nome){
    FILE *arq = fopen(nome, "ab");
    fclose(arq);
}
int len_arqb(FILE *f){
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / (sizeof(char) * (MAX_CHAR +1));
    fseek(f, 0, SEEK_SET);
    return n;
}
int len_arqb_na(char *nome){
    FILE *f = fopen(nome, "rb");
    if(!f) return 0;
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / (sizeof(char) * (MAX_CHAR +1));
    fclose(f);
    return n;
}
void vet2arqb(void *v, int n, char *nome){
    char (*vet)[MAX_CHAR+1] = (char (*)[MAX_CHAR+1]) v;
    ver_arqb(nome);
    FILE *f = fopen(nome, "wb");

    for(int i=0; i<n; i++)
        fwrite(vet[i], sizeof(char) * (MAX_CHAR+1), 1, f);

    fclose(f);
}
char **arqb2vet(char *nome){
    FILE *f = fopen(nome, "rb");
    int n = len_arqb(f);

    // Lê palavra por palavra e coloca dentro do vetor
    char **vet = (char **) malloc(sizeof(char *) * n);
    for(int i=0; i<n; i++){
        char *palavra = (char *) malloc(sizeof(char) * (MAX_CHAR+1));
        fread(palavra, sizeof(char), 1, f);
        vet[i] = palavra;
    }

    fclose(f);
    return vet;
}
void imp_arqb(char *nome){
    FILE *f = fopen(nome, "rb");
    if(!f) return;

    // Lê palavra por palavra e printa
    int n = len_arqb(f);
    char *palavra = (char *) malloc(sizeof(char) * (MAX_CHAR+1));
    for(int i=0; i<n; i++){
        fread(palavra, sizeof(char) * (MAX_CHAR+1), 1, f);
        printf("%s\n", palavra);
    }

    fclose(f);
}
void imp_vet(char **vet, int n){
    for(int i=0; i<n; i++)
        printf("%s\n", vet[i]);
}

// Função do exercício
void prod_cart_arqb(char *arq1, char *arq2, char *arq3){
    
    // Cria o arquivo
    FILE *f = fopen(arq3, "wb");

    // Faz uma cópia do arquivo 1 e arquivo 2
    char **vet1 = arqb2vet("a.bin"),
         **vet2 = arqb2vet("b.bin");

    // Conta a quantidade de elementos em cada arquivo
    int n1 = len_arqb_na("a.bin"),
        n2 = len_arqb_na("b.bin");

    imp_vet(vet1, n1);
    imp_vet(vet2, n2);

    // Conta a quantidade máxima de caracteres em cada registro
    int max_reg = MAX_CHAR * 2 + 2; 

    // Faz uma iteração para fazer o produto cartesiano
    char *registro = (char *) malloc(sizeof(char) * max_reg);
    for(int i=0; i<n1; i++){
        for(int j=0; j<n2; j++){
            sprintf(registro, "%s %s", vet1[i], vet2[j]);
            fwrite(registro, sizeof(char), max_reg, f);
        }
    }

    // Fecha o arquivo
    fclose(f);
}




// (Q2) Escreva um programa em C que receba como entrada um arquivo binário de clientes “clientes.bin” e, sem ler todos os registros para memória, permita a consulta dos dados de um cliente em função do seu CPF. Considere que o formato de cada registro é dado pelos seguintes campos: nome – char (40), CPF – char(11), conta_corrente (int), agencia (int), saldo (float).

// (Q3) Escreva um programa em C que receba o arquivo de clientes do exercício Q2 e produza um arquivo binário de índices “indices.bin”, onde a sequência dos índices descreve os registros do arquivo de clientes ordenados pelo saldo.