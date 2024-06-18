#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB.c"

// função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A
// função retorna um se elas são iguais e zero, caso contrário. A função deve
// obedecer ao seguinte protótipo: 
// int igual (TARVB* a1, TARVB* a2);

int igual(NO *a1, NO *a2){
    if((a1 && !a2) || (!a1 && a2)) return 0;
    if(!a1 && !a2) return 1;
    if(a1->folha != a2->folha) return 0; 
    if(a1->folha == a2->folha){
        if(a1->n != a2->n) return 0;
        for(int i=0; i<a1->n; i++)
            if(a1->chaves[i] != a2->chaves[i])
                return 0;
    }
    return 1;
}


int main(void){
  int t = 2;
  NO *a = NULL, *b = NULL;

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

  b = insere(b, 13, t);
  b = insere(b, 1111, t);
  b = insere(b, 311, t);
  b = insere(b, 12, t);
  b = insere(b, 21, t);
  b = insere(b, 12, t);
  b = insere(b, 31, t);
  b = insere(b, 21, t);
  b = insere(b, 2311, t);
  b = insere(b, 13, t);
  b = insere(b, 13, t);
  b = insere(b, 1221, t);
  b = insere(b, 12, t);
  b = insere(b, 11, t);
  b = insere(b, 14, t);
  b = insere(b, 11111, t);

  imprime(a);

  printf("%s\n", (igual(a, b)) ? "sim" : "não");

  return 0;
}