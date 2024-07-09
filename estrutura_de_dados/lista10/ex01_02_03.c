#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB.c"

// sucessor de um elemento na árvore. Se o elemento for o maior da estrutura, sua
// função deve retornar INT_MAX: 
// int suc (TARVB *a, int elem);
// maior elemento da árvore: TARVB* maior(TARVB *a);
//  menor elemento da árvore: TARVB* menor(TARVB *a);
int maior(NO *a){
    if(!a) return 0;
    if(!a->folha)
        return getmaior(a->filhos[a->n]);
    return a->chaves[a->n-1];
}
int menor(NO *a){
    if(!a) return 0;
    if(!a->folha) menor(a->filhos[0]);
    return a->chaves[0];
}
int suc(NO *a, int elem){
    return (getmaior(a) == elem) ? INT_MAX : 0;
}

int main(void){
  int t = 2;
  int n = 2311;
  NO *a = NULL;
  a = insere(a, 13, t);
  a = insere(a, 1111, t);
  a = insere(a, 311, t);
  a = insere(a, 12, t);
  a = insere(a, 21, t);
  a = insere(a, 21, t);
  a = insere(a, 12, t);
  a = insere(a, 31, t);
  a = insere(a, 2311, t);
  a = insere(a, 13, t);
  a = insere(a, 13, t);
  a = insere(a, 1221, t);
  a = insere(a, 12, t);
  a = insere(a, 11, t);
  a = insere(a, 14, t);
  a = insere(a, 11111, t);

  a = remova(a, 31, t);

  imprime(a);

  printf("O número %d é o maior elemento?: %d\n", n, suc(a, n));

  return 0;
}