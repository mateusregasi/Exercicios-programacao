#include <stdio.h>
#include <stdlib.h>
#include "TARVB.c"

typedef struct node{
    int dado;
    struct node *prox;
} NOL;

NOL *criar(int e){
    NOL *n = (NOL *) malloc(sizeof(NOL));
    n->prox = NULL;
    n->dado = e;
    return n;
}
NOL *insfim(NOL *n, int e){
    NOL *novo = criar(e), *a = n;
    if(!n) return novo;
    while(a->prox)
        a = a->prox;
    a->prox = novo;
    return n;
}
void imp(NOL *a){
    while(a){
        printf("%d ", a->dado);
        a = a->prox;
    }
}

// Uma função em C que, dada uma árvore B qualquer, retorne, numa lista, todos os elementos maiores que N. A função deve ter o seguinte protótipo:

NOL *mn(NO *a, int n);

int main(void){

    int t = 2;
    NO *a = NULL;
    a = insere(a, 1, t);
    a = insere(a, 1111, t);
    a = insere(a, 311, t);
    a = insere(a, 2, t);
    a = insere(a, 21, t);
    a = insere(a, 21, t);
    a = insere(a, 12, t);
    a = insere(a, 31, t);
    a = insere(a, 1, t);
    a = insere(a, 13, t);
    a = insere(a, 13, t);
    a = insere(a, 1221, t);
    a = insere(a, 12, t);
    a = insere(a, 11, t);
    a = insere(a, 4, t);
    a = insere(a, 11111, t);
    imprime(a);

    NOL *lista = mn(a, 10);
    imp(lista);

}

NOL *mn(NO *a, int v){
    if(!a) return NULL;
    int i = 0;
    while((i < a->n) && (a->chaves[i] < v)) i++;
    NOL *lista = NULL;
    if(a->folha){
        while(i < a->n){
            lista = insfim(lista, a->chaves[i]);
            i++;
        }
        return lista;
    }
    while((i <= a->n) && (!lista)){
        lista = mn(a->filhos[i], v);
        i++;
    }
    NOL *aux = lista;
    while(i <= a->n){
        while(aux->prox) aux = aux->prox;
        aux->prox = mn(a->filhos[i], v);
        i++;
    }
    return lista;
}