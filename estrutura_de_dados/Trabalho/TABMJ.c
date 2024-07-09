#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lista_simplesmente_encadeada.c"
// #include "TABELAS_antiga.c"

// Jogador
typedef struct jogador{
    int id,
        camisa,
        capitao,
        idade;
    char posicao[3],
         nome[51],
         nascimento[11];
    int n_partidas,
        n_gols;
    char pais_atual[30],
         pais_origem[30],
         time[30];
} TJ;

typedef struct arvbmj{
  int nchaves, folha;
  TJ *chave;
  char **filho, *prox;
}TABMJ;

void imprime_jog(TJ *j){
    printf("id: %d\n", j->id);
    printf("camisa: %d\n", j->camisa);
    printf("capitao: %d\n", j->capitao);
    printf("n_partidas: %d\n", j->n_partidas);
    printf("n_gols: %d\n", j->n_gols);

    printf("posicao: %s", j->posicao);
    printf("\nnome: %s", j->nome);
    printf("\nnascimento: %s", j->nascimento);
    printf("\npais atual: %s", j->pais_atual);
    printf("\ntime: %s", j->time);
    printf("\n\n");
}

void imprime_no(TABMJ *a){
    printf("nchaves: %d\n", a->nchaves);
    printf("folha: %d\n", a->folha);
    printf("chaves: \n");
    int i;
    for(i=0; i<a->nchaves; i++) imprime_jog(&a->chave[i]);
    printf("filhos: \n");
    for(i=0; i<=a->nchaves; i++) printf("%s\n", a->filho[i]);
    printf("prox: %s\n", a->prox);
    printf("\n\n");
}
// Criei essa função para checar a existência de um arquivo <- Regasi (03/07/24)
int verifica_existencia(char *nome){
    FILE *f = fopen(nome, "rb");
    int v;
    if(f){
        fclose(f);
        return 0;
    } else return 1;
}
// Fim da adição
void leitura(char *origem, TABMJ *destino){
    FILE *arq = fopen(origem, "rb");
    // Alterei pra quando tentar ler um arquivo que não existe não quebrar  <- Regasi (03/07/24)
    if(!arq) return;
    // if(!arq) exit(1);
    // Fim da alteração

    fread(&destino->nchaves, sizeof(int), 1, arq);
    fread(&destino->folha, sizeof(int), 1, arq);

    int i;
    for(i=0; i<destino->nchaves; i++) fread(&destino->chave[i], sizeof(destino->chave[i]), 1, arq);
    for(i=0; i<=destino->nchaves; i++) fread(destino->filho[i], sizeof(char), 30, arq);

    fread(&(destino->prox), sizeof(destino->prox), 1, arq);

    fclose(arq);
}

void escrita(TABMJ *origem, char *destino){
    FILE *arq = fopen(destino, "wb");
    if(!arq) exit(1);

    fwrite(&(origem->nchaves), sizeof(int), 1, arq);
    fwrite(&(origem->folha), sizeof(int), 1, arq);

    int i;
    for(i=0; i<origem->nchaves; i++) fwrite(&origem->chave[i], sizeof(origem->chave[i]), 1, arq);
    for(i=0; i<=origem->nchaves; i++) fwrite(origem->filho[i], sizeof(char), 30, arq);

    fwrite(&(origem->prox), sizeof(origem->prox), 1, arq);

    fclose(arq);
}

TABMJ* cria_no(int t){
    TABMJ *novo = (TABMJ *) malloc(sizeof(TABMJ));
    novo->nchaves = 0;
    novo->folha = 1;
    novo->chave = (TJ *) malloc(sizeof(TJ)*((2*t)-1));
    novo->filho = (char **) malloc(sizeof(char*)*(2*t));
    novo->prox = malloc(sizeof(char)*30);
    strcpy(novo->prox, "");
    int i;
    for(i=0; i<=(2*t); i++){
        novo->filho[i] = (char *) malloc(sizeof(char)*30);
        strcpy(novo->filho[i], "");
    }

    return novo;
}

void libera_no(TABMJ *a){
    int i;
    for(i=0; i<=a->nchaves; i++) free(a->filho[i]);
    free(a->filho);
    free(a->chave);
    free(a);
}

void imprime_arq(char *a, int t){
    printf("arquivo: %s\n", a);
    TABMJ *no = cria_no(t);
    leitura(a, no);
    imprime_no(no);
    libera_no(no);
}

void imprime_filhos(char *a, int t){
    TABMJ *no = cria_no(t);
    leitura(a, no);
    int i;
    for(i=0;i<=no->nchaves;i++){
        printf("FILHO %d: %s\n", i, no->filho[i]);
        imprime_arq(no->filho[i], t);
    }
    libera_no(no);
}

