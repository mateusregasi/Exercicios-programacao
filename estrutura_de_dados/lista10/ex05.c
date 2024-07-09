#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "TARVB.c"

// função em C que, dada uma árvore qualquer, retire todos os elementos pares da
// árvore original. A função deve ter o seguinte protótipo: 
// TARVB* retira_pares(TARVB* arv);

NO *retira_pares(NO *a, int t){
    if(!a) return a;
    int i;
    for(i=0; i<a->n; i++){
        a->filhos[i] = retira_pares(a->filhos[i], t);
        if(a->chaves[i] % 2 == 0){
            a = remova(a, a->chaves[i], t);
            i = 0;
        }
    }
    a->filhos[i] = retira_pares(a->filhos[i], t);
    if(a->chaves[i] % 2 == 0){
        a = remova(a, a->chaves[i], t);
    }
    return a;
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
  a = retira_pares(a, t);

  printf("\n");
  imprime(a);

  return 0;
}