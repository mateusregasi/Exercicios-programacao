// Dada a seguinte representação de uma árvore binária de busca (ABB):
// typedef struct ab{
//     int info;
//     struct ab *esq, *dir;
// } TABB;
// Escreva as seguintes funções:

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void *dado;
    struct node *prox;
} NO;
typedef struct ab{
    int info;
    struct ab *esq, *dir;
} TABB;

TABB *vet2ab(int *vet, int n);
TABB *cria(int info, TABB *esq, TABB *dir);
void imprime(TABB *a);
TABB *maior(TABB *a);

// (Q1) maior elemento da árvore: TABB* maior(TAB *a);

int main(void){

    int vet[] = {1, 4, 6 , 2, 3, 5, 7};
    TABB *a = vet2ab(vet, 7);

    imprime(maior(a));

    return 0;
}

void imprime(TABB *a){
	if(a){
		imprime(a->esq);
		printf("%d ", a->info);
		imprime(a->dir);
	}
}
TABB *criar(int info, TABB *esq, TABB *dir){
    TABB *n = (TABB *) malloc(sizeof(TABB));
    n->info = info;
    n->esq = esq;
    n->dir = dir;
    return n;
}
TABB *ins(TABB *a, int n){
    if(!a) return criar(n, NULL, NULL);
    if(a->info > n) a->esq = ins(a->esq, n);
    else if(a->info < n) a->dir = ins(a->dir, n); 
    return a;
}
TABB *vet2ab(int *vet, int n){
    TABB *a = NULL;
    for(int i = 0; i < n; i++) a = ins(a, vet[i]);
    return a;
}
TABB *maior(TABB *a){
    if((!a) || (!a->dir)) return a;
    return maior(a->dir);
}
