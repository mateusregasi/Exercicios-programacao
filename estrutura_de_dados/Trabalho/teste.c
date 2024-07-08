#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TABMJ.c"

void func(void *v){
    TJ *j = (TJ *) v;
    printf("%s - %d\n", j->nome, j->idade);
}

int main(void){

    int t = 2, n;
    char *nome = "EURO.txt";
    
    // char *raiz = arq2arvbmarq(nome, "arv", t, &n);
    char *raiz = "187.dat";
    printf("Raiz: %s\n", raiz);

    // TLSE *l = jogadores_mais_novos_e_mais_velhos(raiz, t);
    char *s = selecao_com_mais_jogadores_fora_do_pais(raiz, t);
    printf("%s\n", s);
    // printf("Número de nós: %d\n", TLSE_conta(l));
    printf("\n");

    // TLSE_imp(l, func);
    // imprime(raiz, t);

    return 0;
}
