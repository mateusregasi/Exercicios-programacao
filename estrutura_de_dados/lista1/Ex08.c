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
void imprime(TAB *a);
int ni(TAB *a);

// (Q8) descubra a quantidade de nós internos: int ni(TAB *a);

int main(void){

    int vet[] = {1, 2, 3, 4, 5, 6};
    TAB *a = vet2ab(vet, 6);

    imprime(a);
    printf("\nNumero de elementos: %d\n", ni(a));

    return 0;
}

void imprime(TAB *a){
	if(a){
		printf("%d ", a->info);
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
int ni(TAB *a){
    if(!a) return 0;
    return 1 + ni(a->esq) + ni(a->dir);
}