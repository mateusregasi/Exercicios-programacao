#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.c"
#include ""

// ---------------- Estruturas que vão ser usadas no trabalho ----------------

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

// Nó de um arquivo
typedef struct arvbarqjog{
    int n, folha;
    char prox[50];
} CAB;
typedef struct arqjog{
    CAB *cabecalho;
    NO *chaves,
       *filhos;
} NOA;

// ---------------------------------------------------------------------------

// Auxiliares para lista encadeada
void impjogador(void *jog){
    JO *j = (JO *) jog;
    printf("%d/%d/%s/%s/%s/%d/%d/%s/%s/%s/%d\n",
        j->id, 
        j->camisa, 
        j->posicao, 
        j->nome, 
        j->nascimento, 
        j->n_partidas, 
        j->n_gols, 
        j->pais, 
        j->time, 
        j->pais,
        j->capitao);
}

// Dado um arquivo com a base de dados, transforme em um conjunto de dados de jogadores
void *le_string(char *origem, char *destino, char separador){
    char *p = strchr(origem, separador);
    if(!p) p = origem + strlen(origem) - 1;
    int n = ((int) (p - origem)) / sizeof(char);
    strncpy(destino, origem,  n);
    destino[n] = '\0';
    return p + 1;
}
JO *le_jogador(char *linha){
    char nome[70], data[30], *p, texto[15];

    // Aloca o jogador
    JO *j = (JO *) malloc(sizeof(JO));

    // Lê cada elemento
    sscanf(linha, "%d/%d/%s/",  &j->id, &j->camisa, j->posicao);
    for(int i=0; i<3; i++){
        linha = strchr(linha, '/');
        linha++;
    }
    linha = le_string(linha, nome, '/');
    linha = le_string(linha, data, '/');
    sscanf(linha, "%d/%d/",  &j->n_partidas, &j->n_gols);
    for(int i=0; i<2; i++){
        linha = strchr(linha, '/');
        linha++;
    }
    linha = le_string(linha, j->pais, '/');
    le_string(linha, j->time, '/');

    // Verificando se é capitão
    p = strchr(nome, '(');
    if(p){
        p -= 1;
        *p = '\0';
        j->capitao = 1;
    } else j->capitao = 0;
    strcpy(j->nome, nome);

    // Formata a data
    // 20 December 1998 (aged 25)
    char meses[13][20] = {"January","February","March","April","May","June","July","August","September","October","November","December"},
        mes[10];
    int dia, ano, i;
    sscanf(data, "%d", &dia);
    p = (strchr(data, ' ')) + 1;
    sscanf(p, "%s", mes);
    p = (strchr(p, ' ')) + 1;
    sscanf(p, "%d", &ano);
    for(i=0; strcmp(meses[i], mes); i++);
    sprintf(j->nascimento, "%d-%s%d-%s%d", ano, (i+1 < 10) ? "0" : "", i+1, (dia < 10) ? "0" : "", dia);

    return j;
}
NO *arq2listajogador(char *nomearquivo, int *n){
    char lixo[30], linha[100], *p;
    JO *j;
    int c = 0;
    NO *lista = NULL;

    // Abre o arquivo
    FILE *f = fopen(nomearquivo, "r");

    while(!feof(f)){
    // for(int i=0; i<100; i++){

        // Lê a linha
        fgets(linha, 100, f);

        // Se não for dado, vai para a próxima iteração
        if(!strchr(linha, '/'))
            continue;

        // Faz a leitura do jogador
        j = le_jogador(linha);
        c++;

        // Adiciona na lista
        lista = insini(lista, j);
    }

    // Fecha o arquivo
    fclose(f);
    *n = c;
    return lista;
}

// Pega uma lista encadeada de jogadores e transforma em uma árvore b+ de jogadores
void listajogador2arqbin(NO *l, char *nome){
    while(l){
        insere(l, nome);
        l = l->prox;
    }
}

int main(void){
    int n;
    NO *lista = arq2listajogador("EURO.txt", &n);
    imp(lista, impjogador);

    return 0;
}