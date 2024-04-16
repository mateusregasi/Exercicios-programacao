#include <stdlib.h>
#include <stdio.h>

// Testar se duas árvores possuam as mesmas informações
// int mi(NO *a1, NO *a2);
 
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
NO *busca(NO *a, int n);

// FUNÇÃO DO EXERCÍCIO
int mi(NO *a1, NO *a2);

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
NO *busca(NO *a, int n){
	if((!a) || (a->dado == n)) return a;
	NO *resp = busca(a->esq);
	if(resp) return resp;
	return busca(a->dir);
}

// FUNÇÃO DO EXERCÍCIO
int conta(NO *a){
	if(!a) return 0;
	return 1 + conta(a->esq) + conta_menor(a->dir);
}
int mi_aux(a1, a2){
	if(!a) return 1;
	else{
		if(!busca(a2, a1->dado)) return 0;
		return (mi_aux(a1->esq, a2) && mi_aux(a1->dir, a2));
	}
}
int mi(NO *a1, NO *a2){
	if(conta(a1) != conta(a2)) return 0;
	return mi_aux(a1, a2);
}