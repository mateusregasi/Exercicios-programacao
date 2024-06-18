#include <stdio.h>
#include <stdlib.h>

typedef struct arvoreb{
  int n, folha, *chaves;
  struct arvoreb **filhos;
} NO;

NO *cria(int t){
  NO* n = (NO *) malloc(sizeof(NO));
  n->n = 0;
  n->chaves = (int*) malloc(sizeof(int*) * ((t*2)-1));
  n->folha = 1;
  n->filhos = (NO**) malloc(sizeof(NO*) * t*2);
  for(int i=0; i < (t*2); i++) 
    n->filhos[i] = NULL;
  return n;
}
NO *libera(NO *a){
  if(a){
    if(!a->folha){
      int i;
      for(i=0; i<=a->n; i++) 
        libera(a->filhos[i]);
    }
    free(a->chaves);
    free(a->filhos);
    free(a);
    return NULL;
  }
}

void imp_rec(NO *a, int tab){
  if(a){
    int i,j;
    for(i=0; i<=a->n-1; i++){
      imp_rec(a->filhos[i], tab+1);
      for(j=0; j<=tab; j++) printf("\t");
      printf("%d\n", a->chaves[i]);
    }
    imp_rec(a->filhos[i], tab+1);
  }
}

void imprime(NO *a){
  imp_rec(a, 0);
}

NO *busca(NO *x, int v){
  if(!x) return NULL;
  int i = 0;
  while((i<x->n) && (v > x->chaves[i])) i++;
  if((i<x->n) && (v == x->chaves[i])) return x;
  if(x->folha) return NULL;
  return busca(x->filhos[i], v);
}

NO *inicializa(){
  return NULL;
}

NO *divida(NO *x, int i, NO *y, int t){
  NO *n = cria(t);
  n->n = t-1;
  n->folha = y->folha;
  int j;
  for(j=0; j<t-1; j++) 
    n->chaves[j] = y->chaves[j+t];
  if(!y->folha){
    for(j=0; j<t; j++){
      n->filhos[j] = y->filhos[j+t];
      y->filhos[j+t] = NULL;
    }
  }
  y->n = t-1;
  for(j=x->n; j>=i; j--) 
    x->filhos[j+1] = x->filhos[j];
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
    while((i>=0) && (v<x->chaves[i])){
      x->chaves[i+1] = x->chaves[i];
      i--;
    }
    x->chaves[i+1] = v;
    x->n++;
    return x;
  }
  while((i>=0) && (v<x->chaves[i])) i--;
  i++;
  if(x->filhos[i]->n == ((2*t)-1)){
    x = divida(x, (i+1), x->filhos[i], t);
    if(v>x->chaves[i]) i++;
  }
  x->filhos[i] = insere_incompleto(x->filhos[i], v, t);
  return x;
}


NO *insere(NO *a, int v, int t){
  if(busca(a, v)) return a;
  if(!a){
    a = cria(t);
    a->chaves[0] = v;
    a->n = 1;
    return a;
  }
  if(a->n == (2*t)-1){
    NO *n = cria(t);
    n->n = 0;
    n->folha = 0;
    n->filhos[0] = a;
    n = divida(n, 1, a, t);
    n = insere_incompleto(n, v, t);
    return n;
  }
  a = insere_incompleto(a, v, t);
  return a;
}


NO *libera_remocao(NO *a){
  free(a->chaves);
  free(a->filhos);
  free(a);
  return NULL;
}

NO* remova(NO* a, int v, int t);

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

NO *caso2A(NO *a, int i, int t){
  NO *f = a->filhos[i];
  while(!f->folha) 
    f = f->filhos[f->n];
  int temp = f->chaves[f->n-1];
  a->filhos[i] = remova(a->filhos[i], temp, t); 
  a->chaves[i] = temp;
  return a;
}

NO *caso2B(NO *a, int i, int t){
  NO *f = a->filhos[i+1];
  while(!f->folha) 
    f = f->filhos[0];
  int temp = f->chaves[0];
  f = remova(a->filhos[i+1], temp, t);
  a->chaves[i] = temp;
  return a;
}

