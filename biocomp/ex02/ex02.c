#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 6
#define DATAFILE "data.txt"
#define EXITFILE "saida.txt"
#define compl(a) (a == 'A' ? 'T' : (a == 'T' ? 'A' : (a == 'C' ? 'G' : 'C')))

typedef struct clip{
    int i;
    int hsize;
} CLP;

typedef struct node{
    void *data;
    struct node *prox;
} NO;

NO *insini_no(NO *no, void *v){
    NO *newno = (NO *) malloc(sizeof(NO));
    newno->data = v;
    newno->prox = no;
    return newno;
}

NO *insfim_no(NO *no, void *v){
    NO *newno = (NO *) malloc(sizeof(NO)), *aux = no;
    newno->data = v;
    newno->prox = NULL;
    if(!no) return newno;
    while(aux->prox){
        aux = aux->prox;
    }
    aux->prox = newno;
    return no;
}

NO *remini_no(NO *no){
    if(!no) return NULL;
    NO *aux = no->prox;
    free(no->data);
    free(no);
    
    return aux;
}

// Lê a linha usando uma pilha de caracteres como auxiliar
char *read_line(FILE *f){
    if(feof(f)) return NULL;
    char c;
    NO *string_list = NULL; 
    char *string;
    int cont = 0;

    while(((c = fgetc(f)) != '\n') && (c != EOF)){
        cont++;
        char *p = malloc(sizeof(char));
        *p = c;
        string_list = insini_no(string_list, p);
    }

    string = (char *) malloc(sizeof(char) * (cont+1));

    for(int i=cont-1; i >= 0; i--){
        string[i] = *((char *) string_list->data);
        string_list = remini_no(string_list);
    }
    string[cont] = '\0';

    return string;
}

int is_palindromic(char *string, int n){
    for(int i = 0; i < n/2; i++){
        if(string[i] != compl(string[n-1-i])) return 0;    
    }
    return 1;
}

// Função principal, acha os clipes na força bruta usando janelas.
NO *find_clips(char *string, int k){
    int n = strlen(string), flag;
    NO *clips = NULL;
    for(int i=0; i<n-(2*k+3); i++){
        for(int l=3; l <= (k-1);l++){
            flag = 1;
            for(int j=0; j < k; j++){
                if(i+2*k+l-j >= n) continue;
                if(string[i+j] != compl(string[i+2*k+l-j])){
                    flag = 0;
                    break;
                }
            }
            if(flag){
                flag = !is_palindromic(&string[i+k], l);
                if(flag){
                    CLP *clip = (CLP *) malloc(sizeof(CLP));
                    clip->i = i;
                    clip->hsize = l+1;
                    clips = insfim_no(clips, clip);
                }
                
            }
        }
    }
    return clips;
}
void print_clips(FILE *f, NO *clipes, char *string){
    CLP *clipe;
    int cont = 1;
    while(clipes){
        clipe = (CLP *) clipes->data;
        fprintf(f, "---\nGrampo %d achado em:\n- Posição: %d\n- Tam. Pescoço: %d\n- Tam. Cabeça: %d\nFormato:\n\n", cont, clipe->i, K, clipe->hsize);
        for(int i=clipe->i; i < clipe->i+K; i++){
            fprintf(f, "%c", string[i]);
        }
        fprintf(f, "\n");
        for(int i=0; i < K; i++){
            fprintf(f, "|", string[i]);
        }
        for(int i=clipe->i+K; i < clipe->i+K+clipe->hsize; i++){
            fprintf(f, "%c", string[i]);
        }
        fprintf(f, "\n");
        for(int i=clipe->i+2*K+clipe->hsize-1; i >= clipe->i+K+clipe->hsize; i--){
            fprintf(f, "%c", string[i]);
        }
        fprintf(f, "\n---\n\n");
        clipes = clipes->prox;
        cont++;
    }
}

void destroy_list(NO *no){
    NO *rem;
    while(no){
        rem = no;
        no = no->prox;
        free(rem->data);
        free(rem);
    }
}

int main(){
    FILE *fr = fopen(DATAFILE, "r");
    FILE *fw = fopen(EXITFILE, "w");
    char *string = NULL;
    string = read_line(fr);

    do{
        NO *clips = find_clips(string, K);
        print_clips(fw, clips, string);

        destroy_list(clips);
        free(string);
        string = NULL;
    } while(string = read_line(fr));

    fclose(fr);
    fclose(fw);
    return 0;
}