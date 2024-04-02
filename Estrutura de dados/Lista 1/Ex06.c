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
typedef struct fila{
    NO *ini, *fim;
} FI;

TAB *vet2ab(int *vet, int n);
TAB *cria(int info, TAB *esq, TAB *dir);
TAB imprime(TAB *a);
TAB *retira_pares(TAB *arv);
TAB *retira(TAB *a, int *folha);

// (Q6) uma função em C que, dada uma árvore binária qualquer, retire todos os elementos pares da
// árvore original. A função deve ter o seguinte protótipo: 

int main(void){

    int vet[] = {1, 4, 6 , 2, 3, 5, 7};
    TAB *a = vet2ab(vet, 7);

    imprime(retira_pares(a));

    return 0;
}

TAB imprime(TAB *a){
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

TAB *retira(TAB *a, int *folha){
	if(!a) return a;
	if((!a->esq) && (!a->dir)){
		(*folha) = a->info;
		free(a);
		return NULL;
	}
	if(a->esq) a->esq = retira(a->esq, folha);
	else a->dir = retira(a->dir, folha);
	return a;
}
TAB *retira_pares(TAB *arv){
	if(!arv) return arv;

	if((!arv->esq) && (!arv->dir)){
		if(arv->info % 2) return arv;
		free(arv);
		return NULL;

	} if((arv->info % 2 ) == 0){
		int x;
		arv = retira(arv, &x);
		arv->info = x;
		arv = retira_pares(arv);

	} else{
		arv->esq = retira_pares(arv->esq);
		arv->dir = retira_pares(arv->dir);
	}
	return arv;
}

