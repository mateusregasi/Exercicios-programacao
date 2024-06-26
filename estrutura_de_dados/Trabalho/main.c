#include <stdio.h>
#include "TABMJ.c" 

int main(void){

    // Lendo o arquivo
    int n = 0, t = 5, i = 0;

    // char *nome = "EURO.txt";
    // NO *lista = arq2listajogador(nome, &n);
    // imp(lista, impjogador);
    
    char *nome = cria_arquivo(t, n);
    arq2arvbmarq(nome, t, &n);

    // Transforma em arquivo

    return 0;
}