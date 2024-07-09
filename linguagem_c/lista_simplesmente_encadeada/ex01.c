#include <stdio.h>
#include <stdlib.h>

typedef struct node{ int dado; struct node *prox; } NO;
NO *cria(int v){
	NO *n = (NO *) malloc(sizeof(NO));
	n->prox = NULL;
	n->dado = v;
	return n;
}
NO *insini(NO *l, int v){
	NO *n = cria(v);
	n->prox = l;
	return n;
}
void imp(NO *l){
	while(l){
		printf("%d ", l->dado);
		l = l->prox;
	}
	printf("\n");
}
NO *vet2lse(int *vet, int n){
	NO *l = NULL;
	for(int i=0; i<n; i++)
		l = insini(l, vet[i]);
	return l;
}

// Faça uma função recursiva que inverta uma lista simplesmente encadeada alterando somente seus ponteiros e não seus valores

NO *inv_aux(NO *ant, NO *atual){
	NO *prox = atual->prox;
	atual->prox = ant;
	if(prox) return inv_aux(atual, prox);
	return atual;
}
NO *inv(NO *l){
	if((!l) || (!l->prox)) return l;
	NO *ant = l, *atual = l->prox;
	ant->prox = NULL;
	return inv_aux(ant, atual);
}


int main(void){
	int vet[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	NO *l = vet2lse(vet, 8);
	imp(l);
	l = inv(l);
	imp(l);
}