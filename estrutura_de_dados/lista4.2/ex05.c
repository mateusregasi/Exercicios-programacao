#include <stdio.h>
#include <stdlib.h>

typedef struct viz {
    int id_viz;
    struct viz *prox_viz;
}TVIZ;

typedef struct grafo{
    int id_no;
    TVIZ *prim_viz;
    struct grafo *prox_no;
}TG;

// (Q5) testar se dois grafos são iguais - int ig(TG *g1, TG *g2).

// Funções auxilidares
TG *cria(int n);
TVIZ *cria_viz(int n);
TG *ins(TG *g, int v);
TG *busca(TG *g, int v);
TG *busca_ar(TG *g, int v, int j);
TG *add_ar_dir(TG *g, int i, int j);
void imp(TG *g);

// Função da questão
int bar(int i, TVIZ *v){
    while(v){
        if(i != v->id_viz)
            return 0;
        v = v->prox_viz;
    }
    return 1;
}
int compara_viz(TVIZ *v1, TVIZ *v2){
    while(v1){
        if(!bar(v1->id_viz, v2))
            return 0;
        v1 = v1->prox_viz;
    }
    return 1;
}
int compara(TG *g1, TG *g2){
    TG *g = NULL;
    while(g1){

        g = busca(g2, g1->id_no);
        if(!g) return 0;

        if(!compara_viz(g1->prim_viz, g->prim_viz)) 
            return 0;
        if(!compara_viz(g->prim_viz, g1->prim_viz)) 
            return 0;

        g1 = g1->prox_no;
    }

    return 1;
}
int ig(TG *g1, TG *g2){
    TG *a = g1, *b = g2;

    if(!compara(b, a))
        return 0;
    if(!compara(a, b))
        return 0;

    return 1;
}

int main(void){
    TG *g1 = NULL, 
       *g2 = NULL;
    for(int i=0; i<10; i++){
        g1 = ins(g1, i);
        g2 = ins(g2, i);
        add_ar_dir(g1, i, 0);
        add_ar_dir(g2, i, 0);
        // add_ar_dir(g2, i, (i*2+1)%10);
        // add_ar_dir(g1, i, (i*3+5)%10);
        // add_ar_dir(g, i, (i*4+1)%10);
    }
    imp(g1);
    printf("\n");
    imp(g2);
    printf("\n");

    printf("Os grafos são iguais?: %s\n", (ig(g1, g2)) ? "sim" : "não");

    return 0;
}

// Função da questão

// Funções auxilidares
TG *busca(TG *g, int v){
    while(g){
        if(g->id_no == v) return g;
        g = g->prox_no;
    }
    return NULL;
}
TG *cria(int n){
    TG *novo = (TG *) malloc(sizeof(TG));
    novo->id_no = n;
    novo->prox_no = NULL;
    novo->prim_viz = NULL;
    return novo;
}
TVIZ *cria_viz(int n){
    TVIZ *v = (TVIZ *) malloc(sizeof(TVIZ));
    v->id_viz = n;
    v->prox_viz = NULL;
    return v;
}
TG *ins(TG *g, int v){
    if(!busca(g, v)){
        TG *novo = cria(v);
        novo->prox_no = g;
        return novo;
    }
    return g;
}
void imp(TG *g){
    TVIZ *v;
    while(g){
        printf("%d: ", g->id_no);
        v = g->prim_viz;
        while(v){
            printf("%d ", v->id_viz);
            v = v->prox_viz;
        }
        printf("\n");
        g = g->prox_no;
    }
}
TG *busca_ar(TG *g, int i, int j){
    TG *gi = busca(g, i);
    if(!gi) return NULL;
    if(!busca(g, j)) return NULL;
    TVIZ *v = gi->prim_viz;
    while(v){
        v = v->prox_viz;
    }
    return 0;
}
TG *add_ar_dir(TG *g, int i, int j){
    TG *a = busca(g, i);
    if((!a) || (!busca(g, j))) return g; 
    if(!busca_ar(a, i, j)){
        TVIZ *v = cria_viz(j);
        v->prox_viz = a->prim_viz;
        a->prim_viz = v;
    }
    return g;
}