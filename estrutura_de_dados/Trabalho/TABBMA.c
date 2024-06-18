#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.c"

// Estruturas que vão ser usadas no trabalho

// Jogador
typedef struct jogador{
    int id,
        camisa,
        capitao;
    char posicao[3],
         nome[51],
         nascimento[11];
    int n_partidas,
        n_gols;
    char pais[30],
         time[30];
} JO;

// // Nó de um arquivo
typedef struct arvbarqjog{
    int n, folha;
    char prox[50];
} CAB;
typedef struct arqjog{
    CAB *cabecalho;
    NO *chaves,
       *filhos;
} NOA;

// Dado um arquivo com a base de dados, transforme em um conjunto de dados de jogadores
NOA *arq2listajogador(char *nome, int *n){
    char nomearquivo[70],
         data[30],
         pais[30];
    char linha[100], p[30], *pc, meses[13][20] = {"January","February","March","April","May","June","July","August","September","October","November","December"}, mes[15];

    int c = 0, dia;
    NO *lista = NULL;

    // Abre o arquivo
    FILE *f = fopen(nomearquivo, "r");

    while(1){

        // Lê a linha
        fgets(linha, 100, f);
        printf("%s", linha);

        // Verifica se é um país
        sscanf(linha, "%30s[^\n]", p);
        if(!strchr(p, '/')){
            strcpy(pais, p);
            continue;
        }

        // Aloca espaço para o jogador
        struct jogador *j = (JO *) malloc(sizeof(NO));
        c++;

        // Lê cada elemento
        scanf("%d/%d/%3s/%70s/%30s/%d/%d/%30s/%30s",
        j->id, j->camisa, j->posicao, nome, data, j->n_partidas, j->n_gols, j->pais, j->time);

        // Verificando se é capitão
        pc = strchr(nome, '(');
        if(pc){
            *pc = '\0';
            j->capitao = 1;
        } else j->capitao = 0;
        strncpy(j->nome, nome, 51);

        // Convertendo a data
        // 15 December 1996 (aged 27)
        j->nascimento[4] = '/';
        j->nascimento[7] = '/';
        j->nascimento[8] = data[0];
        j->nascimento[9] = data[1];
        pc = &data[3];
        sscanf(pc, "%s", mes);
        int i;
        for(i=0; i<12; i++)
            if(!strcmp(mes, meses[i]));
        sprintf(p, "%d", i+1);
        strncpy(&j->nascimento[5], p, 2);
        pc += strlen(mes) + 1;
        strncpy(j->nascimento, pc, 4);

        // Adiciona na lista
        lista = insini(lista, j);
    }

    // Fecha o arquivo
    fclose(f);
    *n = c;
    return lista;
}

void impjogador(void *e){
    JO *j = (JO *) e;
    printf("%d/%d/%s/%s/%s/%d/%d/%s/%s/%s\n",
        j->id, j->camisa, j->posicao, j->nome, j->nascimento, j->n_partidas, j->n_gols, j->pais, j->time, j->pais);
}

int main(void){
    int n;
    NO *lista = arq2listajogador("EURO.txt", &n);
    imp(lista, impjogador);

    return 0;
}