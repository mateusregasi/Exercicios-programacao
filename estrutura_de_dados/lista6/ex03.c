#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    char nome[41];
    char cpf[12];
    int conta_corrente;
    int agencia;
    float saldo;
} CLI;
typedef struct registro{
    int id;
    CLI pessoa;
} REG;

// ------------------------------ Funções auxiliares ------------------------------
int len_arqb(char *nome, int bytes);
void ver_arq(char *nome);

// Cópia de vetor
CLI *copy_vet_cli(CLI *v, int n);

// Ordenação de vetor
CLI *ord_vet_cli_cpf(CLI *vet, int n);
REG *ord_vet_reg_cpf(REG *vet, int n);
CLI *ord_vet_cli_saldo(CLI *vet, int n);

// Transformação vetor/vetor
REG *vet_cli2vet_reg(CLI *v, int n);
CLI *vet2vet_cli(void *nome_v, void *cpf_v, int *conta_corrente, int *agencia, float *saldo, int n);

// Transformação vetor/arquivo
void vet_cli2arqb_cli(CLI *vet, int n, char *nome);
void vet_reg2arqb_reg(REG *vet, int n, char *nome);

// Transformação arquivo/vetor
CLI *arqb_cli2vet_cli(char *nome, int *n);
REG *arqb_reg2vet_reg(char *nome, int *n);

// Impressão de vetor
void imp_vet_cli(CLI *v, int n);
void imp_vet_reg(REG *v, int n);

// Impressão de arquivo
void imp_arqb_cli(char *nome);
void imp_arqb_reg(char *nome);

// (Q3) Escreva um programa em C que receba o arquivo de clientes do exercício Q2 e produza um arquivo binário de índices “indices.bin”, onde a sequência dos índices descreve os registros do arquivo de clientes ordenados pelo saldo.

// typedef struct cliente{
//     char nome[40];
//     char cpf[11];
//     int conta_corrente;
//     int agencia;
//     float saldo;
// } CLI;

// Função do exercício
void corrige_id_reg(REG *vet, int n);
void arqb_cli2arqb_reg(char *nome);

