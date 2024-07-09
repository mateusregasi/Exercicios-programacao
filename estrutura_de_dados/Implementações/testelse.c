#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int dado;
    struct node *prox;
} NO;
NO *cria(int e){
    NO *n = (NO *) malloc(sizeof(NO));
    n->prox = 0;
    n->dado = e;
    return n;
}
NO *insfim_rec(NO *n, int e){
    if(!n) return cria(e);
    n->prox = insfim_rec(n->prox, e);
    return n;
}
NO *insord_rec(NO *n, int e){
    if(!n) return cria(e);
    if(!n->prox){
        NO *i = cria(e);
        if(e < n->dado){
            i->prox = n;
            return i;
        } else {
            n->prox = i;
            return n;
        }
    }
    if(e < n->prox->dado){
        NO *i = cria(e);
        i->prox = n->prox;
        n->prox = i;
        return i;
    }
    n->prox = insord_rec(n->prox, e);
    return n;
}
void imp(NO *a){
    while(a){
        printf("%d ", a->dado);
        a = a->prox;
    }
    printf("\n");
}

int main(void){
    NO *l1 = NULL, *l2 = NULL;
    
    l1 = insfim_rec(l1, 5);
    l1 = insfim_rec(l1, 2);
    l1 = insfim_rec(l1, 7);
    l1 = insfim_rec(l1, 9);
    imp(l1);
    
    printf("\n");

    l2 = insord_rec(l2, 5);
    l2 = insord_rec(l2, 2);
    l2 = insord_rec(l2, 7);
    l2 = insord_rec(l2, 9);
    imp(l2);

    return 0;
}