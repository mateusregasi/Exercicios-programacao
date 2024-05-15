#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MEM 26
#define calc_tam_vet(n) (MAX_MEM / n);

typedef struct node{
	char *dado;
	struct node *prox;
} NO;

// (Q1) Reescreva o algoritmo de seleção natural com o reservatório implementado em memória secundária.
void imp_vet(int *vet, int n);
int get_minor_vet(int *vet, int n);
char *create_partition_name(char *nome, char *conome, int i);
int get_from_opened_file(FILE *f);
int put_n_file(char *nome, int v, int n);
int file_empty(FILE *f);
void copy_n_arq2vet(int *vet, int n, int *i, char *nome);
void get_opened_arq2vet(int *vet, int n, int *i, FILE *f);

void selecao_natural(char *nome){
	FILE *fr;
	int num_max_vet, num_part, i, num_vet, 
		n, menor, num_res, i_arq,
		*vet;
	char *nome_part;

	// Abre o arquivo
	fr = fopen(nome, "r");

	// Verifica se o arquivo está vazio
	printf("Verificando a situação do arquivo: ");
	if(!fr){
		printf("o arquivo não existe\n");
		return;
	} else if(file_empty(fr)){
		printf("o arquivo está vazio\n");
		return;
	}
	printf("o arquivo foi aberto\n");

	// Calcula o tamanho máximo do vetor
	num_max_vet = calc_tam_vet(sizeof(int));
	printf("Tamanho máximo do vetor: %d\n", num_max_vet);

	// Aloca o vetor principal
	vet = (int *) malloc(sizeof(int) * num_max_vet);

	// Loop principal
	i_arq = 0;
	num_part = 0;
	while(!feof(fr)){

		// Gera o nome da partição
		nome_part = create_partition_name(nome, "_part_", num_part);
		num_part++;

		// Carrega as coisas no vetor principal
		if(num_part == 0){
			get_opened_arq2vet(vet, num_max_vet, &num_vet, fr);
			i_arq += num_vet;
		} else copy_n_arq2vet(vet, num_max_vet, &num_vet, nome_part);

		do{

			// Pega o menor elemento do vetor
			menor = get_minor_vet(vet, num_vet);
			num_vet--;

			// Coloca o elemento dentro da partição
			put_n_file(nome, menor, i_arq);
			i_arq++;

			// Pega um elemento dentro do arquivo de leitura
			n = get_from_opened_file(fr);

			// Se o elemento pego for menor que o novo menor congela
			menor = get_minor_vet(vet, num_vet);
			num_vet--;
			if(n < vet){

				

			} else{

			}

		} while(!feof(fr) && (num_res < num_max_vet));


	}

	// Fecha o arquivo
	fclose(fr);
}

int main(void){

	selecao_natural("ex01.arq");

	return 0; 
}

// Funções auxiliares
int get_minor_vet(int *vet, int n){
	int menor = 0;
	for(int i=1; i<n; i++)
		if(vet[i] < vet[menor])
			menor = i;
	if((menor != 0) && (menor != n-1)){
		int t = vet[n-1];
		vet[n-1] = vet[menor];
		vet[menor] = vet[n-1];
	}
	printf("Analisando o vetor: ");
	imp_vet(vet, n);
	printf("Menor elemento: %d\n", menor);
	return menor;
}
char *create_partition_name(char *nome, char *conome, int i){
	int n = 13 + strlen(nome) + strlen(conome);
	char *nome_completo = (char *) malloc(sizeof(char) * n),
		 *num = (char *) malloc(sizeof(char) * 13);
	sprintf(num, "%d", i);
	strcpy(nome_completo, nome);
	strcat(nome_completo, conome);
	strcat(nome_completo, num);
	free(num);
	printf("Criando a partição %s\n", nome_completo);
	return nome_completo;
}
void imp_vet(int *vet, int n){
	for(int i=0; i<n; i++){
		printf("%d ", vet[i]);
	}
	printf("\n");
}
int get_from_opened_file(FILE *f){
	int n;
	fscanf(f, "%d", &n);
	printf("Pegando no arquivo o valor %d\n", n);
	return n;
}
int file_empty(FILE *f){
	fgetc(f);
	int v = feof(f);
	fseek(f, 0l, SEEK_SET);
	return v;
}
void copy_n_arq2vet(int *vet, int n, int *i, char *nome){
	printf("Carregando o vetor com o arquivo %s\n", nome);
	FILE *f = fopen(nome, "r");
	int x, j;
	for(j=0; (j<n) && (!feof(f)); j++){
		x = get_from_opened_file(f);
		i++;
		vet[j] = x;
	}
	*i = j;
	imp_vet(vet, j);
}
void get_opened_arq2vet(int *vet, int n, int *i, FILE *f){
	printf("Carregando o vetor com o arquivo\n");
	int x, j;
	for(j=0; (j<n) && (!feof(f)); j++){
		x = get_from_opened_file(f);
		vet[j] = x;
	}
	*i = j;
	imp_vet(vet, j);
}