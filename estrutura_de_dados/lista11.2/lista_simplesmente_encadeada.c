#include <stdlib.h>

// Lista
typedef struct node{
    void *dado;
    struct node *prox;
} NOL;

typedef void impf(void *e);
typedef int cmpf(void *e1, void *e2);

NOL *cria(void *e){
    NOL *n = (NOL *) malloc(sizeof(NOL));
    n->prox = 0;
    n->dado = e;
    return n;
}
NOL *insini(NOL *n, void *e){
    NOL *novo = cria(e);
    novo->prox = n;
    return novo;
}
NOL *insfim(NOL *n, void *e){
    NOL *novo = cria(e), *a = n;
    if(!n) return novo;
    while(a->prox)
        a = a->prox;
    a->prox = novo;
    return n;
}
NOL *insfim_rec(NOL *n, void *e){
    if(!n) return cria(e);
    n->prox = insfim_rec(n->prox, e);
    return n;
}
NOL *insord(NOL *n, void *e, cmpf *f){
    NOL *novo = cria(e), *a = n;
    if(!n) return novo;
    while((a->prox) && (f(a->prox->dado, e) < 0))
        a = a->prox;
    a->prox = novo;
    return n;
}
NOL *insord_rec(NOL *n, void *e, cmpf *f){
    if(!n) return cria(e);
    if(!n->prox){
        NOL *i = cria(e);
        if(f(e, n->dado) < 0){
            i->prox = n;
            return i;
        } else {
            n->prox = i;
            return n;
        }
    }
    if(f(e, n->prox->dado) < 0){
        NOL *i = cria(e);
        i->prox = n->prox;
        n->prox = i;
        return i;
    }
    n->prox = insord_rec(n->prox, e, f);
    return n;
}
void imp(NOL *a, impf *f){
    while(a){
        f(a->dado);
        a = a->prox;
    }
}
NOL *inv(NOL *l){
    if((!l) || (!l->prox)) return l;
    NOL *ant = l, *atual = l->prox;
    ant->prox = NULL;
    return inv_aux(ant, atual);
}
NOL *inv_rec(NOL *ant, NOL *atual){
    NOL *prox = atual->prox;
    atual->prox = ant;
    if(prox) return inv_rec(atual, prox);
    return atual;
}