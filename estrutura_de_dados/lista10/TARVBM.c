#include <stdio.h>
#include <stdlib.h>

typedef struct arvbm{
    int n, folha, *chaves;
    struct arvbm *prox, **filhos;
} NO;

NO *cria(int t){
  NO *n = (NO *) malloc(sizeof(NO));
  n->n = 0;
  n->chaves =(int *) malloc(sizeof(int) * ((t*2)-1));
  n->folha = 1;
  n->filhos = (NO **) malloc(sizeof(NO*) * t*2);
  n->prox = NULL;
  int i;
  for(i=0; i<(t*2); i++) 
    n->filhos[i] = NULL;
  return n;
}

NO *inicializa(void){
  return NULL;
}

void libera(NO *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i<=a->n; i++) 
        libera(a->filhos[i]);
    }
    free(a->chaves);
    free(a);
  }
}

NO *busca(NO *a, int v){
  if (!a) return NULL;
  int i = 0;
  while ((i < a->n) && (v > a->chaves[i])) i++;
  if ((i < a->n) && (a->folha) && (v == a->chaves[i])) return a;
  if (a-> folha) return NULL;
  if (a->chaves[i] == v) i++;
  return busca(a->filhos[i], v);
}


void imprime_chaves(NO *a){
  if(!a) return;
  NO *p = a;
  while(p->filhos[0]) 
    p = p->filhos[0];
  while(p){
    int i;
    for(i = 0; i < p->n; i++) 
        printf("%d ", p->chaves[i]);
    p = p->prox;
  }
  printf("\n");
}


void imp(NO *a, int tab){
  if(a){
    int i,j;
    for(i=0; i<=a->n-1; i++){
      imp(a->filhos[i], tab+1);
      for(j=0; j<=tab; j++) 
        printf("\t");
      printf("%d\n", a->chaves[i]);
    }
    imp(a->filhos[i], tab+1);
  }
}

void imprime(NO *a){
  imp(a, 0);
}

NO *divide(NO *x, int i, NO* y, int t){
  NO *n = cria(t);
  n->folha = y->folha;
  int j;
  if(!y->folha){
    n->n = t-1;
    for(j=0; j<t-1; j++) 
        n->chaves[j] = y->chaves[j+t];
    for(j=0; j<t; j++){
      n->filhos[j] = y->filhos[j+t];
      y->filhos[j+t] = NULL;
    }
  } else {
    n->n = t;
    for(j=0; j<t; j++) 
        n->chaves[j] = y->chaves[j+t-1];
    n->prox = y->prox;
    y->prox = n;
  }
  y->n = t-1;
  for(j=x->n; j>=i; j--) 
    x->filhos[j+1]=x->filhos[j];
  x->filhos[i] = n;
  for(j=x->n; j>=i; j--) 
    x->chaves[j] = x->chaves[j-1];
  x->chaves[i-1] = y->chaves[t-1];
  x->n++;
  return x;
}


NO *insere_incompleto(NO *x, int v, int t){
  int i = x->n-1;
  if(x->folha){
    while((i>=0) && (v < x->chaves[i])){
      x->chaves[i+1] = x->chaves[i];
      i--;
    }
    x->chaves[i+1] = v;
    x->n++;
    return x;
  }
  while((i>=0) && (v < x->chaves[i])) i--;
  i++;
  if(x->filhos[i]->n == ((2*t)-1)){
    x = divide(x, (i+1), x->filhos[i], t);
    if(v > x->chaves[i]) i++;
  }
  x->filhos[i] = insere_incompleto(x->filhos[i], v, t);
  return x;
}

NO *insere(NO *a, int v, int t){
  if(busca(a, v)) return a;
  if(!a){
    a=cria(t);
    a->chaves[0] = v;
    a->n = 1;
    return a;
  }
  if(a->n == (2*t)-1){
    NO *n = cria(t);
    n->n = 0;
    n->folha = 0;
    n->filhos[0] = a;
    n = divide(n, 1, a, t);
    n = insere_incompleto(n, v, t);
    return n;
  }
  a = insere_incompleto(a, v, t);
  return a;
}

NO* remova(NO *a, int v, int t);

NO *caso1(NO *a, int i){
    int j;
    for(j=i; j<a->n-1; j++) 
        a->chaves[j] = a->chaves[j+1];
    a->n--;
    if(!a->n){
      libera(a);
      a = NULL;
    }
    return a;   
}