int main(void){

    // Criando o arquivo de exemplo
    char nome[10][41] = {"Mateus", "Regasi", "Gomes", "Martins", "Guilherme", "Pimentel", "Rangel", "Priscila", "Rebeca", "Rafael"};
    char cpf[10][12] = {"78910111213", "12345678910", "23456789101", "34567891011", "45678910111", "01234567891", "67891011121", "89101112131", "91011121314", "56789101112"};
    int conta_corrente[10] = {0,1,2,3,4,5,6,7,8,9};
    int agencia[10] = {0,1,2,3,4,5,6,7,8,9};
    float saldo[10] = {0,1,2,3,4,5,6,7,8,9};
    CLI *vet = vet2vet_cli(nome, cpf, conta_corrente, agencia, saldo, 10);
    vet_cli2arqb_cli(vet, 10, "clientes.bin");

    // Imprimindo o arquivo
    imp_arqb_cli("clientes.bin");

    // Agora transforma e imprime os registros
    printf("\nAgora vamos transformar em registros:\n");
    arqb_cli2arqb_reg("clientes.bin");
    imp_arqb_reg("clientes.bin");

    return 0;
}

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
CLI *copy_vet_cli(CLI *v, int n){
    CLI *vet = (CLI *) malloc(sizeof(CLI) * n);
    for(int i=0; i<n; i++){
        strncpy(vet[i].nome, v[i].nome, 50); 
        strncpy(vet[i].cpf, v[i].cpf, 12);
        vet[i].conta_corrente = v[i].conta_corrente;
        vet[i].agencia = v[i].agencia;
        vet[i].saldo = v[i].saldo;
    }
    return vet;
}
CLI *ord_vet_cli_cpf(CLI *vet, int n){
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
REG *ord_vet_reg_cpf(REG *vet, int n){
    for(int i=0; i<n; i++){
        REG aux = vet[i];
        int j = i-1;
        while((j >= 0) && (strcmp(vet[j].pessoa.cpf, aux.pessoa.cpf) > 0)){
            vet[j+1] = vet[j];
            vet[j] = aux;
            j--;
        }
    }
    return vet;
}
CLI *ord_vet_cli_saldo(CLI *vet, int n){
    for(int i=0; i<n; i++){
        CLI aux = vet[i];
        int j = i-1;
        while((j >= 0) && (aux.saldo > vet[j].saldo)){
            vet[j+1] = vet[j];
            vet[j] = aux;
            j--;
        }
    }
    return vet;
}
REG *vet_cli2vet_reg(CLI *v, int n){
    REG *vet = (REG *) malloc(sizeof(REG) * n);
    for(int i=0; i<n; i++){
        vet[i].id = i;
        strncpy(vet[i].pessoa.nome, v[i].nome, 41); 
        strncpy(vet[i].pessoa.cpf, v[i].cpf, 12);
        vet[i].pessoa.conta_corrente = v[i].conta_corrente;
        vet[i].pessoa.agencia = v[i].agencia;
        vet[i].pessoa.saldo = v[i].saldo;
    }
    return vet;
}
CLI *vet2vet_cli(void *nome_v, void *cpf_v, int *conta_corrente, int *agencia, float *saldo, int n){
    char (*nome)[41] = (char (*)[41]) nome_v,
         (*cpf)[12] = (char (*)[12]) cpf_v;
    
    // Copia os valores
    CLI *vet = (CLI *) malloc(sizeof(CLI) * n);
    for(int i=0; i<n; i++){
        strncpy(vet[i].nome, nome[i], 41); 
        strncpy(vet[i].cpf, cpf[i], 12);
        vet[i].conta_corrente = conta_corrente[i];
        vet[i].agencia = agencia[i];
        vet[i].saldo = saldo[i];
    }

    ord_vet_cli_saldo(vet, n);

    return vet;
}
void vet_cli2arqb_cli(CLI *vet, int n, char *nome){
    if(n <= 0) return;
    FILE *f = fopen(nome, "wb");
    fwrite(vet, sizeof(CLI), n, f);
    fclose(f);
}
void vet_reg2arqb_reg(REG *vet, int n, char *nome){
    if(n <= 0) return;
    FILE *f = fopen(nome, "wb");
    fwrite(vet, sizeof(REG), n, f);
    fclose(f);
}
CLI *arqb_cli2vet_cli(char *nome, int *n){
    *n = len_arqb(nome, sizeof(CLI));
    FILE *f = fopen(nome, "rb");
    CLI *vet = (CLI *) malloc(sizeof(CLI) * (*n));
    fread(vet, sizeof(CLI), *n, f);
    fclose(f);
    return vet;
}
REG *arqb_reg2vet_reg(char *nome, int *n){
    *n = len_arqb(nome, sizeof(REG));
    FILE *f = fopen(nome, "rb");
    REG *vet = (REG *) malloc(sizeof(REG) * (*n));
    fread(vet, sizeof(REG), *n, f);
    fclose(f);
    return vet;
}
void imp_vet_cli(CLI *v, int n){
    for(int i=0; i<n; i++)
        printf("%s %s %d %d %.2f\n", v[i].nome, v[i].cpf, v[i].conta_corrente, v[i].agencia, v[i].saldo);
}
void imp_vet_reg(REG *v, int n){
    for(int i=0; i<n; i++)
        printf("%d - %s %s %d %d %.2f\n", v[i].id, v[i].pessoa.nome, v[i].pessoa.cpf, v[i].pessoa.conta_corrente, v[i].pessoa.agencia, v[i].pessoa.saldo);
}
void imp_arqb_cli(char *nome){
    int n;
    CLI *vet = arqb_cli2vet_cli(nome, &n);
    imp_vet_cli(vet, n);
    free(vet);
}
void imp_arqb_reg(char *nome){
    int n;
    REG *vet = arqb_reg2vet_reg(nome, &n);
    imp_vet_reg(vet, n);
    free(vet);
}

// Função do exercício
void corrige_id_reg(REG *vet, int n){
    for(int i=0; i<n; i++) vet[i].id++;
}
void arqb_cli2arqb_reg(char *nome){

    // Transforma o arquivo em vetor
    int n;
    CLI *vet_cli = arqb_cli2vet_cli(nome, &n);

    // Ordena em função do saldo
    ord_vet_cli_saldo(vet_cli, n);

    // Transforma o vetor de clientes em vetor de registros
    REG *vet = vet_cli2vet_reg(vet_cli, n);
    free(vet_cli);

    // Algoritmo que corrige o id (soma 1)
    corrige_id_reg(vet, n);

    // Ordena o vetor de registro de acordo com o cpf
    ord_vet_reg_cpf(vet, n);

    // Imprime o vetor de registros no arquivo
    vet_reg2arqb_reg(vet, n, nome);
}