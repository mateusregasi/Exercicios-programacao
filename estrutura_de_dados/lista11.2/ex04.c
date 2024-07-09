#include <stdio.h>
#include <stdlib.h>
#include "hashms.c"

void cria_arquivo(char *nome){
    FILE *f = fopen(nome, "wb+");
    fclose(f);
}

// Dado dois arquivos texto que representam conjuntos inteiros (isto é, não há elementos repetidos nos arquivos), um elemento por linha, e fazendo SOMENTE uma leitura em cada arquivos, faça cada uma das questões utilizando tabela hash em memória secundária:

// (a) intersecção dos conjuntos:
void inter(char *arq1, char *arq2, char *saida);

// (b) diferença simétrica de conjunto:
void dif_sim(char *arq1, char *arq2, char *saida);

// (c) união dos conjuntos:
void uniao(char *arq1, char *arq2, char *saida);

int main(void){
    int n = 3;
    char *h1 = "ex04.1.hash", *f1 = "ex04.1.dados",
        *h2 = "ex04.2.hash", *f2 = "ex04.2.dados";
    inicializa(h1, f1, n);
    inicializa(h2, f2, n);

    insere(h1, f1, n, 1);
    insere(h1, f1, n, 2);
    insere(h1, f1, n, 3);
    insere(h1, f1, n, 4);
    insere(h1, f1, n, 5);
    insere(h1, f1, n, 6);

    insere(h2, f2, n, 7);
    insere(h2, f2, n, 8);
    insere(h2, f2, n, 9);
    insere(h2, f2, n, 10);
    insere(h2, f2, n, 11);
    insere(h2, f2, n, 12);

    imprime(h1, f1, n);
    imprime(h2, f2, n);

    return 0;
}

void inter(char *arq1, char *arq2, char *saida){}
void dif_sim(char *arq1, char *arq2, char *saida){}
void uniao(char *arq1, char *arq2, char *saida){}