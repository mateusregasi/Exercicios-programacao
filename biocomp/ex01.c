// Crie um algoritmo que resolva palíndromos de DNA
// Dataset: https://www.ncbi.nlm.nih.gov/genbank/samplerecord/#OriginB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define complementar(a) (a == 't' ? 'a' : (a == 'a' ? 't' : (a == 'g' ? 'c' : 'g')))

typedef struct no{
    void *dado;
    struct no* prox;
    struct no* ant;
} NO;

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

NO *remElemento(NO *no){
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

void impListaSDNA(NO *lista, char *string, FILE *arquivo){
    NO *aux = lista;
    SDNA *auxPrint;
    while(aux != lista->ant){
        auxPrint = (SDNA *) aux->dado;
        fprintf(arquivo,"Trecho (%d->%d):\nSequência:\t\t\t\t", auxPrint->i, auxPrint->j);
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
        aux = aux->prox;
    }
}

// Lê determinada linha da fita em até 100 caracteres
char *lerFita(char *arquivo, int i){
    FILE *f = fopen(arquivo, "r");
    char string[100];
    int j = 0;
    fscanf(f, "%s",&string);
    while((!feof(f)) && (j < i)){
        fscanf(f,"%s",&string);
        j++;
    }
    if(feof(f)){
        fclose(f);
        return NULL;
    }
    fclose(f);
    int n = strlen(string);
    char *fita = (char *) malloc(sizeof(char) * n);
    strcpy(fita, string);
    return fita;
}

NO *pegaListaPalindromos(char *string){
    NO *listaPalindromos = NULL;
    int n = strlen(string);

    // Varre procurando uma sequência de duas bases nitrogenadas complementares
    // Caso ache, tenta expandir para os lados e guarda em uma lista o resultado.
    for(int i = 0; i < n-1; i++){
        if(string[i] == complementar(string[i+1])){
            int j = i, k = i+1;
            while(j > 0 && k < n-1 && string[j-1] == complementar(string[k+1])){
                j--; k++;
            }

            SDNA *dna = (SDNA *) malloc(sizeof(SDNA));
            dna->i = j;
            dna->j = k;
            listaPalindromos = insFimSDNA(listaPalindromos, dna);
        }
    }

    // Pode ser que haja sobreposição, se houver retira
    if(listaPalindromos && listaPalindromos->ant){
        NO *aux = listaPalindromos->prox;
        while(aux != listaPalindromos){
            SDNA *atual = (SDNA *) aux->dado, 
                 *anterior = (SDNA *) aux->ant->dado, 
                 *posterior = (SDNA *) aux->prox->dado;
            
            if(((atual->i >= posterior->i) && (atual->j <= posterior->j)) || ((atual->i >= anterior->i) && (atual->j <= anterior->j))){
                aux = remElemento(aux);
            } else{
                aux = aux->prox;
            }
        }
        if(listaPalindromos->prox != listaPalindromos){
            SDNA *atual = (SDNA *) listaPalindromos->dado, 
             *posterior = (SDNA *) listaPalindromos->prox->dado;
            
            if(((atual->i >= posterior->i) && (atual->j <= posterior->j))){
                listaPalindromos = remElemento(listaPalindromos);
            }
        }
        
    }

    return listaPalindromos;
}

int main(){
    char *string;
    FILE *arquivo = fopen("saida.txt", "w");
    int i = 0;
    do{
        string = lerFita("data.txt", i);
        if(string){

            fprintf(arquivo, "Linha %d:\n%s\n\n", i+1, string);
            NO *palindromos = pegaListaPalindromos(string);
            impListaSDNA(palindromos, string, arquivo);
            destroiListaSDNA(palindromos);

            free(string);
            i++;
        }
    } while(string);
    fclose(arquivo);
    return 0;
}