NO *caso2C(NO *a, int i, int t, int v){
  NO *f = a->filhos[i];
  NO *fp = a->filhos[i+1];
  f->chaves[f->n] = v;
  int j;
  for(j=0; j<t-1; j++)                
    f->chaves[t+j] = fp->chaves[j];
  for(j=0; j<t; j++){                
    f->filhos[t+j] = fp->filhos[j];
    fp->filhos[j] = NULL; 
  }
  f->n = 2*t-1;
  for(j=i; j < a->n-1; j++)  
    a->chaves[j] = a->chaves[j+1];
  for(j=i+1; j < a->n; j++)  
    a->filhos[j] = a->filhos[j+1]; 
  a->filhos[j] = NULL;
  libera_remocao(fp);
  a->n--;
  if(!a->n){ 
    NO *temp = a;
    a = a->filhos[0];
    temp->filhos[0] = NULL;
    libera_remocao(temp);
    a = remova(a, v, t);
  }
  else a->filhos[i] = remova(a->filhos[i], v, t);
  return a;   
}

NO *caso3Adir(NO *a, int i, int t, int v){
  NO *f = a->filhos[i], *fp = a->filhos[i+1];
  f->chaves[t-1] = a->chaves[i];   
  f->n++;
  a->chaves[i] = fp->chaves[0];    
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
  NO *f = a->filhos[i], *fp = a->filhos[i+1];
  fp = a->filhos[i-1];
  int j;
  for(j = f->n; j>0; j--)             
    f->chaves[j] = f->chaves[j-1];
  for(j = f->n+1; j>0; j--)             
    f->filhos[j] = f->filhos[j-1];
  f->chaves[0] = a->chaves[i-1];              
  f->n++;
  a->chaves[i-1] = fp->chaves[fp->n-1];  
  f->filhos[0] = fp->filhos[fp->n];        
  fp->n--;
  a->filhos[i] = remova(f, v, t);
  return a;
}

NO *caso3Bdir(NO *a, int i, int t, int v){
  NO *f = a->filhos[i], *fp = a->filhos[i+1];
  f->chaves[t-1] = a->chaves[i];    
  f->n++;
  int j;
  for(j=0; j < t-1; j++){
    f->chaves[t+j] = fp->chaves[j];    
    f->n++;
  }
  if(!f->folha){
    for(j=0; j<t; j++){
      f->filhos[t+j] = fp->filhos[j];
      fp->filhos[j] = NULL; 
    }
  }
  libera(fp);
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

NO *caso3Besq(NO *a, int i, int t, int v){
  NO *f = a->filhos[i], *fa = a->filhos[i-1];
  if(i == a->n)
    fa->chaves[t-1] = a->chaves[i-1];
  else
    fa->chaves[t-1] = a->chaves[i]; 
  fa->n++;
  int j;
  for(j=0; j < t-1; j++){
    fa->chaves[t+j] = f->chaves[j]; 
    fa->n++;
  }
  if(!fa->folha){
    for(j=0; j<t; j++){
      fa->filhos[t+j] = f->filhos[j];
      f->filhos[j] = NULL;
    }
  }
  libera(f);
  a->filhos[a->n] = NULL;
  a->n--;
  if(!a->n){
    NO *temp = a;
    a = a->filhos[0];
    temp->filhos[0] = NULL;
    libera(temp);
  }
  else a->filhos[i-1] = fa;
  a = remova(a, v, t);
  return a;
}

NO* remova(NO* a, int v, int t){
  if(!a) return a;

  int i = 0;
  while(i<a->n && a->chaves[i] < v){
    i++;
  }
  if(i < a->n && v == a->chaves[i]){
    if(a->folha)
      return caso1(a, i);
    if(!a->folha){
      if(a->filhos[i]->n >= t)
        return caso2A(a, i, t);
      if(a->filhos[i+1]->n >= t)
        return caso2B(a, i, t);
      if(a->filhos[i+1]->n == t-1 && a->filhos[i]->n == t-1)
        return caso2C(a, i, t, v);
    }
  }

  if(!a->folha){
    NO *f = a->filhos[i];
    if(f->n == t-1){
      if((i < a->n) && (a->filhos[i+1]->n >= t))
        return caso3Adir(a, i, t, v);
      if((i > 0) && (a->filhos[i-1]->n >= t))
        return caso3Aesq(a, i, t, v);
        if(i < a->n && a->filhos[i+1]->n == t-1)
          return caso3Bdir(a, i, t, v);
        if((i > 0) && (a->filhos[i-1]->n == t-1))
          return caso3Besq(a, i, t, v);
    }  
  }
  a->filhos[i] = remova(a->filhos[i], v, t);
  return a;
}


NO* retira(NO* a, int v, int t){
  if(!a || !busca(a, v)) return a;
  return remova(a, v, t);
}