#include <stdlib.h>
#include <stdio.h>

// Verifiar se uma árvore é estritamente binária, isto é, os nós 
// dessa árvore possuem ou zero ou dois filhos
// int estbin(NO *a);
 
typedef struct node{
	int dado;
	struct ode *esq, *dir;
} NO;
typedef struct node{
	int dado;
	struct prox;
} NOL;

// AUXILIARES
int *cp2vet(int *vet);
void imp(NO *a);
int *ins(NO *a, int n);
NO *vet2arv(int *vet);
NO *cria(int n, NO *esq, NO *dir);

// FUNÇÃO DO EXERCÍCIO

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
int estbin(NO *a){
	if(!a) return 1;
	if(((a->esq) && (!a->dir)) || ((!a->esq) && (a->dir))) return 0;
	return (estbin(a->esq) && estbin(a->dir)); 
}