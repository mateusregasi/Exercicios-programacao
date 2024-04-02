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
TAB *retira_pares(TAB* arv);

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

FI *f_inicializa(){
    FI *f = (FI *) malloc(sizeof(FI));
    f->ini = f->fim = NULL;
    return f;
}
int f_vazia(FI *f){
    return (f->ini) ? 1 : 0;
}
FI *f_ins(FI *f, TAB *v){
    NO *n = (NO *) malloc(sizeof(NO));
    n->dado = (TAB *) v;
    n->prox = f->ini;
    if(f->fim == NULL) f->fim = f->ini;
    f->ini = n;
    return f;
}
TAB *f_ret(FI *f){
    if(f_vazia(f)) return NULL;
    NO *r = f->ini;
    f->ini = r->prox;
    if(f->ini == NULL) f->fim = NULL;
    TAB *v = r->dado;
    free(r);
    return v;
}
void f_free(FI *f){
    free(f);
}


TAB *retira_pares(TAB *arv){
    if(arv){
        arv->esq = retira_pares(arv->esq);
        arv->dir = retira_pares(arv->dir);

        if(arv->info % 2 == 0){
            TAB *r = arv;
            TAB *add;

            if(r->esq){
                arv = r->esq;
                add = r->dir;
            } else{
                arv = r->dir;
                add = r->esq;
            }
            free(r);

            FI *f = f_inicializa();
            f_ins(f, arv);
            while(!f_vazia(f)){
                TAB *aux = f_ret(f);
                if(!aux->esq){
                    aux->esq = add;
                    break;
                }
                if(!aux->dir){
                    aux->dir = add;
                    break;
                }
                f_ins(f, aux->esq);
                f_ins(f, aux->dir);
            }
            f_free(f);
        }
    }
    return arv;
}

