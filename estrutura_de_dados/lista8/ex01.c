#include <stdio.h>
#include <stdlib.h>
#define MAX_MEM 100
#define calc_tam_vet(n) (n / MAX_MEM);

// (Q1) Reescreva o algoritmo de seleção natural com o reservatório implementado em memória secundária.

// Gera o nome da partição
char *gerar_nome_particao(nome, i);

void selecao_natural(char *nome){
	int n, i = 0, j = 0;	// i conta o número de partições e j percorre ver_rep
	char *nome_particao;

	// Abre o arquivo
	FILE *fr = fopen(nome, "r");

	// Verifica se o arquivo não existe ou está vazio
	if(!f) return;
	if(arq_vaz(fr)){
		fclose(fr);
		return;
	}

	// Calcula o tamanho maximo do vetor
	n = calc_tam_vet(sizeof(int));

	// Aloca na memória os dois vetores que serão utilizados
	int *vet_base = (int *) malloc(sizeof(int) * n), 
		*vet_rep = (int *) malloc(sizeof(int) * n);

	do{

		// Monta o vetor base
		if(i == 0)
			pega_vetor_inicial(vet_base, n, fr);
		else
			copia_vetor_base(vet_base, vet_rep, n);

		// Monta a partição
		FILE *fw = fopen(gerar_nome(nome, i), "w");

		// Começa o loop
		j = 0;
		while(){



		}

		

		i++;

	// Enquanto existir elementos arquivo
	} while(arq_vaz(fr));

	// Se o repositório estiver vazio
	if(vet_vaz(vet, n))
}

int main(void){
	printf("%d\n", calc_tam_vet(100000));
	return 0; 
}
