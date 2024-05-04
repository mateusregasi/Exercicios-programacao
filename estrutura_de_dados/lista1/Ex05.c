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
int igual(TAB *a1, TAB *a2);

// (Q5) uma função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A função
// retorna um se elas são iguais e zero, caso contrário. A função deve obedecer ao seguinte protótipo:
// int igual (TAB* a1, TAB* a2);

int main(void){

    int vet[] = {1, 2, 3, 4, 5, 6};
    int vet2[] = {6, 5, 4, 3, 2, 1};

    TAB *a = vet2ab(vet, 6);
    TAB *a2 = vet2ab(vet2, 6);

    if(igual(a, a)) printf("Igual");
    if(igual(a, a2)) printf("Não igual");

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
int igual(TAB *a1, TAB *a2){
    if((!a1) && (!a2)) return 1;
    if(((!a1) && (a2)) || ((a1) && (!a2))) return 0;
    if(a1->info != a2->info) return 0;
    if(!igual(a1->esq, a2->esq)) return 0;
    return igual(a1->dir, a2->dir);
}