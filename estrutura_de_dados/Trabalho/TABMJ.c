#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.c"

// ---------------- Estruturas que vão ser usadas no trabalho ----------------
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
} TJ;
typedef struct arvbmj{
  int nchaves, folha;
  TJ *chave;
  char **filho, *prox;
} TABMJ;
// ---------------------------------------------------------------------------
void impjogador(void *jog);
void *le_string(char *origem, char *destino, char separador);
TJ *le_registro_jogador(TJ *j, FILE *f);
NO *arq2listajogador(char *nome, int *n);
void arq2arvbmarq(char *nome, int t, int *n);
void listajogador2arqbin(NO *l, char *nome);
int verifica_existencia(char *nome);

void leitura(char *origem, TABMJ *destino);
void escrita(TABMJ *origem, char *destino);
TABMJ* cria_no(int t);
void libera_no(TABMJ *a);
char *cria_arquivo(int t, int *contador);
char *busca(char *arq, int id, int t);
char *divisao(char *arq_x, int i, char *arq_y, int t, int *contador);
char *insere_nao_completo(char *arq, TJ *jog, int t, int *contador);
char *insere(char *arq, TJ *jog, int t, int *contador);

// ---------------------------------------------------------------------------

void *le_string(char *origem, char *destino, char separador){
    char *p = strchr(origem, separador);
    if(!p) p = origem + strlen(origem) - 1;
    int n = ((int) (p - origem)) / sizeof(char);
    strncpy(destino, origem,  n);
    destino[n] = '\0';
    return p + 1;
}
TJ *le_registro_jogador(TJ *j, FILE *f){
    char nome[70], data[30], *p, texto[15], l[100], *linha;

    // Lê a linha
    fgets(l, 100, f);
    linha = l;

    // Se não for dado, vai para a próxima iteração
    if(!strchr(linha, '/'))
        return NULL;

    // Lê cada elemento
    sscanf(l, "%d/%d/",  &j->id, &j->camisa);
    for(int i=0; i<2; i++){
        linha = strchr(linha, '/');
        linha++;
    }
    linha = le_string(linha, j->posicao, '/');
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
NO *arq2listajogador(char *nome, int *n){

    // Abre o arquivo
    FILE *f = fopen(nome, "r");
    if(!f) exit(1);

    // Inicializa as variáveis necessárias
    NO *lista = NULL;
    int c = 0;

    while(!feof(f)){

        // Lê o jogador
        TJ *j = (TJ *) malloc(sizeof(TJ));
        if(le_registro_jogador(j, f)){
            lista = insini(lista, j);
            c++;
        } else free(j);
    }

    // Fecha o arquivo
    fclose(f);
    *n = c;
    return lista;
}
void arq2arvbmarq(char *nome, int t, int *n){
    TJ *j = (TJ *) malloc(sizeof(TJ));
    int c = 0;

    // Abre o arquivo
    FILE *f = fopen(nome, "r");

    while(!feof(f)){

        // Faz a leitura do jogador
        if(le_registro_jogador(j, f))

        // Insere no arquivo
        insere(nome, j, t, &c);
    }

    // Fecha o arquivo
    free(j);
    fclose(f);
    *n = c;
}
void listajogador2arqbin(NO *l, char *nome){
    while(l){
        insini(l, nome);
        l = l->prox;
    }
}
void impjogador(void *jog){
    TJ *j = (TJ *) jog;
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
int verifica_existencia(char *nome){
    FILE *f = fopen(nome, "rb");
    int v = (f) ? 1 : 0;
    fclose(f);
    return v;
}
void leitura(char *origem, TABMJ *destino){
    FILE *arq = fopen(origem, "rb");
    if(!arq) exit(1);

    fread(&destino->nchaves, sizeof(int), 1, arq);
    fread(&destino->folha, sizeof(int), 1, arq);

    int i;
    for(i=0; i<destino->nchaves; i++) 
        fread(&destino->chave[i], sizeof(destino->chave[i]), 1, arq);
    for(i=0; i<=destino->nchaves; i++) 
        fread(destino->filho[i], sizeof(char), 30, arq);

    fread(&(destino->prox), sizeof(destino->prox), 1, arq);

    fclose(arq);
}
void escrita(TABMJ *origem, char *destino){
    FILE *arq = fopen(destino, "wb");
    if(!arq) exit(1);

    fwrite(&(origem->nchaves), sizeof(int), 1, arq);
    fwrite(&(origem->folha), sizeof(int), 1, arq);

    int i;
    for(i=0; i<origem->nchaves; i++) 
        fwrite(&origem->chave[i], sizeof(origem->chave[i]), 1, arq);
    for(i=0; i<=origem->nchaves; i++) 
        fwrite(origem->filho[i], sizeof(char), 30, arq);

    fwrite(&(origem->prox), sizeof(origem->prox), 1, arq);

    fclose(arq);
}
TABMJ* cria_no(int t){
    TABMJ *novo = (TABMJ *) malloc(sizeof(TABMJ));
    novo->nchaves = 0;
    novo->folha = 1;
    novo->chave = (TJ *) malloc(sizeof(TJ)*((2*t)-1));
    novo->filho = (char **) malloc(sizeof(char*)*(2*t));
    novo->prox = NULL;
    int i;
    for(i=0; i<(2*t); i++) novo->filho[i] = (char *) malloc(sizeof(char) * 30);

    return novo;
}
void libera_no(TABMJ *a){
    int i;
    for(i=0; i<=a->nchaves; i++) free(a->filho[i]);
    free(a->filho);
    free(a->chave);
    free(a);
}
char *cria_arquivo(int t, int *contador){
    char *arq = (char *) malloc(sizeof(char)*30);
    strcpy(arq, "");
    sprintf(arq, "%d", *contador++);
    strcat(arq, ".dat");

    TABMJ *no = cria_no(t);
    escrita(no, arq);
    libera_no(no);

    return arq;
}
char *busca(char *arq, int id, int t){
    TABMJ *no = cria_no(t);
    leitura(arq, no);
    int i = 0;
    while((i<no->nchaves) && (id>no->chave[i].id)) i++;
    if((i<no->nchaves) && (no->folha) && (no->chave->id == id)){
        libera_no(no);
        return arq;
    };
    if(no->folha){
        libera_no(no);
        return NULL;
    };
    if(no->chave[i].id == id) i++;

    char *resp = busca(no->filho[i], id, t);
    libera_no(no);
    return resp;
}
char *divisao(char *arq_x, int i, char *arq_y, int t, int *contador){
    TABMJ *x = cria_no(t), *y = cria_no(t), *z = cria_no(t);
    char *arq_z = cria_arquivo(t, contador);
    leitura(arq_x, x); leitura(arq_y, y);

    z->folha = y->folha;
    int j;

    if(!y->folha){
        z->nchaves = t-1;
        for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
        for(j=0;j<t;j++){
            z->filho[j] = y->filho[j+t];
            y->filho[j+t] = NULL;
        }
    } else {
        z->nchaves = t;
        for(j=0;j<t;j++) z->chave[j] = y->chave[j+t-1];
        z->prox = y->prox;
        y->prox = arq_z;
    }
    y->nchaves = t-1;
    for(j=x->nchaves;j>=i;j--) x->filho[j+1] = x->filho[j];
    x->filho[i] = arq_z;
    for(j=x->nchaves;j>=i;j--) x->chave[j] = x->chave[j-1];
    x->chave[i-1] = y->chave[t-1];
    x->nchaves++;

    escrita(x, arq_x); escrita(y, arq_y); escrita(z, arq_z);
    libera_no(x); libera_no(y); libera_no(z);
    free(arq_y); free(arq_z);
    return(arq_x);
}
char *insere_nao_completo(char *arq, TJ *jog, int t, int *contador){
    TABMJ *no = cria_no(t);
    leitura(arq, no);

    int i = no->nchaves-1;
    if(no->folha){
        while((i>=0)&&(jog->id<no->chave[i].id)){
            no->chave[i+1] = no->chave[i];
            i--;
        }
        no->chave[i+1] = *jog;
        no->nchaves++;
        escrita(no, arq);
        libera_no(no);
        return(arq);
    }
    while((i>=0)&&(jog->id<no->chave[i].id)) i--;
    i++;
    TABMJ *no_filho = cria_no(t);
    leitura(no->filho[i], no_filho);
    int nch = no_filho->nchaves;
    libera_no(no_filho);
    if(nch == ((2*t)-1)){
        escrita(no, arq);
        char *arq_filho = (char *) malloc(sizeof(char)*30);
        strcpy(arq_filho, no->filho[i]);
        arq = divisao(arq, (i+1), arq_filho, t, contador);
        leitura(arq, no);
        if(jog->id > no->chave[i].id) i++;
    }
    no->filho[i] = insere_nao_completo(no->filho[i], jog, t, contador);
    escrita(no, arq);
    libera_no(no);
    return(arq);
}
char *insere(char *arq, TJ *jog, int t, int *contador){
    if(busca(arq, jog->id, t)) return arq;

    TABMJ *no = cria_no(t);
    leitura(arq, no);

    if(no->nchaves == (2*t)-1){
        char *novo_arq = cria_arquivo(t, contador);
        TABMJ *novo_no = cria_no(t);
        leitura(novo_arq, novo_no);
        novo_no->folha = 0;
        novo_no->nchaves = 0;
        novo_no->filho[0] = arq;
        escrita(novo_no, novo_arq);
        libera_no(novo_no);
        libera_no(no);

        novo_arq = divisao(novo_arq, 1, arq, t, contador);
        novo_arq = insere_nao_completo(novo_arq, jog, t, contador);
        free(arq);
        return novo_arq;
    }
    libera_no(no);
    arq = insere_nao_completo(arq, jog, t, contador);
    return arq;
}
