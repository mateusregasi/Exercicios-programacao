#include <stdio.h>
#include <stdlib.h>

// Considere n cidades numerdas de 0 a n-1 que estão interligadas por uma série de entradas de mão única. As ligações entre as cidade são representadas pelos elementos de uma matriz quadrada Lij cujos elemento I assumem o valor 1 ou 0, conforme exista ou não estrada direta que saia da cidade i e chegue na cidade j. Assim, os elementos da linha i indicam as estradas que saem da cidade i, e os elementos da coluna j indicam as estradas que chegam à cidade j. Por convenção Iij = 1.
// (a) Dado k, determinar quantas estradas saem e quantas chegam à cidade k.
// (b) A qual das cidades chega o maior número de estradas?
// (c) Dado k, verificar se todas as ligações diretas entre a cidade k e outras são de mão dupla.
// (d) Relacionar as cidades que possuem saídas diretas para a cidade k
// (e) Relacionar, se existirem:
//      (i) As cidades isoladas, isto é. as que não tem ligação com nenhuma outra;
//      (ii) As cidades das quais não há saída, apesar de haver entrada;
//      (iii) As cidades das quais há saída sem haver entrada.
// (d) Dada uma sequência de m inteiros cujos valores estão entre 0 e n-1, verificar é pe possível realizar o roteiro correspondente. No exemplo dado, o roteiro representado pela sequência (m=5) 2 3 2 1 0 é impossível.
// (g) Dados k e p, determinar se é possível ir da cidade p pelas estradas existentes. Você consegue encontrar o menor caminho entre as cidades?
// Matriz de exemplo: mat = {{0,1,1,1}, {0,1,0,0}, {1,0,1,1}, {0,0,1,1}}

// Funções do problema
int cidades_chegam_em_i(void *matriz, int n, int i);                    // (a)
int cidades_saem_de_i(void *matriz, int n, int i);                      // (a)
int cidade_mais_estradas_entrada(void *matriz, int n);                  // (b)
int ver_todas_cidade_mao_dupla(void *matriz, int n, int i);             // (c)
int *cidades_saida_direta_com_i(void *matriz, int n, int i, int *c);    // (d)
int *cidades_isoladas(void *matriz, int n, int *c);                     // (e)(i)
int *cidades_entrada_somente(void *matriz, int n, int *c);              // (e)(ii)
int *cidades_saida_somente(void *matriz, int n);                        // (e)(iii)
int ver_roteiro(int *rot, int m, void *matriz, int n);                  // (d)
int eh_possivel_ir_de_i_a_j(void *matriz, int n, int i, int j);         // (g)

void printa_vetor(int *vet, int n){
    for(int i=0; i<n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}
void printa_matriz(void *matriz, int n){
    int (*mat)[n] = (int (*)[n]) matriz;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }        
}

int main(void){

    // Matriz de exemplo
    int mat[4][4] = {{0,1,1,1}, {0,1,0,0}, {1,0,1,1}, {0,0,1,1}}, n;

    // Questões
    printf("Quantas cidades chegam na cidade 1?: %d\n", cidades_chegam_em_i(mat, 4, 1));
    printf("Quantas cidades saem da cidade 1?: %d\n", cidades_saem_de_i(mat, 4, 1));
    printf("A cidade com mais entradas é?: %d\n", cidade_mais_estradas_entrada(mat, 4));
    printf("Todas as cidades que vão para 1 são de mão dupla: %s\n", ver_todas_cidade_mao_dupla(mat, 4, 1) ? "sim" : "não");
    printf("Cidade com saída em 1?: ");
    cidades_saida_direta_com_i(mat, 4, 1, &n);
    printa_vetor(cidades_saida_direta_com_i(mat, 4, 1, &n), n);
    printf("Cidade isoladas?: ");
    cidades_isoladas(mat, 4, &n);
    printa_vetor(cidades_isoladas(mat, 4, &n), n);
    printf("Cidade sem saída?: ");
    cidades_entrada_somente(mat, 4, &n);
    printa_vetor(cidades_entrada_somente(mat, 4, &n), n);


    return 0;
}

