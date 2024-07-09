#include <stdio.h>
#include <stdlib.h>



int esq(int ind){
  return (ind * 2 + 1);
}

int dir(int ind){
  return (ind * 2 + 2);
}

int pai(int ind){
  if(ind > 0) return (ind - 1)/2;
  return -1;
}

void corrige_no(int *vet, int n, int ind){
  int e = esq(ind), d = dir(ind), maior = ind;
  if(e < n && vet[e] > vet[ind]) maior = e;
  if(d < n && vet[d] > vet[maior]) maior = d;
  if(maior != ind){
    int temp = vet[ind];
    vet[ind] = vet[maior];
    vet[maior] = temp;
    corrige_no(vet, n, maior);
  }
}

void corrige_arvore(int *v, int n){
  int i, ultimo_pai = pai(n - 1);
  for(i = ultimo_pai; i >= 0; i--)
    corrige_no(v, n, i);
}

void heapsort(int *v, int n){
  int i;
  corrige_arvore(v, n);
  for(i = n - 1; i >= 1; i--){
    int temp = v[i];
    v[i] = v[0];
    v[0] = temp;
    corrige_no(v, i, 0);
  }
}