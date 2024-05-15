#include <stdio.h>
#include <stdlib.h>
#define MAX_MEM 100
#define calc_tam_vet(n) (n / MAX_MEM);

typedef struct node{
	char *dado;
	struct node *prox;
} NO;

// (Q1) Reescreva o algoritmo de seleção natural com o reservatório implementado em memória secundária.

// Gera o nome da partição
char *gerar_nome_particao(char *nome, int i);

// Gera o nome do reservatório
char *gerar_nome_reservatorio(char *nome);

// Pega os primeiros n elementos do arquivo de leitura
void pega_vetor_inicial(int *ver, int n, FILE *f);

// Pega os primeiros n elementos do arquivo de reservatório e copia no vetor.
// Também conta o número de elementos no reservatório em m
void copia_vetor_reservatorio(int *vet, int n, int *m, char *nome);

// Verifica se o vetor está vazio
int vet_vaz(int *vet, int n);

// Pega o enésimo elemento do arquivo
int pega_n_arq(FILE *f, int n);

// Pega o menor elemento e retorna seu índice
int pega_menor_vetor(int *vet, int num_max_vet, int *i);

// Insere na iésima posição do arquivo
void ins_n_arq(char *nome, int i, int v);

// Insere elemento no final do arquivo
void ins_arq(char *nome, int v);

// Insere no final da lista
NO *insf(NO *l, char *v);


void selecao_natural(char *nome){
	int num_part, num_res, num_max_vet, 
		n_pilha, n, menor, *vet, i;
	char *nome_res, *nome_part;
	NO *lista_particoes = NULL;

	// Cria o nome do reservatorio
	nome_res = gerar_nome_reservatorio(nome);

	// Abre o arquivo de leitura e cria o arquivo de reservatório
	FILE *fr = fopen(nome, "r"),
		 *fw = fopen(nome_res, "wb");
	fclose(fw);

	// Verifica se o arquivo não existe ou está vazio
	if(!fr) return;
	if(arq_vaz(fr)){
		fclose(fr);
		return;
	}

	// Calcula o tamanho maximo do vetor
	num_max_vet = calc_tam_vet(sizeof(int));

	// Aloca na memória para o vetor base
	vet = (int *) malloc(sizeof(int) * num_max_vet);

	do{

		// Monta o vetor base
		if(num_part == 0){
			pega_vetor_inicial(vet, num_max_vet, fr);
			n_pilha = num_max_vet;
		}
		else{
			// Se o reservatório estiver vazio
			if(num_res == 0) break;

			copia_vetor_reservatorio(vet, num_max_vet, &num_res, nome_res);
		}


		// Monta a partição
		nome_part = gerar_nome(nome, num_part);
		num_part++;

		// Adiciona a partição na lista de partições
		lista_particoes = ins(lista_particoes, nome_part);

		// Começa o loop que faz o algoritmo principal
		num_res = 0;
		do{

			// Pega o topo da pilha no arquivo de leitura
			n = pega_n_arq(fr, n_pilha);
			n_pilha++;

			// Pega o novo menor elemento
			menor = pega_menor_vetor(vet, num_max_vet, &i);

			// Se ele for menor insere no repositório
			if(n < menor){
				ins_n_arq(nome_res, n, num_res);
				num_res++;
				
				// Se não
				} else vet[i] = n;

			} while((n < menor) && (num_res < num_max_vet));
			
			// Se acabar o espaço do reservatório
			if(num_res < num_max_vet) break;
		}

		


	// Enquanto existir elementos arquivo
	} while(arq_vaz(fr));

	// Se o repositório estiver vazio
	if(vet_vaz(vet, n))


}

int main(void){
	printf("%d\n", calc_tam_vet(100000));
	return 0; 
}