char *cria_arquivo(int t, int *contador){
    char *arq = (char *) malloc(sizeof(char)*30);
    sprintf(arq, "%d", (*contador)++);
    strcat(arq, ".dat");

    TABMJ *no = cria_no(t);
    escrita(no, arq);
    libera_no(no);

    return arq;
}

char *busca(char *arq, int id, int t){
    // Adicionei essa linha para não fazer leitura caso não exista o arquivo - Regasi (03/07/24)
    if(verifica_existencia(arq)) return NULL;
    // Fim da adição
    TABMJ *no = cria_no(t);
    leitura(arq, no);
    int i = 0;
    while((i<no->nchaves) && (id>no->chave[i].id)) i++;
    if((i<no->nchaves) && (no->folha) && (no->chave[i].id == id)){
        libera_no(no);
        char *resp = (char *) malloc(sizeof(char)*30);
        strcpy(resp, arq);
        return resp;
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
        for(j=0;j<t-1;j++) z->chave[j] = y->chave[t+j];
        for(j=0;j<t;j++){
            strcpy(z->filho[j], y->filho[t+j]);
            strcpy(y->filho[t+j], "");
        }
    } else {
        z->nchaves = t;
        for(j=0;j<t;j++) z->chave[j] = y->chave[j+t-1];
        strcpy(z->prox, y->prox);
        strcpy(y->prox, arq_z);
    }
    y->nchaves = t-1;
    for(j=x->nchaves;j>=i;j--){
        x->chave[j] = x->chave[j-1];
        strcpy(x->filho[j+1], x->filho[j]);
    }
    strcpy(x->filho[i], arq_z);
    x->chave[i-1] = y->chave[t-1];
    x->nchaves++;

    escrita(z, arq_z);
    escrita(y, arq_y);
    escrita(x, arq_x);
    libera_no(z);
    libera_no(y);
    libera_no(x);
    free(arq_z);
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
        free(arq_filho);
        leitura(arq, no);
        if(jog->id > no->chave[i].id) i++;
    }
    char *temp = insere_nao_completo(no->filho[i], jog, t, contador);
    strcpy(no->filho[i], temp);
    escrita(no, arq);
    libera_no(no);
    return(arq);
}

