#include <stdio.h>
#include <stdlib.h>

// Auxiliares
void ver_arqb(char *nome);
int len_arqb(FILE *arq, int bytes);
int *arqb2vet(char *nome, int *n);
void imp_arqb(char *nome);
void vet2arqb(int *vet, int n, char *nome);


// Escreva o algoritmo de ordenação por bolha em arquivos binários - void BolhaBin(char *nomeArq).
void ord_arqb_bolha(char *nome);

int main(void){
    int vet[10] = {4, 2, 7, 3, 9, 0, 8, 6, 5, 1};
    
    vet2arqb(vet, 10, "arq01");
    imp_arqb("arq01");
    printf("\n------------------------------------------------------\n");
    ord_arqb_bolha("arq01");
    imp_arqb("arq01");
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
void ord_arqb_bolha_aux(FILE *f, int i, int ult){

    // Se não for a última iteração
    if(i != ult){

        // Posiciona o cursor
        fseek(f, i, SEEK_SET);

        // Lê os dois números em sequência 
        int i_dado, j_dado;
        fread(&i_dado, sizeof(int), 1, f);
        fread(&j_dado, sizeof(int), 1, f);
        // printf("Números analisados: (%d) e (%d)\n", i_dado, j_dado);

        // Se i for maior que j troca
        if(i_dado > j_dado){
            fseek(f, i, SEEK_SET);
            fwrite(&j_dado, sizeof(int), 1, f);
            fwrite(&i_dado, sizeof(int), 1, f);
            // printf("Trocando (%d) por (%d)\n",  i_dado, j_dado);
        }

        // Chama a próxima iteração
        ord_arqb_bolha_aux(f, i+sizeof(int), ult);
    }
}
void ord_arqb_bolha(char *nome){

    // Abre o arquivo
    FILE *f = fopen(nome, "rb+");
    if(!f) return;

    // Conta o número de elementos
    int n = len_arqb(f, sizeof(int));

    // Acha o último endereço para ser usado na função auxiliar
    int ult_end = (n-1)*sizeof(int);

    // Chama o algoritmo de ordenação bolha n vezes
    for(int i=ult_end; i>0; i -= sizeof(int)){
        ord_arqb_bolha_aux(f, 0, i);
    }

    // Fecha o arquivo
    fclose(f);
}