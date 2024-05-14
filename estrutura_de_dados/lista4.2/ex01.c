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

// (Q1) descubra a quantidade de nós: int nn(TG *g);

// Funções auxilidares
TG *cria(int n);
TG *ins(TG *g, int v);
TG *busca(TG *g, int v);

// Função da questão
int nn(TG *g);

int main(void){
    TG *g = NULL;
    for(int i=0; i<5; i++)
        g = ins(g, i);
    printf("Número de elementos no grafo: %d\n", nn(g));
    imp(g);
    return 0;
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

// Função da questão
int nn(TG *g){
    int n = 0;
    while(g){
        g = g->prox_no;
        n++;
    }
    return n;
}