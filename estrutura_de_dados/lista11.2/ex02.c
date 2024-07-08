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
NOL *retfim(NOL *l){
    if(!l) return NULL;
    if(!l->prox){
        free(l);
        return NULL;
    }
    NOL *a = l;
    while(a->prox->prox)
        a = a->prox;
    free(a->prox);
    a->prox = NULL;
    return l;
}

// Retornar todas as informações ancestrais de um nó na árvore B, da raiz da árvore até o elemento passado como parâmetro, usando a biblioteca de lista encadeada:

NOL *misc(NO *a, int v);

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

    NOL *lista = misc(a, 4);
    imp(lista);

}

NOL *misc(NO *a, int v){
    if(!a) return NULL;
    int i = 0, j = -1;
    NOL *lista = NULL; 
    while(i < a->n){
        lista = insfim(lista, a->chaves[i]);
        if(a->chaves[i] == v){
            while(i != 0){
                lista = retfim(lista);
                i--;
            }
            break;
        }
        if((j == -1) && (v < a->chaves[i])){
            j = i;
        }
        i++;
    }
    if(j != -1){
        NOL *aux = lista;
        if(aux){
            while(aux->prox) aux = aux->prox;
            aux->prox = misc(a->filhos[j], v);
        } else lista = misc(a->filhos[j], v);
    }
    return lista;
}