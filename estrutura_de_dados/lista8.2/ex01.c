#include <stdio.h>
#include <stdlib.h>

// Dado um grafo conectado, verifique se ele pode ser transformado em árvore binária
typedef struct vizinho{
	int dado;
	struct vizinho *prox;
} VIZ;
typedef struct grafo{
	int dado;
	struct grafo *prox;
	VIZ *viz;
} GR;
typedef struct lista{
	int dado;
	struct lista *prox;
} NO;

// Funções auxiliares
GR *cria(int n);
VIZ *criav(int v);
int buscaa(GR *g, int x, int y);
int contaa(VIZ *v);
GR *busca(GR *g, int v);
GR *ins(GR *g, int v);
GR *insao(GR *g, int x, int y);
void imp(GR *g);
NO *insf(NO *f, int v);
NO *retf(NO *f, int *v);
int buscal(NO *l, int v);
void libl(NO *l);

//Função do exercício 
int teste(GR *g);

int main(void){

	// Cria um grafo
	GR *g = NULL;
	GR *g2 = NULL;
	g2 = ins(g2, 1);
	g2 = ins(g2, 2);
	g2 = ins(g2, 3);
	g2 = insao(g2, 1, 2);	
	g2 = insao(g2, 1, 3);	
	for(int i=1; i<11; i++){
		g = ins(g, i);
	}
	for(int i=1; i<11; i++){
		insao(g, i, (i + 3)%10);
		insao(g, i, (2*i + 1)%10);
		insao(g, i, (3*i)%10);
		insao(g, i, (5*i + 2)%10);
	}
	imp(g);

	printf("Isso é uma árvore?: %s\n", (teste(g2)) ? "sim" : "não");

	return 0;
}

// Funções auxiliares
GR *cria(int n){
	GR *g = (GR *) malloc(sizeof(GR));
	g->dado = n;
	g->viz = NULL;
	g->prox = NULL;
	return g;
}
VIZ *criav(int v){
	VIZ *viz = (VIZ *) malloc(sizeof(VIZ));
	viz->dado = v;
	viz->prox = NULL;
	return viz;
}
int buscaa(GR *g, int x, int y){
	while(g){
		if(g->dado == x){
			VIZ *v = g->viz;
			while(v){
				if(v->dado == y) return 1;
				v = v->prox;
			}
		}
		g = g->prox;
	}
	return 0;
}
int contaa(VIZ *v){
	int c = 0;
	while(v){
		c++;
		v = v->prox;
	}
	return c;
}
GR *busca(GR *g, int v){
	while(g){
		if(g->dado == v) return g;
		g = g->prox;
	}
	return NULL;
}
GR *ins(GR *g, int v){
	if(!busca(g, v)){
		GR *n = cria(v);
		n->prox = g;
		return n;
	}
	return g;
}
GR *insao(GR *g, int x, int y){
	GR *a = busca(g, x);
	if((a) && (busca(g, y))){
		if(!buscaa(a, x, y)){
			VIZ *v = criav(y);
			v->prox = a->viz;
			a->viz = v;
			return g;
		}
	}
	return g;
}
void imp(GR *g){
	while(g){
		printf("%d: ", g->dado);
		VIZ *v = g->viz;
		while(v){
			printf("%d ", v->dado);
			v = v->prox;
		}
		printf("\n");
		g = g->prox;
	}
}
NO *insf(NO *f, int v){
	NO *n = (NO *) malloc(sizeof(NO));
	n->dado = v;
	n->prox = NULL;
	NO *a = f;
	while((a) && (a->prox))
		a = a->prox;
	if(a){
		a->prox = n;
		return f;
	}
	return n;
}
NO *retf(NO *f, int *v){
	NO *r = f;
	*v = r->dado;
	f = f->prox;
	free(r);
	return f;
}
int buscal(NO *l, int v){
	while(l){
		if(l->dado == v) 
			return 1;
		l = l->prox;
	}
	return 0;
}
void libl(NO *l){
	NO *r;
	while(l){
		r = l;
		l = l->prox;
		free(r);
	}
}

// Função do exercício
int teste(GR *g){
	NO *f = insf(NULL, g->dado),
	   *l = NULL;
	GR *a;
	VIZ *v;
	int c, n;

	while(f){
		
		f = retf(f, &n);
		a = busca(g, n);
		v = a->viz;
		
		if((contaa(a->viz) > 2) || (buscal(l, n))){
			libl(f); libl(l);
			return 0;
		}
		l = insf(l, n);
		while(v){
			a = busca(g, v->dado);
			f = insf(f, a->dado);
			v = v->prox;
		}
	}
	return 1;
}