// Funções do problema
int cidades_chegam_em_i(void *matriz, int n, int i){                  // (a)
    int (*mat)[n] = (int (*)[n]) matriz;

    int soma = 0;
    for(int j=0; j<n; j++) 
        soma += mat[j][i];

    return soma;
}
int cidades_saem_de_i(void *matriz, int n, int i){                   // (a)
    int (*mat)[n] = (int (*)[n]) matriz;

    int soma = 0;
    for(int j=0; j<n; j++) 
        soma += mat[i][j];
    
    return soma;
}
int cidade_mais_estradas_entrada(void *matriz, int n){                  // (b)
    int (*mat)[n] = (int (*)[n]) matriz;

    // Vai retornar sempre a primeira ocorrência da maior
    int soma, soma_maior = 0, maior = 0;
    for(int i=0; i<n; i++){
        soma = 0;
        for(int j=0; j<n; j++)
            soma += mat[j][i];
        if(soma > soma_maior){
            maior = i;
            soma_maior = soma;
        }
    }

    return maior;
}
int ver_todas_cidade_mao_dupla(void *matriz, int n, int i){             // (c)
    int (*mat)[n] = (int (*)[n]) matriz;

     for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if((mat[i][j] && !mat[j][i]) || (!mat[i][j] && mat[j][i])) return 0;

    return 1;
}
int *cidades_saida_direta_com_i(void *matriz, int n, int i, int *c){            // (d)
    int (*mat)[n] = (int (*)[n]) matriz;

    // Conta as cidades
    (*c) = 0;
    for(int j=0; j<n; j++)
        if(mat[j][i]) (*c)++;
        
    // Cria o vetor e adiciona
    int *vet = (int *) malloc(sizeof(int) * (*c));
    (*c) = 0;
    for(int j=0; j<n; j++)
        if(mat[j][i]){
            vet[(*c)] = j;
            (*c)++;
        }
    
    return vet;
}
int *cidades_isoladas(void *matriz, int n, int *c){                             // (e)(i)
    int (*mat)[n] = (int (*)[n]) matriz;

    // Conta as cidades isoladas
    (*c) = n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(mat[i][j]){
                (*c)--;
                break;
            };
        }
    }
        
    // Cria o vetor e adiciona
    int *vet = (int *) malloc(sizeof(int) * (*c));
    (*c) = 0;
    for(int i=0; i<n; i++){
        int cont = 0;
        for(int j=0; j<n; j++){
            if(mat[i][j]){
                cont++;
                break;
            };
        }
        if(!cont){
            vet[(*c)] = i;
            (*c)++;
        }
    }
    
    return vet;
}
int *cidades_entrada_somente(void *matriz, int n, int *c){                      // (e)(ii)
    int (*mat)[n] = (int (*)[n]) matriz;

    // Conta as cidades isoladas
    (*c) = n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(mat[i][j]){
                (*c)--;
                break;
            };
        }
    }
        
    // Cria o vetor e adiciona
    int *vet = (int *) malloc(sizeof(int) * (*c));
    (*c) = 0;
    for(int i=0; i<n; i++){
        int cont = 0;
        for(int j=0; j<n; j++){
            if(mat[i][j]){
                cont--;
                break;
            };
        }
        if(!cont){
            vet[(*c)] = i;
            (*c)++;
        }
    }
    
    return vet;
}
int *cidades_saida_somente(void *matriz, int n){                        // (e)(iii)
    int (*mat)[n] = (int (*)[n]) matriz;
}
int ver_roteiro(int *rot, int m, void *matriz, int n){                  // (d)
    int (*mat)[n] = (int (*)[n]) matriz;
}
int eh_possivel_ir_de_i_a_j(void *matriz, int n, int i, int j){         // (g)
    int (*mat)[n] = (int (*)[n]) matriz;
}