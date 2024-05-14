#include <stdio.h>
#include <stdlib.h>

typedef struct viz {
    int id_viz;
    int cor;
    struct viz *prox_viz;
}TVIZ;

typedef struct grafo{
    int id_no;
    int cor;
    TVIZ *prim_viz;
    struct grafo *prox_no;
}TG;

// (Q3) se esta estrutura tivesse um campo cor (int cor) na estrutura de grafo, teste se nós vizinhos não tem a mesma cor. A função retorna um se os vizinhos não tem a mesma cor e zero, caso contrário: int nao_tem_mesma_cor(TG *g);

// Funções auxilidares
TG *cria(int n, int cor);
TVIZ *cria_viz(int n, int cor);
TG *ins(TG *g, int v, int cor);
TG *busca(TG *g, int v);
TG *busca_ar(TG *g, int v, int j);
TG *add_ar_dir(TG *g, int i, int j);
void imp(TG *g);

// Função da questão
int nao_tem_mesma_cor(TG *g);

int main(void){
    TG *g = NULL;
    for(int i=0; i<10; i++){
        g = ins(g, i, (i*2+3)%5);
        add_ar_dir(g, i, (i*1+3)%10);
        add_ar_dir(g, i, (i*3+3)%10);
        add_ar_dir(g, i, (i*4+3)%10);
    }
    imp(g);
    printf("O grafo %d tem a cor %d. Tem alguém que ele está ligado que tenha a mesmo cor?: %s\n", g->id_no, g->cor,(nao_tem_mesma_cor(g)) ? "não" : "sim");
    return 0;
}

// Função da questão
int nao_tem_mesma_cor(TG *g){
    TVIZ *v = g->prim_viz;
    while(v){
        printf("(%d)", v->cor);
        if(v->cor == g->cor)
            return 0;
        v = v->prox_viz;
    }
    return 1;
}

// Funções auxilidares
TG *cria(int n, int cor){
    TG *novo = (TG *) malloc(sizeof(TG));
    novo->id_no = n;
    novo->cor = cor;
    novo->prox_no = NULL;
    novo->prim_viz = NULL;
    return novo;
}
TVIZ *cria_viz(int n, int cor){
    TVIZ *v = (TVIZ *) malloc(sizeof(TVIZ));
    v->id_viz = n;
    v->cor = cor;
    v->prox_viz = NULL;
    return v;
}
TG *ins(TG *g, int v, int cor){
    if(!busca(g, v)){
        TG *novo = cria(v, cor);
        novo->prox_no = g;
        return novo;
    }
    return g;
}
void imp(TG *g){
    TVIZ *v;
    while(g){
        printf("%d de cor %d: ", g->id_no, g->cor);
        v = g->prim_viz;
        while(v){
            printf("%d ", v->id_viz);
            v = v->prox_viz;
        }
        printf("\n");
        g = g->prox_no;
    }
}
TG *busca(TG *g, int v){
    while(g){
        if(g->id_no == v) return g;
        g = g->prox_no;
    }
    return NULL;
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
    TG *a = busca(g, i),
       *b = busca(g, j);
    if((!a) || (!b)) return g; 
    if(!busca_ar(a, i, j)){
        TVIZ *v = cria_viz(j, b->cor);
        v->prox_viz = a->prim_viz;
        a->prim_viz = v;
    }
    return g;
}
