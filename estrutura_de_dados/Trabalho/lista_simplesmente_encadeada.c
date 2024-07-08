#include <stdlib.h>

// Lista
typedef struct node{
    void *dado;
    struct node *prox;
} TLSE;

typedef void impf(void *e);
typedef int cmpf(void *e1, void *e2);

TLSE *TLSE_cria(void *e){
    TLSE *n = (TLSE *) malloc(sizeof(TLSE));
    n->prox = NULL;
    n->dado = e;
    return n;
}
TLSE *TLSE_insini(TLSE *n, void *e){
    TLSE *novo = TLSE_cria(e);
    novo->prox = n;
    return novo;
}
TLSE *TLSE_insfim(TLSE *n, void *e){
    TLSE *novo = TLSE_cria(e), *a = n;
    if(!n) return novo;
    while(a->prox)
        a = a->prox;
    a->prox = novo;
    return n;
}
TLSE *TLSE_insfim_rec(TLSE *n, void *e){
    if(!n) return TLSE_cria(e);
    n->prox = TLSE_insfim_rec(n->prox, e);
    return n;
}
TLSE *TLSE_insord(TLSE *n, void *e, cmpf *f){
    TLSE *novo = TLSE_cria(e), *a = n;
    if(!n) return novo;
    while((a->prox) && (f(a->prox->dado, e) < 0))
        a = a->prox;
    a->prox = novo;
    return n;
}
TLSE *TLSE_insord_rec(TLSE *n, void *e, cmpf *f){
    if(!n) return TLSE_cria(e);
    if(!n->prox){
        TLSE *i = TLSE_cria(e);
        if(f(e, n->dado) < 0){
            i->prox = n;
            return i;
        } else {
            n->prox = i;
            return n;
        }
    }
    if(f(e, n->prox->dado) < 0){
        TLSE *i = TLSE_cria(e);
        i->prox = n->prox;
        n->prox = i;
        return i;
    }
    n->prox = TLSE_insord_rec(n->prox, e, f);
    return n;
}
void TLSE_imp(TLSE *a, impf *f){
    while(a){
        if(a->dado) f(a->dado);
        a = a->prox;
    }
}
TLSE *TLSE_inv_rec(TLSE *ant, TLSE *atual){
    TLSE *prox = atual->prox;
    atual->prox = ant;
    if(prox) return TLSE_inv_rec(atual, prox);
    return atual;
}
TLSE *TLSE_inv(TLSE *l){
    if((!l) || (!l->prox)) return l;
    TLSE *ant = l, *atual = l->prox;
    ant->prox = NULL;
    return TLSE_inv_rec(ant, atual);
}
TLSE *TLSE_retini(TLSE *l, void *v){
    v = l->dado;
    TLSE *a = l->prox;
    free(l);
    return a;
}
void *TLSE_get(TLSE *l, int n){
    int i = 0;
    while(l && i != n){
        l = l->prox;
        i++;
    }
    return (l) ? l->dado : NULL;
}
int TLSE_conta(TLSE *l){
    int c = 0;
    while(l){
        c++;
        l = l->prox;
    }
    return c;
}
void *TLSE_troca(TLSE *l, int n, void *v){
    int c = 0;
    void *t = NULL;
    while((l) && (c != n)){
        l = l->prox;
        c++;
    }
    if(l){
        t = l->dado;
        l->dado = v;
    }
    return t;
}
void TLSE_set(TLSE *l, int n, void *v){
    int c = 0;
    void *t = NULL;
    while((l) && (c != n)){
        l = l->prox;
        c++;
    }
    if(l) l->dado = v;
}
TLSE *TLSE_busca(TLSE *l, void *e, cmpf f){
    while(l && f(l->dado, e))
        l = l->prox;
    return l;
}
int TLSE_buscai(TLSE *l, void *e, cmpf f){
    int i = 0;
    while(l && f(l->dado, e)){
        i++;
        l = l->prox;
    }
    return (l) ? i : -1;
}
void *TLSE_maior(TLSE *l, cmpf *f){
    if(!l) return l;
    void *m = l->dado;
    l = l->prox;
    while(l){
        if(f(l->dado, m) > 0)
            m = l->dado;
        l = l->prox;
    }
    return m;
}
int TLSE_maiori(TLSE *l, cmpf *f){
    if(!l) return -1;
    void *m = l->dado;
    int c = 1, cm = 0;
    l = l->prox;
    while(l){
        if(f(l->dado, m) > 0){
            m = l->dado;
            cm = c;
        }
        l = l->prox;
    }
    printf("%d", cm);
    return cm;
}
void *TLSE_menor(TLSE *l, cmpf *f){
    if(!l) return l;
    void *m = l->dado;
    l = l->prox;
    while(l){
        if(f(l->dado, m) < 0)
            m = l->dado;
        l = l->prox;
    }
    return m;
}
int TLSE_menori(TLSE *l, cmpf *f){
    if(!l) return l;
    void *m = l->dado;
    int c = 1, cm = 0;
    l = l->prox;
    while(l){
        if(f(l->dado, m) < 0){
            m = l->dado;
            cm = c;
        }
        l = l->prox;
        c++;
    }
    return cm;
}
TLSE *TLSE_get_no(TLSE *l, int n){
    int i = 0;
    while(l && i != n){
        l = l->prox;
        i++;
    }
    return l;
}
void TLSE_libera(TLSE *l){
    TLSE *r;
    while(l){
        r = l;
        l = l->prox;
        free(r->dado);
        free(r);
    }
}