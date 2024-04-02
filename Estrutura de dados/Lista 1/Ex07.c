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
    int cor; // o = preto ; 1 = vermelho
    struct ab *esq, *dir;
} TAB;

TAB *vet2ab(int *vet, int n);
TAB *cria(int info, TAB *esq, TAB *dir);
void imprime(TAB *a);
TAB *colore(TAB *a);

// (Q7) se esta estrutura TAB tivesse um campo cor (int cor), defina uma função em C que, ao
// receber uma árvore binária “sem cor” e totalmente balanceada (isto é, a distância da raiz a qualquer
// folha da árvore é sempre a mesma), retorne esta árvore com os nós coloridos somente de vermelho e
// preto, sendo que o nó pai NUNCA pode ter a mesma cor de seus filhos. A função deve possuir o
// seguinte protótipo: void colore (TAB* arv);

int main(void){

    int vet[] = {1, 2, 3, 4, 5, 6};
    TAB *a = vet2ab(vet, 6);
    colore(a);

    imprime(a);

    return 0;
}

void imprime(TAB *a){
	if(a){
		printf("%d ", a->cor);
		imprime(a->esq);
		imprime(a->dir);
	}
}
TAB *criar(int info, TAB *esq, TAB *dir){
    TAB *n = (TAB *) malloc(sizeof(TAB));
    n->info = info;
    n->esq = esq;
    n->dir = dir;
    n->cor = -1;
    return n;
}
TAB *vet2ab(int *vet, int n){
    if(n <= 0) return NULL;
    return criar(vet[n/2], vet2ab(vet, n/2), vet2ab(&vet[n/2+1], n-n/2-1));
}
TAB *colore(TAB *a){
    if(a){
        if(a->cor == -1) a->cor = 1;
        if (a->cor == 1){
            if(a->esq) a->esq->cor = 0;
            if(a->dir) a->dir->cor = 0;
        }
        if (a->cor == 0){
            if(a->esq) a->esq->cor = 1;
            if(a->dir) a->dir->cor = 1;
        }
        colore(a->esq);
        colore(a->dir);
    }

}

