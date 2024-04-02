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
TAB imprime(TAB *a);
TAB *maior(TAB *a);

// (Q3) maior elemento da árvore: TAB* maior(TAB *a);

int main(void){

    int vet[] = {1, 4, 6 , 2, 3, 5, 7};
    TAB *a = vet2ab(vet, 7);

    imprime(maior(a));

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
TAB *maior(TAB *a){
    if((!a) || (!a->esq) && (!a->dir)) return a;
    TAB *m1 = NULL, *m2 = NULL;
    if(a->esq) m1 = maior(a->esq);
    if(a->dir) m2 = maior(a->dir);
    if(!m1) return (a->info > m2->info) ? a : m2;
    if(!m2) return (a->info > m1->info) ? a : m1;
    m1 = (m1->info > m2->info) ? m1 : m2;
    return (a->info > m1->info) ? a : m1; 
}