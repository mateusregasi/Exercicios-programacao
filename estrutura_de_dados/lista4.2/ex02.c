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

// (Q2) ache a quantidade de arestas: int na(TG *g);

// Funções auxilidares
TG *cria(int n);
TVIZ *cria_viz(int n);
TG *ins(TG *g, int v);
TG *busca(TG *g, int v);
TG *busca_ar(TG *g, int v, int j);
TG *add_ar_dir(TG *g, int i, int j);
void imp(TG *g);

// Função da questão
int na(TG *g);

int main(void){
    TG *g = NULL;
    for(int i=0; i<10; i++){
        g = ins(g, i);
        add_ar_dir(g, i, i-1);
    }
    imp(g);

    printf("Número de arestas: %d\n", na(g));

    return 0;
}

// Função da questão
int na(TG *g){
    int c = 0;
    TVIZ *v;
    while(g){
        v = g->prim_viz;
        while(v){
            c++;
            v = v->prox_viz;
        }
        g = g->prox_no;
    }
    return c;
}

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