// Dada a seguinte representação de uma árvore binária de busca (ABB):
// typedef struct ab{
//     int info;
//     struct ab *esq, *dir;
// } TABB;
// Escreva as seguintes funções:

#include <stdio.h>
#include <stdlib.h>

#define tam(vetor) (sizeof((vetor)) / sizeof(int))

typedef struct node{
    void *dado;
    struct node *prox;
} NO;
typedef struct ab{
    int info;
    struct ab *esq, *dir;
} TABB;

TABB *vet2ab(int *vet, int n);
TABB *cria(int info, TABB *esq, TABB *dir);
void imprime(TABB *a);
int *mN(TABB*a, int N);

// (Q4) uma função em C que, dada uma árvore binária de busca qualquer, retorne, num vetor, todos
// os elementos menores que N. A função deve ter o seguinte protótipo: int* mN(TABB*a, int N);

int main(void){

    int vet[] = {1, 4, 6 , 2, 3, 5, 7};

    TABB *a = vet2ab(vet, 7);
    int *b = mN(a, 4);
    // for(int i = 0; i < tam(b); i++) printf("%d ", b[i]);

    return 0;
}
int *vet2vet(int *v){
    int n = tam(v), *v2 = (int *) malloc(sizeof(int) * n);
    for(int i=0; i<n; i++) v2[i] = v[i];
    return v2;
}
void imprime(TABB *a){
	if(a){
		imprime(a->esq);
		printf("%d ", a->info);
		imprime(a->dir);
	}
}
TABB *criar(int info, TABB *esq, TABB *dir){
    TABB *n = (TABB *) malloc(sizeof(TABB));
    n->info = info;
    n->esq = esq;
    n->dir = dir;
    return n;
}
TABB *ins(TABB *a, int n){
    if(!a) return criar(n, NULL, NULL);
    if(a->info > n) a->esq = ins(a->esq, n);
    else if(a->info < n) a->dir = ins(a->dir, n); 
    return a;
}
TABB *vet2ab(int *vet, int n){
    TABB *a = NULL;
    for(int i = 0; i < n; i++) a = ins(a, vet[i]);
    return a;
}
int num_ele(TABB *a){
    if(!a) return 0;
    return 1 + num_ele(a->esq) + num_ele(a->dir);
}
int num_ele_n(TABB *a, int n){
    if((!a) || (a->info > n)) return 0;
    return 1 + num_ele_n(a->esq, n) + num_ele_n(a->dir, n);
} 
void menor_n(TABB *a, int *v, int *i, int n){
    if(!a) return NULL;
    menor_n(a->esq, v, i, n);
    if(a->info > n) return;
    v[(*i)] = a->info;
    (*i)++; 
    menor_n(a->dir, v, i, n);
}
int *mN(TABB *a, int N){
    if(!a) return  NULL;
    int n = num_ele_n(a, N),
        *vet = (int *) malloc(sizeof(int) * n),
        i = 0;
    menor_n(a, vet, &i, N);
    return vet;
}