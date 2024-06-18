#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB.c"


// quantidade de nós internos: int ni(TARVB *a);
// quantidade de nós folha: int nf(TARVB *a);
int ni(NO *a){
    if(!a) return 0;
    int c = 1;
    for(int i=0; i<=a->n; i++)
        c += ni(a->filhos[i]);
    return c;
}
int nf(NO *a){
    if(!a) return 0;
    if(a->folha) return 1;
    int c = 0;
    for(int i=0; i<=a->n; i++)
        c += nf(a->filhos[i]);
    return c;
}

int main(void){
  int t = 2;
  int n = 2311;
  NO *a = NULL;

  a = insere(a, 13, t);
  a = insere(a, 1112, t);
  a = insere(a, 311, t);
  a = insere(a, 12, t);
  a = insere(a, 21, t);
  a = insere(a, 22, t);
  a = insere(a, 12, t);
  a = insere(a, 31, t);
  a = insere(a, 2311, t);
  a = insere(a, 13, t);
  a = insere(a, 16, t);
  a = insere(a, 1221, t);
  a = insere(a, 12, t);
  a = insere(a, 11, t);
  a = insere(a, 14, t);
  a = insere(a, 11111, t);

  imprime(a);
  printf("%d %d\n", ni(a), nf(a));

  return 0;
}