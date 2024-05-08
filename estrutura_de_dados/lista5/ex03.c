#include <stdio.h>
#include <stdlib.h>

// (Q3) Escreva um procedimento que receba o nome de um arquivo texto, cujo conteúdo são valores
// inteiros e imprima na tela o número de vezes que cada elemento aparece e em quais linhas – 
// void resumo(char *Arq).

typedef struct node{
    int dado;
    struct node *prox;
} NO;

NO *add(int v, NO *n){
    NO *novo = (NO *) malloc(sizeof(NO));
    novo->dado = v;
    novo->prox = NULL;
    if(!n) return novo;
    NO *a;
    for(a=n; a->prox; a=a->prox);
    a->prox = novo;
    return n;
}
NO *arq2lista(char *nome){
    NO *lista = NULL;
    FILE *f = fopen(nome, "r");
    int c;
    while(!feof(f)){
        fscanf(f, "%d\n", &c);
        lista = add(c, lista);
    }
    fclose(f);
    return lista;
}
int conta_lista(int dado, NO *lista){
    int c = 0;
    while(lista){
        if(lista->dado == dado) c++;
        lista = lista->prox;
    }
    return c;
}
NO *lista2conjunto(NO *lista){
    NO *conjunto = NULL;
    for(NO *a=lista; a; a=a->prox)
        if(!conta_lista(a->dado, conjunto))
            conjunto = add(a->dado, conjunto);
    return conjunto;
}
void destroi_lista(NO *lista){
    while(lista){
        NO *r = lista;
        lista = r->prox;
        free(r);
    }
}
void imp_lista(NO *lista){
    for(NO *i=lista; i; i=i->prox) printf("%d ", i->dado);
    printf("\n");
}


void resumo(char *nome){

    // Passa o arquivo para lista
    NO *l = arq2lista(nome);

    // Cria um conjunto usando lista
    NO *c = lista2conjunto(l);

    // Varre o conjunto e faz a impressao
    for(NO *a=c; a; a = a->prox)
        printf("%d aparece %d vezes\n", a->dado, conta_lista(a->dado, l));

    // Destroi a lista e o conjunto
    destroi_lista(l);
    destroi_lista(c);
}

int main(void){
    resumo("arqex03");
    return 0;
}