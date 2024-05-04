// (a) Implemente o tipo abstrato de dados lista simplesmente encadeada genérica, usando void *.
// (b) Dada a seguinte representação de uma árvore binária:
// typedef struct ab{
//     int info;
//     struct ab *esq, *dir;
// } TAB;
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void *dado;
    struct node *prox;
} NO;
typedef struct ab{
    int info;
    struct ab *esq, *dir;
} TAB;

TAB *vet2ab(int *vet, int n);
TAB *cria(int info, TAB *esq, TAB *dir);
TAB* copia(TAB *a);
TAB imprime(TAB *a);

// (Q2) espelho de uma árvore (o que está a esquerda na árvore original, estará a direita no espelho, e
// vice-versa): TAB* espelho (TAB *a);

int main(void){

    int vet[] = {1, 2, 3, 4, 5, 6};
    TAB *a = vet2ab(vet, 6), *ab = copia(a);

    imprime(ab);

    return 0;
}

TAB imprime(TAB *a){
	if(a){
		printf("%d", a->info);
		imprime(a->esq);
		imprime(a->dir);
	}
}
TAB *criar(int info, TAB *esq, TAB *dir){
    TAB *n = (TAB *) malloc(sizeof(TAB));
    n->info = info;
    n->esq = esq;
    n->dir = dir;
    return n;
}
TAB *vet2ab(int *vet, int n){
    if(n <= 0) return NULL;
    return criar(vet[n/2], vet2ab(vet, n/2), vet2ab(&vet[n/2+1], n-n/2-1));
}
TAB *copia(TAB *a){
    if(!a) return NULL;
    return criar(a->info, copia(a->dir), copia(a->esq));
}

// 1 2 3 4 5 6

//     4
//  2     6
// 1 3   5

//     4
//  6     2
//   5   3 1