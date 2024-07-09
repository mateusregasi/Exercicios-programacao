#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TABMJ.c"

void func(void *v){
    TJ *j = (TJ *) v;
    printf("%s - %d\n", j->nome, j->idade);
}

int main(void){

    // -=-=-=-=-= CRIANDO A ÁRVORE -=-=-=-=-=
    int t = 2, n;
    char *arquivo_leitura = "EURO.txt";
    char *raiz = arq2arvbmarq(arquivo_leitura, "arv", t, &n);
    // char *raiz = (char *) malloc(sizeof(char) * 30);
    // strcpy(raiz, "114.dat");
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    // -=-=-=- APRESENTANDO A ÁRVORE =-=-=-=-
    printf("Imprimindo a árvore:\n");
    imprime(raiz, t);
    // printf("Quantidade de elementos: %d\n");
    // printf("Quantidade de nós: %d\n");
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    // -=-=-=-=-=-=- QUESTÕES -=-=-=-=-=-=-=-

    // Questão 1)
//     printf("Retorno do jogador mais novo e mais velho da competição, ilustrando essas mesmas informações por seleções e por posições;\n");

//     printf("\nTodos os jogadores\n");
//     TLSE *l = jogadores_mais_novos_e_mais_velhos(raiz, t);
// printf("Jogador mais novo: %s\nJogador mais velhor: %s\n", 
//     ((TJ *) l->dado)->nome,
//     ((TJ *) l->prox->dado)->nome);
//     TLSE_libera(l);
//     printf("\n");

//     printf("\nTodos por seleção");
//     char *selecao = (char *) malloc(sizeof(char) * 30);
//     strcpy(selecao, "Germany");
//     l = jogadores_mais_novos_e_mais_velhos_por_selecao(raiz, t, selecao);
// printf("Jogador mais novo: %s\nJogador mais velhor: %s\n", 
//     ((TJ *) l->dado)->nome,
//     ((TJ *) l->prox->dado)->nome);
//     TLSE_libera(l);
//     printf("\n");

    // Questão 2)
    
    // Questão 3)
    
    // Questão 4)
    
    // Questão 5)
    
    // Questão 6)
    
    // Questão 7)

    // Questão 8)

    // Questão 9)

    // Questão 10)


    // Questão 11)
    // Questão 12)
    // Questão 13)
    // Questão 14)
    // raiz = remove_capitao(raiz, t);
    // imprime(raiz, t);

    // Questão 15)
    raiz = remove_jogadores_pela_idade(raiz, t, 20);



    // Questão 16)
    // Questão 17)
    // Questão 18)
    // Questão 19)

    // Questão 20)
    // int *ns = (int *) malloc(sizeof(int) * 3);
    // ns[0] = 1; ns[1] = 2; ns[3] = 50;
    // TLSE *l = TLSE_insini(NULL, &ns[0]);
    // l = TLSE_insini(l, &ns[1]);
    // l = TLSE_insini(l, &ns[2]);
    // raiz = remocao_por_chaves(raiz, t, l);
    
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    
    printf("Raiz: %s\n", raiz);

    return 0;
}
