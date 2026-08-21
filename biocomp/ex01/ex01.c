// Crie um algoritmo que resolva palíndromos de DNA com tamanho com limite inferior igual a k
// Dataset: https://www.ncbi.nlm.nih.gov/nuccore/CP002157.1?report=fasta

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// IMPORTANTE: parâmetros do programa são definidos aqui

#define LARG_LINHA 91 // número de caracteres de uma linha da sequência de DNA computada
#define ARQUIVO_ENTRADA "data.txt"
#define ARQUIVO_SAIDA "saida.txt"
#define K 1
// Trocar caso seja maiúscula ou minúscula
// #define complementar(a) (a == 't' ? 'a' : (a == 'a' ? 't' : (a == 'g' ? 'c' : 'g')))
#define complementar(a) (a == 'T' ? 'A' : (a == 'A' ? 'T' : (a == 'G' ? 'C' : 'G')))

// ----------------------------------------------------------------


// Lista Duplamente Encadeada (escolhida pois inserção é O(1))
typedef struct no{
    void *dado;
    struct no* prox;
    struct no* ant;
} NO;

// Struct que define um trecho de DNA
typedef struct sessao_dna{
    int i;
    int j;
} SDNA;

NO *insFimSDNA(NO *no, SDNA *dna){
    NO *novo_no = (NO *) malloc(sizeof(NO));
    novo_no->dado = dna;
    novo_no->prox = novo_no;
    novo_no->ant = novo_no;
    if(no == NULL){
        return novo_no;
    } 
    novo_no->prox = no;
    novo_no->ant = no->ant;
    no->ant->prox = novo_no;
    no->ant = novo_no;    
    
    return no;
}

NO *remSDNA(NO *no){
    if(!no) return NULL;
    else{
        free(no->dado);
        if(no->prox == no){
            free(no);
            return NULL;
        } else{
            NO *r = no->prox;
            no->ant->prox = no->prox;
            no->prox->ant = no->ant;
            free(no);
            return r;
        }
    } 
}

void destroiListaSDNA(NO *no){
    if(!no) return ;
    NO *fim = no->ant, *aux;
    while(no != fim){
        free(no->dado);
        aux = no->prox;
        free(no);
        no = aux;
    }
}

void impNoSDNA(NO *aux, char *string, FILE *arquivo){
    SDNA *auxPrint = (SDNA *) aux->dado;
    fprintf(arquivo,"Trecho (%d->%d) - Tamanho %d:\nSequência:\t\t\t\t", auxPrint->i, auxPrint->j, auxPrint->j - auxPrint->i + 1);
    for(int i = auxPrint->i; i < auxPrint->j+1; i++){
        fprintf(arquivo,"%c", string[i]);
    }
    fprintf(arquivo,"\nInverso:\t\t\t\t");
    for(int i = auxPrint->j; i >= auxPrint->i; i--){
        fprintf(arquivo,"%c", string[i]);
    }
    fprintf(arquivo,"\nInverso Complementar:\t");
    for(int i = auxPrint->j; i >= auxPrint->i; i--){
        fprintf(arquivo, "%c", complementar(string[i]));
    }
    fprintf(arquivo,"\n\n");
}

void impListaSDNA(NO *lista, char *string, FILE *arquivo){
    if(!lista) return;
    NO *aux = lista;
    impNoSDNA(aux, string, arquivo);
    while(aux != lista->ant){
        impNoSDNA(aux, string, arquivo);
        aux = aux->prox;
    }
}

char *lerFitaLarguraFixa(char *arquivo, int i){
    FILE *f = fopen(arquivo, "r");
    char *string = (char *) malloc(sizeof(char) * (LARG_LINHA+1));
    strcpy(string, "");
    fseek(f, sizeof(char) * (LARG_LINHA+1) * i, SEEK_SET);
    fscanf(f, "%s", string);
    fclose(f);
    if(!strcmp("", string)){
        free(string);
        return NULL;
    }
    return string;
}

NO *pegaListaPalindromos(char *string){
    NO *listaPalindromos = NULL;
    int n = strlen(string);

    // Varre procurando uma sequência de duas bases nitrogenadas complementares
    // Caso ache, tenta expandir para os lados e guarda em uma lista o resultado.
    for(int l = 0; l < n-1; l++){
        if(string[l] == complementar(string[l+1])){
            int i = l, j = i+1;
            while(i > 0 && j < n-1 && string[i-1] == complementar(string[j+1])){
                i--; j++;
            }

            if(j - i + 1 >= K){
                SDNA *dna = (SDNA *) malloc(sizeof(SDNA));
                dna->i = i;
                dna->j = j;
                listaPalindromos = insFimSDNA(listaPalindromos, dna);
            }
            
        }
    }

    // Pode ser que determinado trecho esteja contido em outro
    // Testa os vizinhos para retirar esses trechos
    if(listaPalindromos && listaPalindromos->ant){
        NO *aux = listaPalindromos->prox;
        while(aux != listaPalindromos){
            SDNA *atual = (SDNA *) aux->dado, 
                 *anterior = (SDNA *) aux->ant->dado, 
                 *posterior = (SDNA *) aux->prox->dado;
            
            if(((atual->i >= posterior->i) && (atual->j <= posterior->j)) || ((atual->i >= anterior->i) && (atual->j <= anterior->j))){
                aux = remSDNA(aux);
            } else{
                aux = aux->prox;
            }
        }
        if(listaPalindromos->prox != listaPalindromos){
            SDNA *atual = (SDNA *) listaPalindromos->dado, 
             *posterior = (SDNA *) listaPalindromos->prox->dado;
            
            if(((atual->i >= posterior->i) && (atual->j <= posterior->j))){
                listaPalindromos = remSDNA(listaPalindromos);
            }
        }
        
    }

    return listaPalindromos;
}

int main(){
    char *string;
    FILE *arquivo = fopen(ARQUIVO_SAIDA, "w");
    int i = 0;
    do{
        string = lerFitaLarguraFixa(ARQUIVO_ENTRADA, i);
        if(string){

            NO *palindromos = pegaListaPalindromos(string);
            if(palindromos){
                fprintf(arquivo, "Linha %d - Limite Inferior K = %d\n%s\n\n", i+1, K, string);

                impListaSDNA(palindromos, string, arquivo);
                destroiListaSDNA(palindromos);
            }
            
            free(string);
            i++;
        }
    } while(string);
    fclose(arquivo);
    return 0;
}