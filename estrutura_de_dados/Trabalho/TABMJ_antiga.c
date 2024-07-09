#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_simplesmente_encadeada.c"

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

/*
char *remover(char *arq, int id, int t){
    int i;
    TABMJ *no = cria_no(t);
    leitura(arq, no);
    for(i=0; (i<no->nchaves) && (no->chave[i].id < id); i++);
    if((i<no->nchaves) && (no->chave[i].id) && (no->folha)){
        int j;
        for(j=i; j<(no->nchaves-1); j++) no->chave[j] = no->chave[j+1];
        no->nchaves--;
        escrita(no, arq);
        libera_no(no);
        return arq;
    };

    if((i<no->nchaves) && (no->chave[i].id == id)) i++;
    TABMJ *y = cria_no(t), *z = cria_no(t);
    leitura(no->filho[i], y); 
    if(i<no->nchaves)
        leitura(no->filho[i+1], z);
    if(y->nchaves == t-1){
        if((i < no->nchaves) && (z->nchaves >= t)){
            if(!y->folha){
                y->chave[t-1] = no->chave[i];
                no->chave[i] = z->chave[0];
            }else{
                no->chave[i] = z->chave[0];
                no->chave[i].id++;
                y->chave[t-1] = z->chave[0];
            };
            y->nchaves++;

            int j;
            for(j=0; j<(z->nchaves-1); j++) z->chave[j] = z->chave[j+1];
            strcpy(y->filho[y->nchaves], z->filho[0]);
            for(j=0; j<z->nchaves; j++) strcpy(z->filho[j], z->filho[j+1]);
            z->nchaves--;
            escrita(y, no->filho[i]); escrita(z, no->filho[i+1]);
            libera_no(y); libera_no(z);
            no->filho[i] = remover(no->filho[i], id, t);
            escrita(no, arq);
            libera_no(no);
            return arq;
        };
        if(i>0) leitura(no->filho[i-1], z);
        if((i>0) && (z->nchaves >= t)){
            int j;
            for(j=y->nchaves; j>0; j--) y->chave[j] = y->chave[j-1];
            for(j=(y->nchaves+1); j>0; j--) strcpy(y->filho[j], y->filho[j-1]);

            if(!y->folha){
                y->chave[0] = no->chave[i-1];
                no->chave[i-1] = z->chave[z->nchaves-1];
            } else {
                no->chave[i-1] = z->chave[z->nchaves-1];
                y->chave[0] = z->chave[z->nchaves-1];
            };
            y->nchaves++;

            strcpy(y->filho[0], z->filho[z->nchaves-1]);
            z->nchaves--;
            escrita(y, no->filho[i]); escrita(z, no->filho[i-1]);
            libera_no(y); libera_no(z);
            no->filho[i] = remover(no->filho[i], id, t);
            escrita(no, arq);
            libera_no(no);
            return(arq);
        };
        if(i<no->nchaves)
            leitura(no->filho[i+1], z);
        if((i < no->nchaves) && (z->nchaves == t-1)){
            if(!y->folha){
                y->chave[t-1] = no->chave[i];
                y->nchaves++;
            }
            int j;
            for(j=0; j<t-1; j++){
                if(!y->folha) y->chave[t+j] = z->chave[j];
                else y->chave[t+j-1] = z->chave[j];
                y->nchaves++;
            };
            y->prox = z->prox;
            if(!y->folha){
                for(j=0; j<t; j++) strcpy(y->filho[t+j], z->filho[j]);
            };
            libera_no(z);
            escrita(y, no->filho[i]);
            libera_no(y);
            for(j=i; j<no->nchaves-1; j++){
                no->chave[j] = no->chave[j+1];
                strcpy(no->filho[j+1], no->filho[j+2]);
            };
            strcpy(no->filho[no->nchaves], "");
            no->nchaves--;
            if(!no->nchaves){
                char *temp = malloc(sizeof(char)*30);
                strcpy(temp, no->filho[0]);
                remove(arq);
                free(arq);
                arq = temp;
            }
            escrita(no, arq);
            libera_no(no);
            arq = remover(arq, id, t);
            return arq;
        }
        if(i>0) leitura(no->filho[i-1], z);
        if((i > 0) && (z->nchaves == t-1)){
            if(!y->folha){
                if(i == no->nchaves){
                    z->chave[t-1] = no->chave[i-1];
                } else {
                    z->chave[t-1] = no->chave[i];
                };
                z->nchaves++;
            }
            int j;
            for(j=0; j<t-1; j++){
                if(!y->folha) z->chave[t+j] = y->chave[j];
                else z->chave[t+j-1] = y->chave[j];
                z->nchaves++;
            };
            z->prox = y->prox;
            if(!z->folha){
                for(j=0; j<t; j++) strcpy(z->filho[t+j], y->filho[j]);
                remove(no->filho[i]);
            }else{
                escrita(y, no->filho[i]);
            };
            libera_no(y);
            escrita(z, no->filho[i-1]);
            libera_no(z);

            strcpy(no->filho[no->nchaves], "");
            no->nchaves--;
            if(!no->nchaves){
                char *temp = malloc(sizeof(char)*30);
                strcpy(temp, no->filho[0]);
                remove(arq);
                free(arq);
                arq = temp;
            }
            libera_no(no);
            arq = remover(arq, id, t);
            return arq;
        }
    }
    no->filho[i] = remover(no->filho[i], id, t);
    libera_no(y); libera_no(z);
    escrita(no, arq);
    libera_no(no);
    return(arq);
}
*/

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
TJ *le_registro_jogador(TJ *j, FILE *f, char *pais_atual){
    char nome[70], data[30], *p, texto[15], l[100], *linha;

    // Lê a linha
    fgets(l, 100, f);
    linha = l;

    // Se não for dado, vai para a próxima iteração
    if(!strchr(linha, '/')){
        linha[strlen(linha)-1] = '\0';
        strcpy(pais_atual, linha);
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
    linha = le_string(linha, j->pais_origem, '/');
    le_string(linha, j->time, '/');
    strcpy(j->pais_atual, pais_atual);

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

char *arq2arvbmarq(char *origem, char *destino, int t, int *n){
    TJ *j = (TJ *) malloc(sizeof(TJ));
    int c = (*n);

    char *d = (char *) malloc(sizeof(char) * 30),
        *pais_atual = (char *) malloc(sizeof(char) * 30);
    strcpy(d, destino);

    // Abre o arquivo
    FILE *f = fopen(origem, "r");

    while(!feof(f)){

        // Faz a leitura do jogador
        if(le_registro_jogador(j, f, pais_atual))

        // Insere no arquivo
        d = insere(d, j, t, &c);
		
    }

    // Fecha o arquivo
    free(j);
    free(pais_atual);
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
        if((a->folha) && (ver(&a->chave[i], l))) // Precisa ser folha pois b+ tem nó de fantasia
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
/*-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

//////////////////////////////////////////////////////////////////////////////////////////////

// Lê uma linha do arquivo "EURO.txt" e passa adequadamente para a tabela 
// Passa todas as informações do arquivo "EURO.txt" para a tabela
// Lê a informação requisitada da tabela e retorna um vetor (atualiza um contador externo)
// Substitui um ID da tabela pelo valor "-1"

void le_registro2tabela_selecoes(TJ *j, FILE *f, FILE *s, int* contador, int* pulo);
void arq2tabela_selecoes(char *nome, char *tabela);
int* le_tabela_selecao(char *tabela, char *selecao, int* c);
void retira_tabela_selecao(char *tabela, int num);

void le_registro2tabela_posicoes(TJ *j, FILE *f, FILE *s, int* contador, char *pos);
void arq2tabela_posicoes(char *nome, char *tabela);
int* le_tabela_posicao(char *tabela, char *pos, int* c);
void retira_tabela_posicao(char *tabela, int num);

//////////////////////////////////////////////////////////////////////////////////////////////

void le_registro2tabela_selecoes(TJ *j, FILE *f, FILE *s, int* contador, int* pulo){
    char l[100], *linha;

    fgets(l, 100, f);
    linha = l;

	// Se não é o registro de um jogador:
    if(!strchr(linha, '/')){
		if(!strchr(linha, '.')){
			
			// Caso não seja a primeira iteração:
			if((*contador)){
				
				// Volta para o contador da seleção anterior e reescrevo 
				fseek(s, (*pulo), SEEK_SET);
				fwrite(contador, sizeof(int), 1, s);
				
				// Atualizo os valores e ponteiros
				(*pulo) += (sizeof(int)*((*contador)+1)) + (sizeof(char)*20);
				(*contador) = 0;
				
				fseek(s, 0, SEEK_END);
			}
			
			// Escrevo o pais e seu contador (zerado)
			fwrite(linha, (sizeof(char)*20), 1, s);
			fwrite(contador, sizeof(int), 1, s);
		}
		return;
	}
	
	// Escrevo o id do jogador
    sscanf(l, "%d",  &j->id);
	fwrite(&j->id, sizeof(int), 1, s);
	
	// Atualizo o contador
	(*contador)++;
	return;
}

void arq2tabela_selecoes(char *nome, char *tabela){
	
	// Inicializo o contador e pulo que serão usados no "le_registro2tabela_selecoes"
	int contador = 0;
	int pulo = sizeof(char)*20;

	// Abro os arquivos
    FILE *f = fopen(nome, "r");
    if(!f) exit(1);
	
    FILE *t = fopen(tabela, "wb+");
    if(!t) exit(1);

	TJ *j = (TJ *) malloc(sizeof(TJ));
	
	// Leio as linhas do arquivo "EURO.txt" até que ele acabe
    while(!feof(f)){
		le_registro2tabela_selecoes(j, f, t, &contador, &pulo);
    }
	
	// CORREÇÃO PARA A ÚLTIMA SELEÇÃO LIDA //
	fseek(t, pulo, SEEK_SET);
	fwrite(&contador, sizeof(int), 1, t);
	
	// Atualizo os valores e ponteiros
	pulo += (sizeof(int)*(contador+1)) + (sizeof(char)*20);
	contador = 0;
	
	fseek(t, 0, SEEK_END);
	/////////////////////////////////////////

	free(j);
    fclose(f);
	fclose(t);
}

int* le_tabela_selecao(char *tabela, char *selecao, int* c){
	char pais[20];
	int contador;
	int *ids;
	
	char* s = (char*)malloc(sizeof(char)*20);
	strcpy(s, selecao);
	strcat(s, "\n");
	
    FILE *t = fopen(tabela, "rb");
    if(!t) exit(1);
	
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){

		// Leio os valores da tabela
		fread(&pais, sizeof(char), 20, t);
		fread(&contador, sizeof(int), 1, t);
		ids = (int*)malloc(sizeof(int)*contador);
		for(int i = 0; i<contador; i++) fread(&ids[i], sizeof(int), 1, t);
		
		// Se não for a seleção requisitada, passo para próxima, se sim, retorno.
		if(strcmp(pais, s)) free(ids);
		else break;
		
	}
	
	// Se não encontrei a seleção requisitada, retorno nulo 
	if((feof(t)) && (strcmp(pais, s))){
		fclose(t);
		(*c) = 0;
		return NULL;
	}
	
	// Retorno a lista de IDs da seleção requisitada
	fclose(t);
	(*c) = contador;
	return ids;
}

void retira_tabela_selecao(char *tabela, int num){
	char pais[20];
	int contador;
	int pulo;
	
	// O valor -1 é escolhido para representar IDs que não existem mais.
	int del = -1;
	int id;
	
    FILE *t = fopen(tabela, "rb+");
    if(!t) exit(1);
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){
		
		// Leio os valores da tabela
		fread(&pais, sizeof(char), 20, t);
		fread(&contador, sizeof(int), 1, t);
		
		for(int i = 0; i<contador; i++){
			fread(&id, sizeof(int), 1, t);
			
			// Se encontro o ID requisitado
			if(id==num){
				
				
				// Reescrevo ele como "-1"
				pulo = (ftell(t)-sizeof(int));
				fseek(t, pulo, SEEK_SET);
				fwrite(&del, sizeof(int), 1, t);
				fclose(t);
				return;
				
			}
		}
	}

	fclose(t);
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void le_registro2tabela_posicoes(TJ *j, FILE *f, FILE *s, int* contador, char *pos){
	char l[100], *linha;

    fgets(l, 100, f);
    linha = l;

	// Se não é o registro de um jogador:
    if (!strchr(linha, '/')) return;
	
	// Escrevo o id do jogador se ele for da posição requisitada
    sscanf(l, "%d/%d/",  &j->id, &j->camisa);
    for(int i=0; i<2; i++){
        linha = strchr(linha, '/');
        linha++;
    }
	
    linha = le_string(linha, j->posicao, '/');
	if (!strcmp(j->posicao, pos)){
		fwrite(&j->id, sizeof(int), 1, s);
		
		// Atualizo o contador
		(*contador)++;
	}
	
	return;
}

void arq2tabela_posicoes(char *nome, char *tabela){
	
	// Inicializo o contador e pulo que serão usados no "le_registro2tabela_posicoes"
	int contador = 0;
	int pulo = sizeof(char)*3;
	
	char* pos[4] = {"GK", "DF", "MF", "FW"};

	// Abro os arquivos
    FILE *f = fopen(nome, "r");
    if(!f) exit(1);
	
    FILE *t = fopen(tabela, "wb+");
    if(!t) exit(1);

	TJ *j = (TJ *) malloc(sizeof(TJ));
	
	for (int i = 0; i<4; i++){
		
		// Escrevo a posição e inicio o contador no arquivo
		fwrite(pos[i], (sizeof(char)*3), 1, t);
		fwrite(&contador, sizeof(int), 1, t);
		
		// Leio as linhas do arquivo "EURO.txt" até que ele acabe
		while(!feof(f)){
			le_registro2tabela_posicoes(j, f, t, &contador, pos[i]);
		}
		
		// Atualizo o contador no arquivo (tabela)
		fseek(t, pulo, SEEK_SET);
		fwrite(&contador, sizeof(int), 1, t);
		pulo += (sizeof(char)*3) + (sizeof(int)*(contador+1));
		contador = 0;
		fseek(t, 0, SEEK_END);
		
		
		fseek(f, 0, SEEK_SET);
	}

	free(j);
    fclose(f);
	fclose(t);
}

int* le_tabela_posicao(char *tabela, char *pos, int* c){
	char p[3];
	int contador;
	int *ids;
	
    FILE *t = fopen(tabela, "rb");
    if(!t) exit(1);
	
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){

		// Leio os valores da tabela
		fread(&p, sizeof(char), 3, t);
		fread(&contador, sizeof(int), 1, t);
		ids = (int*)malloc(sizeof(int)*contador);
		for(int i = 0; i<contador; i++) fread(&ids[i], sizeof(int), 1, t);
		
		// Se não for a posição requisitada, passo para próxima, se sim, retorno.
		if(strcmp(p, pos)) free(ids);
		else break;
		
	}
	
	// Se não encontrei a posição requisitada, retorno nulo 
	if((feof(t)) && (strcmp(p, pos))){
		fclose(t);
		(*c) = 0;
		return NULL;
	}
	
	// Retorno a lista de IDs da seleção requisitada
	fclose(t);
	(*c) = contador;
	return ids;
}

void retira_tabela_posicao(char *tabela, int num){
	char pos[3];
	int contador;
	int pulo;
	
	// O valor -1 é escolhido para representar IDs que não existem mais.
	int del = -1;
	int id;
	
    FILE *t = fopen(tabela, "rb+");
    if(!t) exit(1);
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){
		
		// Leio os valores da tabela
		fread(&pos, sizeof(char), 3, t);
		fread(&contador, sizeof(int), 1, t);
		
		for(int i = 0; i<contador; i++){
			fread(&id, sizeof(int), 1, t);
			
			// Se encontro o ID requisitado
			if(id==num){
				
				
				// Reescrevo ele como "-1"
				pulo = (ftell(t)-sizeof(int));
				fseek(t, pulo, SEEK_SET);
				fwrite(&del, sizeof(int), 1, t);
				fclose(t);
				return;
				
			}
		}
	}

	fclose(t);
	return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// (1) Retorno do jogador mais novo e mais velho da competição, ilustrando essas mesmas informações por seleções e por posições;
void mais_novo_e_mais_velho_aux(char *arq, int t, TJ *novo, TJ *velho){
    TABMJ *no = cria_no(t);
    leitura(arq, no);
	
    if(no->folha){
        int i;
        for(i=0; i<no->nchaves; i++){
            if(strcmp(no->chave[i].nascimento, novo->nascimento) == 1) (*novo) = no->chave[i];
            if(strcmp(no->chave[i].nascimento, velho->nascimento) == -1) (*velho) = no->chave[i];
        }
    } else {
        int i;
        for(i=0; i<=no->nchaves; i++) mais_novo_e_mais_velho_aux(no->filho[i], t, novo, velho);
    }
    libera_no(no);
}

void mais_novo_e_mais_velho(char *arq, int t, TJ *novo, TJ *velho){
	
    TABMJ *no = cria_no(t);
    leitura(arq, no);

    while(!no->folha){
        leitura(no->filho[0], no);
    }
    (*novo) = no->chave[0];
    (*velho) = no->chave[0];
    libera_no(no);
	
    mais_novo_e_mais_velho_aux(arq, t, novo, velho);
}

// (2) Os jogadores que mais e menos atuaram em suas equipes;
TJ *busca_jog(char *arq, int t, int id);

void *mais_e_menos_selecao(char *arq, int t, char *tabela, char *selecao, TJ *mais, TJ *menos){
    int c, i;
    int *ids = le_tabela_selecao(tabela, selecao, &c);
    TJ *aux = busca_jog(arq, t, ids[0]);
    (*mais) = (*aux);
    (*menos) = (*aux);
    free(aux);
    for(i = 1; i < c; i++){
        aux = busca_jog(arq, t, ids[i]);
        if(aux->n_partidas > mais->n_partidas) (*mais) = (*aux);
        if(aux->n_partidas < mais->n_partidas) (*menos) = (*aux);
        free(aux);
    }
    free(ids);
}

// (3) Os jogadores que mais e menos atuaram no total;


// (4) A menor e a maior seleção, isto é, com menos ou mais convocados;



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
    ano = TLSE_get(l, 0);
    if(strncmp(j->nascimento, ano, 4)) return 0;
    return 1;
}

TLSE *jogadores_do_mesmo_ano(char *arq, int t, int ano){
    char a[5];
    sprintf(a, "%d", ano);
    TLSE *l = TLSE_insini(NULL, a), *lista;
    lista = get_listl(arq, t, faux_jogadores_do_mesmo_ano, l);
    free(l);
    return lista;
}

// (8) Busca de todos os jogadores que nasceram no mesmo mês;

// (9) Busca da(s) seleção(ções) com mais jogadores que atuam fora do seu país de origem;

// (10) Busca da(s) seleção(ções) com mais jogadores que atuam no seu país de origem;

// (11) Busca das informações subordinadas, dadas a chave primária (identificador único do jogador);


// (12) Alteração SOMENTE de algumas informações, por exemplo,
//número da camisa que ele usa em sua respectiva seleção,


// (13) Busca de todos os jogadores de uma seleção;

// (14) Busca e remoção de todos os capitães;

// (15) Remoção de jogadores a partir de uma determinada idade;

// (16) Retirada de todos os jogadores de uma seleção que atuam num determinado país;


// (17) Retirada de todos os os jogadores de uma seleção que não atuam no país de origem;


// (18) Retirada de todos os os jogadores de uma seleção atuam fora do país de origem;

// (19) Retirada de todos os os jogadores de uma seleção; e


// (20) Remoção de jogadores, dado um conjunto contendo suas chaves primárias.
