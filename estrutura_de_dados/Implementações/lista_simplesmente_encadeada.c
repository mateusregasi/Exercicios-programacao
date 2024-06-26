#include <stdlib.h>

// Lista
typedef struct node{
    void *dado;
    struct node *prox;
} NO;

typedef void impf(void *e);
typedef int cmpf(void *e1, void *e2);

NO *cria(void *e){
    NO *n = (NO *) malloc(sizeof(NO));
    n->prox = 0;
    n->dado = e;
    return n;
}
NO *insini(NO *n, void *e){
    NO *novo = cria(e);
    novo->prox = n;
    return novo;
}
NO *insfim(NO *n, void *e){
    NO *novo = cria(e), *a = n;
    if(!n) return novo;
    while(a->prox)
        a = a->prox;
    a->prox = novo;
    return n;
}
NO *insfim_rec(NO *n, void *e){
    if(!n) return cria(e);
    n->prox = insfim_rec(n->prox, e);
    return n;
}
NO *insord(NO *n, void *e, cmpf *f){
    NO *novo = cria(e), *a = n;
    if(!n) return novo;
    while((a->prox) && (f(a->prox->dado, e) < 0))
        a = a->prox;
    a->prox = novo;
    return n;
}
NO *insord_rec(NO *n, void *e, cmpf *f){
    if(!n) return cria(e);
    if(!n->prox){
        NO *i = cria(e);
        if(f(e, n->dado) < 0){
            i->prox = n;
            return i;
        } else {
            n->prox = i;
            return n;
        }
    }
    if(f(e, n->prox->dado) < 0){
        NO *i = cria(e);
        i->prox = n->prox;
        n->prox = i;
        return i;
    }
    n->prox = insord_rec(n->prox, e, f);
    return n;
}
void imp(NO *a, impf *f){
    while(a){
        f(a->dado);
        a = a->prox;
    }
}
NO *inv(NO *l){
    if((!l) || (!l->prox)) return l;
    NO *ant = l, *atual = l->prox;
    ant->prox = NULL;
    return inv_aux(ant, atual);
}
NO *inv_rec(NO *ant, NO *atual){
    NO *prox = atual->prox;
    atual->prox = ant;
    if(prox) return inv_rec(atual, prox);
    return atual;
}