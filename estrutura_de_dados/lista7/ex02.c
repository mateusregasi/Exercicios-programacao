#include <stdio.h>
#include <stdlib.h>

// Auxiliares
void ver_arqb(char *nome);
int len_arqb(FILE *arq, int bytes);
int *arqb2vet(char *nome, int *n);
void imp_arqb(char *nome);
void vet2arqb(int *vet, int n, char *nome);


// Escreva o algoritmo de ordenação por inserção em arquivos binários - void insertSort(char *nomeArq).
void ord_arqb_insertion_sort(char *nome);

int main(void){
    int vet[10] = {4, 2, 7, 3, 9, 0, 8, 6, 5, 1};
    
    vet2arqb(vet, 10, "arq02");
    imp_arqb("arq02");
    printf("\n------------------------------------------------------\n");
    ord_arqb_insertion_sort("arq02");
    imp_arqb("arq02");
    printf("\n");

    return 0;
}

// Auxiliares
void ver_arqb(char *nome){
    FILE *f = fopen(nome, "ab");
    fclose(f);
}
int len_arqb(FILE *arq, int bytes){
    fseek(arq, 0L, SEEK_END);
    int n = ftell(arq) / bytes;
    rewind(arq);
    return n;
}
int *arqb2vet(char *nome, int *n){
    FILE *f = fopen(nome, "rb");
    if(!f) exit(1);
    
    (*n) = len_arqb(f, sizeof(int));
    int *vet = malloc(sizeof(int) * (*n));
    fread(vet, sizeof(int), (*n), f);

    fclose(f);
    return vet;
}
void imp_arqb(char *nome){
    int n, *vet = arqb2vet(nome, &n);
    for(int i=0; i<n; i++) printf("%d ", vet[i]);
    free(vet);
}
void vet2arqb(int *vet, int n, char *nome){
    FILE *f = fopen(nome, "wb");
    if(!f) return exit(1);

    fwrite(vet, sizeof(int), n, f);
    fclose(f);
}

// Função do exercício
void ord_arqb_insertion_sort_aux(FILE *f, int i, int dado_i){
    int j = i - sizeof(int);

    // Iterações normais
    if(j >= 0){

        // Colhendo os dados
        int dado_j;
        fseek(f, j, SEEK_SET);
        fread(&dado_j, sizeof(int), 1, f);

        // Caso ache o elemento maior durante a iteração (sai da iteração)
        if(dado_j < dado_i) return;

        // Caso não ache o elemento maior durante a iteração
        fseek(f, j, SEEK_SET);
        fwrite(&dado_i, sizeof(int), 1, f);
        fwrite(&dado_j, sizeof(int), 1, f);

        // Chama a próxima iteração
        ord_arqb_insertion_sort_aux(f, i-sizeof(int), dado_i);

    // Caso não haja elemento maior (caso base)
    } else{
        fseek(f, 0, SEEK_SET);
        fwrite(&dado_i, sizeof(int), 1, f);
    }

}
void ord_arqb_insertion_sort(char *nome){

    // Abre o arquivo
    FILE *f = fopen(nome, "rb+");
    if(!f) return;

    // Conta o número de elementos
    int n = len_arqb(f, sizeof(int)) * sizeof(int), dado;

    // Sequência de iterações que vai chamar a recursiva
    for(int i=sizeof(int); i<n; i+=sizeof(int)){
        fseek(f, i, SEEK_SET);
        fread(&dado, sizeof(int), 1, f);
        ord_arqb_insertion_sort_aux(f, i, dado);
    }

    // Fecha o arquivo
    fclose(f);
}