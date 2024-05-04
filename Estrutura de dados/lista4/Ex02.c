#include <stdlib.h>
#include <stdio.h>

// Testar se uma árvore é zigue-zague, isto é, todos os nós internos, 
// exceto a raiz, possuem exatamente uma sub-árvore vazia:
// int zz(NO *a);
 
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
int zz(NO *a);

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
int zzaux(NO *a){
	if(!a) return 0;
	if((a->esq) && (a->dir)) return 1;
	return (zzaux(a->esq) || zzaux(a->dir));
}
int zz(NO *a){
	return !((!a) || (zzaux(a)));
}