char *insere(char *arq, TJ *jog, int t, int *contador){
    // A função de busca tá dando erro quando se busca um arquivo que não existe
    char *b = busca(arq, jog->id, t);
    if(b){
        free(b);
        return arq;
    }

    TABMJ *no = cria_no(t);
    leitura(arq, no);

    if(no->nchaves == (2*t)-1){
        char *novo_arq = cria_arquivo(t, contador);
        TABMJ *novo_no = cria_no(t);
        novo_no->folha = 0;
        novo_no->nchaves = 0;
        strcpy(novo_no->filho[0], arq);
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

char *remover(char *arq, int id, int t){
    TABMJ *no = cria_no(t);
    leitura(arq, no);
    int i, j;
    for(i = 0;(i < no->nchaves) && (no->chave[i].id < id); i++);
    
    if(no->folha){ 
        if((i < no->nchaves) && (no->chave[i].id == id)){
            for(j=i; j<no->nchaves-1; j++) no->chave[j] = no->chave[j+1];
            no->nchaves--;
            escrita(no, arq);
        }
        libera_no(no);
        return arq;
    };

    if((i < no->nchaves) && (no->chave[i].id == id)) i++;
    TABMJ *y = cria_no(t);
    leitura(no->filho[i], y);
    if(y->nchaves >= t){
        no->filho[i] = remover(no->filho[i], id, t);
        escrita(no, arq);
        return arq;
    }

    TABMJ *z = cria_no(t);
    if(i<no->nchaves){
        leitura(no->filho[i+1], z);
        if(z->nchaves >= t){
            if(y->folha){
                y->chave[t-1] = z->chave[0];
                y->nchaves++;
                z->nchaves--;
                for(j = 0; j < z->nchaves; j++){
                    z->chave[j] = z->chave[j+1];
                }
                no->chave[i] = z->chave[0];        
            }else{
                y->chave[t-1] = no->chave[i];
                no->chave[i] = z->chave[0];
                y->nchaves++;
                z->nchaves--;
                strcpy(y->filho[t], z->filho[0]);
                for(j = 0; j < z->nchaves; j++){
                    strcpy(z->filho[j], z->filho[j+1]);
                    z->chave[j] = z->chave[j+1];
                }
                strcpy(z->filho[z->nchaves], z->filho[z->nchaves + 1]);
            }
            escrita(z, no->filho[i+1]);
            escrita(y, no->filho[i]);
            libera_no(z); libera_no(y);
            no->filho[i] = remover(no->filho[i], id, t);
            escrita(no, arq);
            libera_no(no);
            return arq;
        }
    }
    if(i>0){
        leitura(no->filho[i-1], z);
        if(z->nchaves >= t){
            if(y->folha){
                for(j = y->nchaves; j > 0; j--){
                    y->chave[j] = y->chave[j-1];
                }
                y->nchaves++;
                z->nchaves--;
                y->chave[0] = z->chave[z->nchaves];
                no->chave[i-1] = y->chave[0];
            } else {
                for(j = y->nchaves; j > 0; j--){
                    y->chave[j] = y->chave[j-1];
                    strcpy(y->filho[j+1], y->filho[j]);
                }
                strcpy(y->filho[1], y->filho[0]);
                strcpy(y->filho[0], z->filho[z->nchaves]);
                y->nchaves++;
                z->nchaves--;
                y->chave[0] = no->chave[i-1];
                no->chave[i-1] = z->chave[z->nchaves];
            }
            escrita(z, no->filho[i-1]);
            escrita(y, no->filho[i]);
            libera_no(z); libera_no(y);
            no->filho[i] = remover(no->filho[i], id, t);
            escrita(no, arq);
            libera_no(no);
            return arq;
        }
    }
    if(i<no->nchaves){
        leitura(no->filho[i+1], z);
        if(z->nchaves == t-1){
            if(y->folha){
                for(j = 0; j < t-1; j++){
                    y->chave[t-1+j] = z->chave[j];
                    y->nchaves++;
                }
                strcpy(y->prox, z->prox);
            } else {
                y->chave[t-1] = no->chave[i];
                y->nchaves++;
                for(j=0; j < t-1; j++){
                    y->chave[t+j] = z->chave[j];
                    strcpy(y->filho[t+j], z->filho[j]);
                    y->nchaves++;
                }
                strcpy(y->filho[t+t-1], z->filho[t-1]);
            }
            no->nchaves--;
            for(j = i; j < no->nchaves; j++){
                no->chave[j] = no->chave[j+1];
                strcpy(no->filho[j+1], no->filho[j+2]);
            }
            strcpy(no->filho[no->nchaves+1], "");
            escrita(y, no->filho[i]);
            libera_no(y);
            libera_no(z);
            no->filho[i] = remover(no->filho[i], id, t);

            if(no->nchaves == 0){
                char *tmp = (char *) malloc(sizeof(char)*30);
                strcpy(tmp, no->filho[0]);
                libera_no(no);
                strcpy(arq, tmp);
                free(tmp);
                return arq;
            }
            escrita(no, arq);
            libera_no(no);
            return arq;
        }
    }
    if(i>0){
        leitura(no->filho[i-1], z);
        if(z->nchaves == t-1){
            if(z->folha){
                for(j = 0; j < t-1; j++){
                    z->chave[t-1+j] = y->chave[j];
                    z->nchaves++;
                }
                strcpy(z->prox, y->prox);
            } else {
                z->chave[t-1] = no->chave[i-1];
                z->nchaves++;
                for(j = 0; j < t-1; j++){
                    z->chave[t+j] = y->chave[j];
                    z->nchaves++;
                    strcpy(z->filho[t+j], y->filho[j]);
                }
                strcpy(z->filho[t+t-1], y->filho[t-1]);
            }
            no->nchaves--;
            for(j = i-1; j<no->nchaves; j++){
                no->chave[j] = no->chave[j+1];
                strcpy(no->filho[j+1], no->filho[j+2]);
            }
            strcpy(no->filho[no->nchaves+1], "");
            escrita(z, no->filho[i-1]);
            libera_no(y);
            libera_no(z);
            no->filho[i-1] = remover(no->filho[i-1], id, t);

            if(no->nchaves == 0){
                char *tmp = malloc(sizeof(char)*30);
                strcpy(tmp, no->filho[0]);
                libera_no(no);
                strcpy(arq, tmp);
                free(tmp);
                return arq;
            }
            escrita(no, arq);
            libera_no(no);
            return arq;
        }
    }
}

char *retira(char *arq, int id, int t){
    char *b = busca(arq, id, t);
    if(!b) return arq;
    free(b);
    return remover(arq, id, t);
}

/*-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

// void imprime_chaves(char *arq, int t){
//     TABMJ *p = cria_no(t);
//     leitura(arq, p);
//     while(!p->folha) leitura(p->filho[0], p);
//     int i;
//     do{
//         for(i = 0; i < p->nchaves; i++) printf("%d ", p->chave[i]);
//         leitura(p->prox, p);
//     } while (strcmp(p->prox, ""));
//     printf("\n");
//     libera_no(p);
// }


void imp(char *arq, int andar, int t){
    TABMJ *a = cria_no(t);
    leitura(arq, a);
    if(a){
        int i,j;
        for(i=0; i<=a->nchaves-1; i++){
            if(!a->folha) imp(a->filho[i],andar+1, t);
            for(j=0; j<=andar; j++) printf("\t");
            printf("%d\n", a->chave[i].id);
        }
        if(!a->folha) imp(a->filho[i],andar+1, t);
        libera_no(a);
    }
}

void imprime(char *a, int t){
  imp(a, 0, t);
}

/*-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
typedef int VER(TJ *j);
typedef int VERL(TJ *j, TLSE *l);

TJ *TJ_copia(TJ *j){
    TJ *c = (TJ *) malloc(sizeof(TJ));
    c->id = j->id;
    c->camisa = j->camisa;
    c->capitao = j->capitao;
    c->idade = j->idade;
    c->n_partidas = j->n_partidas;
    c->n_gols = j->n_gols;
    strcpy(c->posicao, j->posicao);
    strcpy(c->nome, j->nome);
    strcpy(c->nascimento, j->nascimento);
    strcpy(c->pais_atual, j->pais_atual);
    strcpy(c->pais_origem, j->pais_origem);
    strcpy(c->time, j->time);
    return c;
}
void *le_string(char *origem, char *destino, char separador){
    char *p = strchr(origem, separador);
    if(!p) p = origem + strlen(origem) - 1;
    int n = ((int) (p - origem)) / sizeof(char);
    strncpy(destino, origem,  n);
    destino[n] = '\0';
    return p + 1;
}
TJ *le_registro_jogador(TJ *j, FILE *f, char *pais_origem){
    char nome[70], data[30], *p, texto[15], l[100], *linha;

    // Lê a linha
    fgets(l, 100, f);
    linha = l;

    // Se não for dado, vai para a próxima iteração
    if(!strchr(linha, '/')){
        linha[strlen(linha)-1] = '\0';
        strcpy(pais_origem, linha);
        return NULL;
    }

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
    linha = le_string(linha, j->pais_atual, '/');
    le_string(linha, j->time, '/');
    strcpy(j->pais_origem, pais_origem);

    // Verificando se é capitão
    p = strchr(nome, '(');
    if(p){
        p -= 1;
        *p = '\0';
        j->capitao = 1;
    } else j->capitao = 0;
    strcpy(j->nome, nome);

    // Formata a data
    int dia, ano, i;
    char mes[10];
    sscanf(data, "%d %s %d (aged %d)", &dia, mes, &ano, &j->idade);

    char meses[13][20] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    for(i=0; strcmp(meses[i], mes); i++);
    sprintf(j->nascimento, "%d-%s%d-%s%d", ano, (i+1 < 10) ? "0" : "", i+1, (dia < 10) ? "0" : "", dia);

    return j;
}
char *arq2arvbmarq(char *origem, char *destino, int t, int *n){
    TJ *j = (TJ *) malloc(sizeof(TJ));
    int c = 0;

    char *d = (char *) malloc(sizeof(char) * 30),
        *pais_origem = (char *) malloc(sizeof(char) * 30);
    strcpy(d, destino);

    // Abre o arquivo
    FILE *f = fopen(origem, "r");

    while(!feof(f)){

        // Faz a leitura do jogador
        if(le_registro_jogador(j, f, pais_origem))

        // Insere no arquivo
        d = insere(d, j, t, &c);
    }

    // Fecha o arquivo
    free(j);
    free(pais_origem);
    fclose(f);
    *n = c;
    return d;
}

TLSE *gl(char *arq, int t, TLSE *lista, VER *ver){
    TABMJ *a = cria_no(t);
    leitura(arq, a);

    int i,j;
    for(i=0; i<a->nchaves; i++){
        if(!a->folha) lista = gl(a->filho[i], t, lista, ver);
        if((a->folha) && (ver(&a->chave[i]))) // Precisa ser folha pois b+ tem nó de fantasia
            lista = TLSE_insini(lista, TJ_copia(&a->chave[i]));
    }
    if(!a->folha) lista = gl(a->filho[i], t, lista, ver);

    libera_no(a);
    return lista;
}
TLSE *gll(char *arq, int t, TLSE *lista, VERL *ver, TLSE *l){
    TABMJ *a = cria_no(t);
    leitura(arq, a);

    int i,j;
    for(i=0; i<a->nchaves; i++){
        if(!a->folha) lista = gll(a->filho[i], t, lista, ver, l);
        if((a->folha) && (ver(&a->chave[i], l)))
            lista = TLSE_insini(lista, TJ_copia(&a->chave[i]));
    }
    if(!a->folha) lista = gll(a->filho[i], t, lista, ver, l);

    libera_no(a);
    return lista;
}

TLSE *get_list(char *arq, int t, VER *v){
    return gl(arq, t, NULL, v);
}
TLSE *get_listl(char *arq, int t, VERL *v, TLSE *l){
    return gll(arq, t, NULL, v, l);
}

char *rem_generico(char *arq, int t, VER *v){
    TLSE *l = gl(arq, t, NULL, v);
    
    while(l){
        int id = ((TJ *) l->dado)->id;
        printf("%d\n", id);
        arq = retira(arq, id, t);
        l = l->prox;
    }
    
    return arq;
}
char *rem_genericol(char *arq, int t, VERL *v, TLSE *lista){
    TLSE *l = gll(arq, t, NULL, v, lista);
    while(l){
        int id = ((TJ *) l->dado)->id;
        printf("%d\n", id);
        arq = retira(arq, id, t);
        l = l->prox;
    }
    return arq;
}

/*-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

// (1) Retorno do jogador mais novo e mais velho da competição, ilustrando essas mesmas informações por seleções e por posições;
int ver_posicao(TJ *j, TLSE *l){
    char *posicao = (char *) l->dado;
    return (strcmp(j->posicao, posicao) == 0);
}
int ver_pais_atual(TJ *j, TLSE *l){
    char *pais_atual = (char *) TLSE_get(l, 0);
    return (strcmp(j->pais_atual, pais_atual) == 0);
}
int faux_jogadores_mais_novos_e_mais_velhos(TJ *j, TLSE *l){
    VERL *v = TLSE_get(l, 2);
    if(!v || v(j, NULL)){
        if(!TLSE_get(l, 0)){
            TLSE_set(l, 0, TJ_copia(j));
            TLSE_set(l, 1, TJ_copia(j));
        } else{
            TJ *jm = (TJ *) TLSE_get(l, 0), *jM = (TJ *) TLSE_get(l, 1);
            if(strcmp(j->nascimento, jm->nascimento) > 0){
                free((TJ *) l->dado);
                TLSE_set(l, 0, TJ_copia(j));
            }
            else if(strcmp(j->nascimento, jM->nascimento) < 0){
                free((TJ *) l->prox->dado);
                TLSE_set(l, 1, TJ_copia(j));
            }
        }
    }
    return 0;
}
TLSE *jogadores_mais_novos_e_mais_velhos(char *arq, int t){
    TLSE *l = TLSE_insini(NULL, NULL);
    l = TLSE_insini(l, NULL);
    get_listl(arq, t, faux_jogadores_mais_novos_e_mais_velhos, l);
    return l;
}
TLSE *jogadores_mais_novos_e_mais_velhos_por_posicao(char *arq, int t, char *posicao){
    TLSE *l = TLSE_insini(NULL, NULL);
    l = TLSE_insini(l, NULL);
    l = TLSE_insfim(l, ver_posicao);
    l = TLSE_insfim(l, posicao);
    get_listl(arq, t, faux_jogadores_mais_novos_e_mais_velhos, l);
    return l;
}
TLSE *jogadores_mais_novos_e_mais_velhos_por_selecao(char *arq, int t, char *selecao){
    TLSE *l = TLSE_insini(NULL, NULL);
    l = TLSE_insini(l, NULL);
    l = TLSE_insfim(l, ver_pais_atual);
    l = TLSE_insfim(l, selecao);
    get_listl(arq, t, faux_jogadores_mais_novos_e_mais_velhos, l);
    return l;
}
// // (2) Os jogadores que mais e menos atuaram em suas equipes;
// TJ *busca_jog(char *arq, int t, int id);

// void *mais_e_menos_selecao(char *arq, int t, char *tabela, char *selecao, TJ *mais, TJ *menos){
//     int c, i;
//     int *ids = le_tabela_selecao(tabela, selecao, &c);
//     TJ *aux = busca_jog(arq, t, ids[0]);
//     (*mais) = (*aux);
//     (*menos) = (*aux);
//     free(aux);
//     for(i = 1; i < c; i++){
//         aux = busca_jog(arq, t, ids[i]);
//         if(aux->n_partidas > mais->n_partidas) (*mais) = (*aux);
//         if(aux->n_partidas < mais->n_partidas) (*menos) = (*aux);
//         free(aux);
//     }
//     free(ids);
// }

// // (3) Os jogadores que mais e menos atuaram no total;
// void mais_e_menos_atuaram_total(char *arq, int t, TJ *mais, TJ *menos){
//     TABMJ *no = cria_no(t);
//     leitura(arq, no);
//     if(no->folha){
//         int i;
//         for(i=0; i<no->nchaves; i++){
//             if(no->chave[i].n_partidas > mais->n_partidas) (*mais) = no->chave[i];
//             if(no->chave[i].n_partidas < menos->n_partidas) (*menos) = no->chave[i];
//         }
//     } else {
//         int i;
//         for(i=0; i<=no->nchaves; i++){
//             mais_e_menos_atuaram_total(no->filho[i], t, mais, menos);
//         }
//     }
//     libera_no(no);
// }

// // (4) A menor e a maior seleção, isto é, com menos ou mais convocados;
// // A menor seleção, isto é, com menos convocados;
// char* menor_selecao(char *tabela){
	
// 	int menor = INT_MAX;
// 	char* selecao = (char*)malloc(sizeof(char)*20);
	
// 	int negativo;
	
// 	char pais[20];
// 	int contador;
// 	int *ids;
	
//     FILE *t = fopen(tabela, "rb");
//     if(!t) exit(1);
	
	
// 	// Enquanto o arquivo não termina:
// 	while(!feof(t)){
		
// 		negativo = 0;

// 		// Leio os valores da tabela
// 		fread(&pais, sizeof(char), 20, t);
// 		fread(&contador, sizeof(int), 1, t);
// 		ids = (int*)malloc(sizeof(int)*contador);
// 		for(int i = 0; i<contador; i++){
// 			fread(&ids[i], sizeof(int), 1, t);
// 			if (ids[i]==-1) negativo++;
// 		}
		
// 		if((contador-negativo) < menor){
// 			strcpy(selecao, pais);
// 			menor = contador-negativo;
// 		}
		
// 	}
	
// 	fclose(t);
// 	free(ids);
	
// 	return selecao;
	
// }
// // A maior seleção, isto é, com mais convocados;
// char* maior_selecao(char *tabela){
	
// 	int maior = INT_MIN;
// 	char* selecao = (char*)malloc(sizeof(char)*20);
	
// 	int negativo;
	
// 	char pais[20];
// 	int contador;
// 	int *ids;
	
//     FILE *t = fopen(tabela, "rb");
//     if(!t) exit(1);
	
	
// 	// Enquanto o arquivo não termina:
// 	while(!feof(t)){
		
// 		negativo = 0;

// 		// Leio os valores da tabela
// 		fread(&pais, sizeof(char), 20, t);
// 		fread(&contador, sizeof(int), 1, t);
// 		ids = (int*)malloc(sizeof(int)*contador);
// 		for(int i = 0; i<contador; i++){
// 			fread(&ids[i], sizeof(int), 1, t);
// 			if (ids[i]==-1) negativo++;
// 		}
		
// 		if((contador-negativo) > maior){
// 			strcpy(selecao, pais);
// 			maior = contador-negativo;
// 		}
// 	}
	
// 	fclose(t);
// 	free(ids);
	
// 	return selecao;
	
// }

// (5) Busca de todos os jogadores que atuam fora do seu país de origem;
int faux_jogadores_fora_do_pais_de_origem(TJ *j){
    if(strcmp(j->pais_origem, j->pais_atual)) return 1;
    return 0;
}
TLSE *jogadores_fora_do_pais_de_origem(char *arq, int t){
    return get_list(arq, t, faux_jogadores_fora_do_pais_de_origem);
}

// (6) Busca de todos os jogadores que atuam no seu país de origem;
int faux_jogadores_no_pais_de_origem(TJ *j){
    return !faux_jogadores_fora_do_pais_de_origem(j);
}
TLSE *jogadores_no_pais_de_origem(char *arq, int t){
    return get_list(arq, t, faux_jogadores_no_pais_de_origem);
}

// (7) Busca de todos os jogadores que nasceram no mesmo ano;
int faux_jogadores_do_mesmo_ano(TJ *j, TLSE *l){
    char *ano;
    ano = (char *) TLSE_get(l, 0);
    if(strncmp(j->nascimento, ano, 4)) return 0;
    return 1;
}
TLSE *jogadores_do_mesmo_ano(char *arq, int t, int ano){
    char a[5];
    TLSE *l = TLSE_insini(NULL, a), *lista;
    lista = get_listl(arq, t, faux_jogadores_do_mesmo_ano, l);
    free(l);
    return lista;
}

// (8) Busca de todos os jogadores que nasceram no mesmo mês;
int faux_jogadores_do_mesmo_mes(TJ *j, TLSE *l){
    char *mes = (char *) TLSE_get(l, 0), *m;
    if(strncmp(&j->nascimento[5], mes, 2)) return 0;
    return 1;
}
TLSE *jogadores_do_mesmo_mes(char *arq, int t, int mes){
    char a[3];
    if(mes / 10) sprintf(a, "%d", mes);
    else sprintf(a, "0%d", mes);
    TLSE *l = TLSE_insini(NULL, a), *lista;
    lista = get_listl(arq, t, faux_jogadores_do_mesmo_mes, l);
    free(l);
    return lista;
}

// (9) Busca da(s) seleção(ções) com mais jogadores que atuam fora do seu país de origem;
int cmpfint(void *p1, void *p2){
    int n1 = *((int *) p1), n2 = *((int *) p2);
    return n1 - n2;
}
int cmpfstr(void *p1, void *p2){
    char *s1 = (char *) p1, *s2 = (char *) p2;
    return strcmp(s1, s2);
}
int faux_ver_quant_lista_dupla_retorna_string(TJ *j, TLSE *l){
    VER *f = (VER *) TLSE_get(l, 2);
    if(f(j)){
        int i = TLSE_buscai(l->dado, j->pais_atual, cmpfstr);
        if(i == -1){
            char *pais = (char *) malloc(sizeof(char) * 30);
            int *v = (int *) malloc(sizeof(int));
            *v = 1;
            strcpy(pais, j->pais_atual);
            l->dado = TLSE_insini(l->dado, pais);
            l->prox->dado = TLSE_insini(l->prox->dado, v);
        } else{
            TLSE *a = TLSE_get_no((TLSE *) l->prox->dado, i);
            (*((int *) a->dado))++;
        }
    }
    return 0;
}
char *ver_quant_lista_dupla_retorna_string(char *arq, int t, VER *f){
    TLSE *l = TLSE_insini(NULL, NULL);
    l = TLSE_insini(l, NULL);
    l = TLSE_insfim(l, f);
    get_listl(arq, t, faux_ver_quant_lista_dupla_retorna_string, l);


    TLSE *a1 = (TLSE *) l->dado, *a2 = l->prox->dado;
    while(a1){
        printf("%s: %d\n", (char *) a1->dado, *((int *) a2->dado));
        a1 = a1->prox;
        a2 = a2->prox;
    }

    int i = TLSE_maiori(l->prox->dado, cmpfint);
    char *str = (char *) malloc(sizeof(char) * 30);
    strcpy(str, (char *) TLSE_get(l->dado, i));
    TLSE_libera(l->dado);
    TLSE_libera(l->prox->dado);
    free(l->prox->prox);
    free(l->prox);
    free(l);
    return str;
}

int pais_igual_ao_de_origem(TJ *j){
    return strcmp(j->pais_atual, j->pais_origem) ? 0 : 1;
}
int pais_diferente_ao_de_origem(TJ *j){
    return !pais_igual_ao_de_origem(j);
}
char *selecao_com_mais_jogadores_fora_do_pais(char *arq, int t){
    return ver_quant_lista_dupla_retorna_string(arq, t, pais_igual_ao_de_origem);
}

// (10) Busca da(s) seleção(ções) com mais jogadores que atuam no seu país de origem;
char *selecao_com_mais_jogadores_do_pais_de_origem(char *arq, int t){
        return ver_quant_lista_dupla_retorna_string(arq, t, pais_diferente_ao_de_origem);
}

// // (11) Busca das informações subordinadas, dadas a chave primária (identificador único do jogador);
// TJ *busca_jog(char *arq, int t, int id){
//     char *a = busca(arq, id, t);
//     if(!a) return NULL;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; i++);
//     TJ *jog = malloc(sizeof(TJ));
//     (*jog) = b->chave[i];
//     free(a);
//     libera_no(b);
	
//     return jog;
// }

// // (12) Alteração SOMENTE de algumas informações, por exemplo, número da camisa que ele usa em sua respectiva seleção, a posição que ele joga (EXCETO GK), o número de partidas pela seleção, o número de gols, o jogador passar a (ou deixar de) ser capitão, o país do seu time atual e o nome do time atual;
// void alteracao_camisa(char *arq, int t, int id, int nova_camisa){
//     char *a = busca(arq, id, t);
//     if(!a) return;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; b++);
//     b->chave[i].camisa = nova_camisa;
//     escrita(b, a);
//     free(a);
//     libera_no(b);
// }

// //a posição que ele joga (EXCETO GK),
// void alteracao_pos(char *arq, int t, int id, char *pos){
//     if(!strcmp(pos, "GK")) return;
//     char *a = busca(arq, id, t);
//     if(!a) return;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; b++);
//     strcpy(b->chave[i].posicao, pos);
//     escrita(b, a);
//     free(a);
//     libera_no(b);
// }

// //o número de partidas pela seleção,
// void alteracao_n_partidas(char *arq, int t, int id, int novo){
//     char *a = busca(arq, id, t);
//     if(!a) return;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; b++);
//     b->chave[i].n_partidas = novo;
//     escrita(b, a);
//     free(a);
//     libera_no(b);
// }

// //o número de gols,
// void alteracao_n_gols(char *arq, int t, int id, int novo){
//     char *a = busca(arq, id, t);
//     if(!a) return;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; b++);
//     b->chave[i].n_gols = novo;
//     escrita(b, a);
//     free(a);
//     libera_no(b);
// }

// //o jogador passar a (ou deixar de) ser capitão,
// void alteracao_cap(char *arq, int t, int id, int novo){
//     char *a = busca(arq, id, t);
//     if(!a) return;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; b++);
//     b->chave[i].capitao = novo;
//     escrita(b, a);
//     free(a);
//     libera_no(b);
// }

// //o país do seu time atual
// void alteracao_pais_atual(char *arq, int t, int id, char *novo){
//     char *a = busca(arq, id, t);
//     if(!a) return;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; b++);
//     strcpy(b->chave[i].pais_atual, novo);
//     escrita(b, a);
//     free(a);
//     libera_no(b);
// }

// //e o nome do time atual;
// void alteracao_time(char *arq, int t, int id, char *novo){
//     char *a = busca(arq, id, t);
//     if(!a) return;
//     TABMJ *b = cria_no(t);
//     leitura(a, b);
//     int i;
//     for(i=0; b->chave[i].id < id; b++);
//     strcpy(b->chave[i].time, novo);
//     escrita(b, a);
//     free(a);
//     libera_no(b);
// }


// // (13) Busca de todos os jogadores de uma seleção;
// int faux_jogadores_da_selecao(TJ *j, TLSE *l){
//     char *s = (char *) TLSE_get(l, 0);
//     if(strcmp(j->pais_atual, s)) return 1;
//     return 0;
// }
// TLSE *jogadores_da_selecao(char *arq, int t, char *selecao){
//     TLSE *lista = TLSE_insini(NULL, selecao), *l;
//     l = get_listl(arq, t, faux_jogadores_da_selecao, lista);
//     free(lista);
//     return l;
// }

// (14) Busca e remoção de todos os capitães;
int ver_capitao(TJ *j){
    return j->capitao;
}
char *remove_capitao(char *arq, int t){
    return rem_generico(arq, t, ver_capitao);
}

// (15) Remoção de jogadores a partir de uma determinada idade;
int tem_tal_idade(TJ *j, TLSE *l){
    int idade = *((int *) TLSE_get(l, 0));
    return j->idade == idade;
}
char *remove_jogadores_pela_idade(char *arq, int t, int idade){
    TLSE *l = TLSE_insini(NULL, &idade);
    return rem_genericol(arq, t, tem_tal_idade, l);
}

// // (16) Retirada de todos os jogadores de uma seleção que atuam num determinado país;
// char* retira_jog_selecao_pais(char *raiz, char *tabela, char *selecao, char *pais, int t){
	
// 	int contador;
// 	TJ jogador;
// 	TABMJ *aux = cria_no(t);
// 	int *ids = le_tabela_selecao(tabela, selecao, &contador);
	
// 	for (int i = 0; i<contador; i++){
		
// 		char *no = busca(raiz, ids[i], t);
// 		leitura(no, aux);
		
// 		for(int j = 0; j<aux->nchaves; j++) if(aux->chave[j].id == ids[i]) jogador = aux->chave[j];
		
// 		if (!strcmp(jogador.pais_atual, pais)){
// 			raiz = retira(raiz, ids[i], t);
// 			retira_tabela_selecao(tabela, ids[i]);
// 		}
		
// 	}
	
// 	free(ids);
// 	libera_no(aux);
// 	return raiz;
// }

// // (17) Retirada de todos os os jogadores de uma seleção que não atuam no país de origem;
// char* retira_jog_selecao_Norigem(char *raiz, char *tabela, char *selecao, int t){
	
// 	int contador;
// 	TJ jogador;
// 	TABMJ *aux = cria_no(t);
// 	int *ids = le_tabela_selecao(tabela, selecao, &contador);
	
// 	for (int i = 0; i<contador; i++){
		
// 		char *no = busca(raiz, ids[i], t);
// 		leitura(no, aux);
		
// 		for(int j = 0; j<aux->nchaves; j++) if(aux->chave[j].id == ids[i]) jogador = aux->chave[j];
		
// 		if (strcmp(jogador.pais_atual, jogador.pais_origem)){
// 			raiz = retira(raiz, ids[i], t);
// 			retira_tabela_selecao(tabela, ids[i]);
// 		}
		
// 	}
	
// 	free(ids);
// 	libera_no(aux);
// 	return raiz;
// }

// // (18) Retirada de todos os os jogadores de uma seleção atuam fora do país de origem;
// char *remove_jogadores_fora_do_pais_de_origem(char *arq, int t, int idade){
//     return rem_generico(arq, t, jogadores_fora_do_pais_de_origem);
// }

// // (19) Retirada de todos os os jogadores de uma seleção; e
// char *retira_selecao(char *arq, int t, char *tabela, char *selecao){
//     int c, i;
//     int *ids = le_tabela_selecao(tabela, selecao, &c);
//     for(i = 0; i < c; i++){
// 		arq = remover(arq, ids[i], t);
// 		retira_tabela_selecao(tabela, ids[i]);
// 	}
//     free(ids);
//     return arq;
// }

// // (20) Remoção de jogadores, dado um conjunto contendo suas chaves primárias.
char *remocao_por_chaves(char *arq, int t, TLSE *chaves){
    int *p;
    while(chaves){
        arq = remover(arq, *((int *) chaves->dado), t);
        chaves = chaves->prox;
    }
    return arq;
}