#include "TABB.c"
#include "TLSE.c"

int TLSE_conta(TLSE *l){
    if(!l) return 0;
    int c = 0;
    while(l){
        c++;
        l = l->prox;
    }
    return c;
}
// Explicando esse código: 
// Criei uma lista com comportamento de conjunto que adicionava
// O nível de cada folha dentro de uma lista sem que o mesmo nível
// Se repetisse (a senhora tinha tirado 1 ponto aqui, dá pra reconsiderar hein hein hein)
TLSE *get_folhas_nivel(TABB *a, TLSE *l, int i){
    if(a){
        l = get_folhas_nivel(a->esq, l, i+1);

        // Se achar uma folha
        if((!a->esq) && (!a->dir)){

            // Se o nível já não estiver na lista adiciona
            if(!TLSE_busca(l, i))
                l = TLSE_insere(l, i);
        }
        l = get_folhas_nivel(a->dir, l, i+1);
    }
    return l;
}
int aux_rec_teste(TABB *a, int i){
    if(!a) return 1;

    // Primeiro caso
    // A única alteração no código foi aqui, antes tava assim:
    // if((i % 3 == 0) && ((!a->esq) || (!a->dir)));
    if((i % 3 == 0) && ((!a->esq && a->dir) || (a->esq && !a->dir)))
        return 0;

    // Segundo caso
    if((i % 3 == 1) && (!a->esq))
        return 0;

    // Terceiro caso
    if((i % 3 == 2) && (!a->dir))
        return 0;

    // Caso ele passe por todos os testes, passa para o próximo
    int v = aux_rec_teste(a->esq, i+1);
    if(!v) return 0;
    return aux_rec_teste(a->dir, i+1);
}
int teste(TABB *a){
    if(!a) return 0;
    printf("");

    // Verifica se todas as folhas estão na mesma altura
    TLSE *f = get_folhas_nivel(a, NULL, 0);
    int v = (TLSE_conta(f) == 1) ? 1 : 0;
    TLSE_libera(f);

    // Se não forem retorna falso
    if(!v) return 0;

    // Se sim retorna o algoritmo que verifica as condições
    return aux_rec_teste(a, 0);
}

int main(void){
  int n;
  TABB *resp = NULL;
  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    resp = TABB_insere(resp, n);
  }
  TABB_imp_ident(resp);
  printf("Segue o padrao? %d\n", teste(resp));
  TABB_libera(resp);
  return 0;
}