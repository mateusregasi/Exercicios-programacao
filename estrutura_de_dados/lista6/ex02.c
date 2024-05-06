#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    char nome[40];
    char cpf[11];
    int conta_corrente;
    int agencia;
    float saldo;
} CLI;

// Funções auxiliares
int len_arqb(char *nome, int bytes){
    FILE *f = fopen(nome, "rb");
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / bytes;
    fclose(f);
    return n;
}
void ver_arq(char *nome){
    FILE *f = fopen(nome, "ab");
    fclose(f);
}
CLI *copy_vet_clientes(CLI *v, int n){
    CLI *vet = (CLI *) malloc(sizeof(CLI) * n);
    for(int i=0; i<n; i++){
        strncpy(vet[i].nome, v[i].nome, 50); 
        strncpy(vet[i].cpf, v[i].cpf, 11);
        vet[i].conta_corrente = v[i].conta_corrente;
        vet[i].agencia = v[i].agencia;
        vet[i].saldo = v[i].saldo;
    }
    return vet;
}
CLI *ord_clientes_cpf(CLI *vet, int n){
    for(int i=0; i<n; i++){
        CLI aux = vet[i];
        int j = i-1;
        while((j >= 0) && (strcmp(vet[j].cpf, aux.cpf) > 0)){
            vet[j+1] = vet[j];
            vet[j] = aux;
            j--;
        }
    }
    return vet;
}
CLI *vet2vet_cliente(void *nome_v, void *cpf_v, int *conta_corrente, int *agencia, float *saldo, int n){
    char (*nome)[40] = (char (*)[40]) nome_v,
         (*cpf)[11] = (char (*)[11]) cpf_v;
    
    // Copia os valores
    CLI *vet = (CLI *) malloc(sizeof(CLI) * n);
    for(int i=0; i<n; i++){
        strncpy(vet[i].nome, nome[i], 50); 
        strncpy(vet[i].cpf, cpf[i], 11);
        vet[i].conta_corrente = conta_corrente[i];
        vet[i].agencia = agencia[i];
        vet[i].saldo = saldo[i];
    }

    ord_clientes_cpf(vet, n);

    return vet;
}
void imp_vet_cliente(CLI *v, int n){
    for(int i=0; i<n; i++)
        printf("%s %s %d %d %.2f\n", v[i].nome, v[i].cpf, v[i].conta_corrente, v[i].agencia, v[i].saldo);
}
void vet2arqb(CLI *vet, int n, char *nome){
    if(n <= 0) return;
    FILE *f = fopen(nome, "wb");
    fwrite(vet, sizeof(CLI), n, f);
    fclose(f);
}
CLI *arqb2vet(char *nome, int *n){
    *n = len_arqb(nome, sizeof(CLI));
    FILE *f = fopen(nome, "rb");
    CLI *vet = (CLI *) malloc(sizeof(CLI) * (*n));
    fread(vet, sizeof(CLI), *n, f);
    fclose(f);
    return vet;
}
void imp_arq_bin(char *nome){
    int n;
    CLI *vet = arqb2vet(nome, &n);
    imp_vet_cliente(vet, n);
    free(vet);
}


// (Q2) Escreva um programa em C que receba como entrada um arquivo binário de clientes “clientes.bin” e, sem ler todos os registros para memória, permita a consulta dos dados de um cliente em função do seu CPF. Considere que o formato de cada registro é dado pelos seguintes campos: nome – char (40), CPF – char(11), conta_corrente (int), agencia (int), saldo (float).

// typedef struct cliente{
//     char nome[40];
//     char cpf[11];
//     int conta_corrente;
//     int agencia;
//     float saldo;
// } CLI;

// Função do exercício
// Minha solução foi basicamente na hora de criar o arquivo ordenado de forma que eu pudesse fazer uma busca binária
CLI *buscar_pessoa_cpf_aux(FILE *f, int ini, int fim, char cpf[11]);    // Busca binária recursiva
CLI *buscar_pessoa_cpf(char *nome, char cpf[11]);                       // Função base


int main(void){

    // Criando o arquivo de exemplo
    char nome[10][40] = {"Mateus", "Regasi", "Gomes", "Martins", "Guilherme", "Pimentel", "Rangel", "Priscila", "Rebeca", "Rafael"};
    char cpf[10][11] = {"78910111213", "12345678910", "23456789101", "34567891011", "45678910111", "01234567891", "67891011121", "89101112131", "91011121314", "56789101112"};
    int conta_corrente[10] = {0,1,2,3,4,5,6,7,8,9};
    int agencia[10] = {0,1,2,3,4,5,6,7,8,9};
    float saldo[10] = {0,1,2,3,4,5,6,7,8,9};
    CLI *vet = vet2vet_cliente(nome, cpf, conta_corrente, agencia, saldo, 10);
    vet2arqb(vet, 10, "clientes.bin");

    // Imprimindo o arquivo
    imp_arq_bin("clientes.bin");

    // Buscando por CPF e fazendo a impressão
    printf("\nAgora buscando o cpf 34567891011:\n");
    CLI *c = buscar_pessoa_cpf("clientes.bin", "34567891011");
    imp_vet_cliente(c, 1);


    return 0;
}

// Funções auxiliares


// Função do exercício
CLI *buscar_pessoa_cpf_aux(FILE *f, int ini, int fim, char cpf[11]){
    
    // Condição de saída (não achou nada)
    if(ini > fim) return NULL;

    // Define o índice do elemento do meio e posiciona o cursor
    int n = (fim + ini) / 2;
    fseek(f,n * sizeof(CLI),SEEK_SET);

    // Aloca memória na reap e faz a leitura dentro dela
    CLI *c = (CLI *) malloc(sizeof(CLI));
    fread(c, sizeof(CLI), 1, f);

    // Compara o cpf do elemento do meio com o cpf procurado
    int res = strcmp(c->cpf, cpf);

    // Se achar o cpf correto retorna a posição dele na reap
    if(res == 0) return c;
    else{

        // Se não achar desaloca esse espaço da reap
        free(c);

        // E passa para a próxima iteração
        if(res > 0)
            return buscar_pessoa_cpf_aux(f, ini, n, cpf);
        else
            return buscar_pessoa_cpf_aux(f, n+1, fim, cpf);
    }
}
CLI *buscar_pessoa_cpf(char *nome, char cpf[11]){

    // Calcula o número de elementos no arquivo
    int n = len_arqb(nome, sizeof(CLI));

    // Abre o arquivo e faz a busca
    FILE *f = fopen(nome, "rb");
    CLI *cliente = buscar_pessoa_cpf_aux(f, 0, n, cpf);
    fclose(f);

    return cliente;
}






// (Q3) Escreva um programa em C que receba o arquivo de clientes do exercício Q2 e produza um arquivo binário de índices “indices.bin”, onde a sequência dos índices descreve os registros do arquivo de clientes ordenados pelo saldo.