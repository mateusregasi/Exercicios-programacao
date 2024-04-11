// Dada a seguinte representação de uma árvore binária de busca (ABB):
// typedef struct ab{
//     int info;
//     struct ab *esq, *dir;
// } TABB;
// Escreva as seguintes funções:

#include <stdio.h>
#include <stdlib.h>

#define tam(vetor) (sizeof((vetor)) / sizeof(int))
#define maior(a, b) ((a >= b) ? a : b)

typedef struct node{
    void *dado;
    struct node *prox;
} NO;
typedef struct ab{
    int dim, area;
    struct ab *esq, *dir;
} TABB;

TABB *inicializa();
TABB *criar(int dim, int area, TABB *esq, TABB *dir);
void destroi(TABB *a);
void imprime(TABB *a);
TABB *destroi_no(TABB *a);
TABB *retira_elemento(TABB *a, int area, int dim);
TABB *retira_no(TABB *a, int *dim, int *area);
TABB *insere(TABB *a, int dim, int area);
TABB *vet2abb(int *v, int n);
TABB *abb2vet(TABB *a);
int *altura(TABB *a);
int conta(TABB *a);


// (Q5) Reescreva as operações básicas da ABB para poder armazenar as figuras geométricas
// quadrado, triângulo, retângulo e trapézio. A área da figura será usada para definir os elementos
// pertencentes a sub-árvore esquerda e a sub-árvore direita. A impressão será em ordem simétrica e,
// além da área, devem ser informadas as dimensões da figura.

int main(void){

    int vet[] = {1, 4, 6 , 2, 3, 5, 7};

    TABB *a = vet2ab(vet, 7);
    int *b = mN(a, 4);
    // for(int i = 0; i < tam(b); i++) printf("%d ", b[i]);

    return 0;
}

TABB *inicializa(){
    return NULL;
}
int *altura(TABB *a){
    if(!a) return -1;
    return 1 + maior(altura(a->esq), altura(a->dir));
}
int conta(TABB *a){
    if(!a) return 0; 
    return 1 + conta(a->esq) + conta(a->dir);
}
TABB *criar(int dim, int area, TABB *esq, TABB *dir){
    TABB *n = (TABB *) malloc(sizeof(TABB));
    n->dim = dim;
    n->area = area;
    n->esq = esq;
    n->dir = dir;
    return n;
}
void destroi(TABB *a){
    if(a){
        destroi(a->esq);
        destroi(a->dir);
        free(a);
    }
}
void imprime(TABB *a){
        if(a){
        destroi(a->esq);
        printf("(a%d, d%d) ", a->area, a->dim);
        destroi(a->dir);
    }
}
TABB *destroi_no(TABB *a){
    if(!a) return a;
    if(a->esq) a->esq = destroi_no(a->esq);
    else if(a->dir) a->dir = destroi_no(a->dir);
    else free(a);
    return a;
}
TABB *retira_elemento(TABB *a, int area, int dim){
    if(!a) return;
    if((a->area < area) || 
        ((a->area == area) && (a->dim < dim))) 
        a->esq = destroi_elemento(a->dir, area, dim);
    else if((a->area > area) || 
        ((a->area == area) && (a->dim > dim))) 
        a->dir = destroi_elemento(a->dir, area, dim);
    else{
        if((!a->esq) && (!a->dir)){
            free(a);
            return NULL;
        } else if((!a->esq) || (!a->dir)){
            TABB *t = (a->esq) ? a->esq : a->dir;
            free(a);
            return t;
        } else{
            TABB *t = a->esq;
            while(t->dir) t = t->dir;
            a->area = t->area;
            a->dim = t->dim;
            t->area = area;
            t->dim = dim;
            a->esq = destroi_elemento(a->esq, area, dim);
        }
    }
    return a;
}
TABB *retira_no(TABB *a, int *dim, int *area){
    if(!a) return a;
    if(a->esq) a->esq = retira_no(a->esq, dim, area);
    else if(a->dir) a->dir = retira_no(a->dir, dim, area);
    else{
        (*dim) = a->dim;
        (*area) = a->area;
        free(a);
    }
    return a;
}
TABB *insere(TABB *a, int dim, int area){
    if(!a) return criar(dim, area, NULL, NULL);
    if((a->area < area) || 
        ((a->area == area) && (a->dim < dim))) 
        a->esq = destroi_elemento(a->dir, area, dim);
    else if((a->area > area) || 
        ((a->area == area) && (a->dim > dim))) 
        a->dir = destroi_elemento(a->dir, area, dim);
    return a;
}
TABB *busca(TABB *a, int dim, int area){
    if((!a) || ((a->dim == dim) && (a->area == area))) return a;
    if((a->area < area) || 
        ((a->area == area) && (a->dim < dim))) 
        return busca(a->dir, area, dim);
    else if((a->area > area) || 
        ((a->area == area) && (a->dim > dim))) 
        return busca(a->dir, area, dim);
}
TABB *vet2abb(int *v, int n){
    if(!v) return NULL;
    return cria(v[0], v[1], vet2abb(v, n/2), vet2abb(&v[n/2+1], n-n/2-1));
}
TABB *abb2vet(TABB *a){
    int n = conta(a) * 2, i = 0;
    int *vet = malloc(sizeof(int) * n);
    abb2vetaux(a, vet, &i);
    return vet;
}
void *abb2vetaux(TABB *a, int *vet, int *i){
    abb2vetaux(a->esq, vet, &i);
    vet[(*i)] = a->dim;
    vet[(*i)+1] = a->area;
    (*i) += 2;
    abb2vetaux(a->dir, vet, &i);
}