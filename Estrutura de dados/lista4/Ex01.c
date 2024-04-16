#include <stdlib.h>
#include <stdio.h>

// Escrever uma função e C que, dada uma árvore binária qualquer, 
// retorne, num vetor, todos os elementos menores que N. 
// A função deve ter o seguinte protótipo:
// int *mN(NO *a, int n, int *tam)
 
typedef struct node{
	int dado;
	struct ode *esq, *dir;
} NO;

// AUXILIARES
int *cp2vet(int *vet);
void imp(NO *a);
int *ins(NO *a, int n);
NO *vet2arv(int *vet);
NO *cria(int n, NO *esq, NO *dir);

// FUNÇÃO DO EXERCÍCIO
int *mN(NO *a, int n, int *tam);
int conta_menor(NO *a, int n);
void aux_mn(NO *a, int n, int *vet, int *tam);

int main(void){
	
	return 0;
}

// AUXILIARES
int *cp2vet(int *vet, int n){
	int *v = (int *) malloc(sizeof(int) * n);
	for(int i=0; i < n; i++) v[i] = vet[i];
	return v;	
}
NO *cria(int n, NO *esq, NO *dir){
	NO *no = (NO *) malloc(sizeof(NO));
	no->dado = n;
	no->esq = esq;
	no->dir = dir;
	return no;
}
int *ins(NO *a, int n){
	if(!a) return cria(n, NULL, NULL);
	if(n < a->dado) a->esq = ins(a->esq, n);
	else if(n > a->dado) a->dir = ins(a->dir, n);
	return a;
}
NO *vet2arv(int *vet, int n){
	NO *n = NULL;
	for(int i=0; i < n; i++) n = ins(n, i[n]);
	return n;
}
void imp(NO *a){
	if(a){
		imp(a->esq);
		printf("%d ", a->dado);
		imp(a->dir);
	}
}

// FUNÇÃO DO EXERCÍCIO
int conta_menor(NO *a, int n){
	if(a->dado > n) return 0;
	return ((a->dado <= n) 1 : 0) + conta_menor(a->esq, n) + conta_menor(a->dir, n);
}
void aux_mn(NO *a, int n, int *vet, int *tam){
	if(!a) return NULL;
	aux_mn(a->esq, n, tam);
	
	if(a->dado <= n){
		vet[*tam] = a->dado;
		(*tam)++;
	}

	if(a->dado < n) aux_mn(a->dir, n, tam);
}
int *mN(NO *a, int n, int *tam){
	*tam = conta_menor(a, n);

	int *vet = (int *) malloc(sizeof(int) * (*tam));
	*tam = 0;

	aux_mn(a, n, vet, tam);
	return vet;
}