NO *caso3Adir(NO *a, int i, int t, int v){
    NO *f = a->filhos[i], 
       *fp = a->filhos[i+1];
    if(!f->folha){
        f->chaves[t-1] = a->chaves[i];
        a->chaves[i] = fp->chaves[0]; 
    } else{ 
        a->chaves[i] = fp->chaves[0] + 1;
        f->chaves[t-1] = fp->chaves[0];
    }
    f->n++;
    int j;
    for(j=0; j < fp->n-1; j++)
        fp->chaves[j] = fp->chaves[j+1];
    f->filhos[f->n] = fp->filhos[0]; 
    for(j=0; j < fp->n; j++)
        fp->filhos[j] = fp->filhos[j+1];
    fp->n--;
    a->filhos[i] = remova(a->filhos[i], v, t);
    return a;
}

NO *caso3Aesq(NO *a, int i, int t, int v){
    NO *f = a->filhos[i], *fa = a->filhos[i-1];
    int j;
    for(j = f->n; j>0; j--)
        f->chaves[j] = f->chaves[j-1];
    for(j = f->n+1; j>0; j--)    
        f->filhos[j] = f->filhos[j-1];
    if(!f->folha){
        f->chaves[0] = a->chaves[i-1];   
        a->chaves[i-1] = fa->chaves[fa->n - 1]; 
    } else{ 
        a->chaves[i-1] = fa->chaves[fa->n - 1];
        f->chaves[0] = fa->chaves[fa->n-1];
    }
    f->n++;
    f->filhos[0] = fa->filhos[fa->n];
    fa->n--;
    a->filhos[i] = remova(f, v, t);
    return a;
}

NO *caso3Besq(NO *a, int i, int t, int v){
    NO *f = a->filhos[i], *fa = a->filhos[i-1];
    if(!f->folha){
        if(i == a->n)
            fa->chaves[t-1] = a->chaves[i-1];
        else
            fa->chaves[t-1] = a->chaves[i];
        fa->n++;
    }
    int j = 0;
    while(j < t-1){
        if(!f->folha) fa->chaves[t+j] = f->chaves[j];
        else fa->chaves[t+j-1] = f->chaves[j];
        fa->n++;
        j++;
    }
    fa->prox = f->prox; 
    if(!fa->folha){
        for(j=0; j<t; j++){
            fa->filhos[t+j] = f->filhos[j];
            f->filhos[j] = NULL; 
        }
        libera(f);
    }
    a->filhos[a->n] = NULL;
    a->n--;
    if(!a->n){
        NO *temp = a;
        a = a->filhos[0];
        temp->filhos[0] = NULL;
        libera(temp);
        a = remova(a, v, t);
    } else{
        i--;
        a->filhos[i] = remova(a->filhos[i], v, t);
    }
    return a;
}

NO *caso3Bdir(NO *a, int i, int t, int v){
    NO *f = a->filhos[i], 
       *fp = a->filhos[i+1];
    if(!f->folha){
        f->chaves[t-1] = a->chaves[i];
        f->n++;
    }
    int j = 0;
    while(j < t-1){
        if(!f->folha) f->chaves[t+j] = fp->chaves[j];
        else f->chaves[t+j-1] = fp->chaves[j];
        f->n++;
        j++;
    }
    f->prox = fp->prox;
    if(!f->folha){
        for(j=0; j<t; j++){
            f->filhos[t+j] = fp->filhos[j];
            fp->filhos[j] = NULL;
        }
        libera(fp);
    }
    for(j=i; j < a->n-1; j++){
        a->chaves[j] = a->chaves[j+1];
        a->filhos[j+1] = a->filhos[j+2];
    }
    a->filhos[a->n] = NULL;
    a->n--;
    if(!a->n){ 
        NO *temp = a;
        a = a->filhos[0];
        temp->filhos[0] = NULL;
        libera(temp);
    }
    a = remova(a, v, t);
    return a;
}

NO *remova(NO *a, int v, int t){
  if(!a) return a;
  int i;
  for(i = 0; i < a->n && a->chaves[i] < v; i++);
  if(a->folha){
    if((i < a->n) && (v == a->chaves[i]))
        return caso1(a, i);
    return a;
  }
  
  if((i < a->n) && (v == a->chaves[i])) i++;
  NO *f = a->filhos[i];
  
  if (f->n == t-1){
    if((i < a->n) && (a->filhos[i+1]->n >=t))
        return caso3Adir(a, i, t, v);
    
    if((i > 0) && (a->filhos[i-1]->n >=t))
        return caso3Aesq(a, i, t, v);

    if(i < a->n && a->filhos[i+1]->n == t-1)
        return caso3Bdir(a, i, t, v);

    if((i > 0) && (a->filhos[i-1]->n == t-1))
        return caso3Besq(a, i, t, v);
  } 

  a->filhos[i] = remova(a->filhos[i], v, t);
  return a;
}

NO *retira(NO* a, int k, int t){
  if(!a || !busca(a, k)) return a;
  return remova(a, k, t);
}