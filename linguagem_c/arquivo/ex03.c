#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Faça um programa em que leia uma frase do usuário e conte qual o número de vezes que cada palavra ocorre em um arquivo que contenha uma palavra por linha. Considere que cada palavra tenha no máximo 14 caracteres e que a frase tenha no máximo 99 carecteres

// Conta palavras
int palavra_no_vetor(char *palavra, char **vet, int j){
	for(int i=0; i<j; i++)
		if(!strcmp(palavra, vet[i]))
			return 1;
	return 0;
}

// Separa as palavras
char **separa_palavras(char *frase, int *n){
	int i = 0, 
		j = 0;
	char *palavra, 
		 **palavras;

	// Enquanto existir palavras
	while(i < 100){

		// Procura a primeira letra e se chegar no final quebra
		while(frase[i] == ' ') i++;
		if((frase[i] == '\0') || (frase[i] == '\n')) break;

		// Aloca palavra
		palavra = (char *) malloc(sizeof(char) * 15);

		// Pega a frase e coleca dentro de palavra
		sscanf(&frase[i], "%s", palavra);

		// Atualiza o i
		i += strlen(palavra);

		// Verifica se a palavra já está no vetor de palavras
		if(!palavra_no_vetor(palavra, palavras, j)){

			// Joga a palavra dentro do vetor de palavras se não estiver no vetor
			if(j == 0) palavras = (char **) malloc(sizeof(char *));
			else palavras = (char **) realloc(palavras, sizeof(char *) * (j+1));
			palavras[j] = palavra;
			j++;

		// Se não desaloca a palavra pois não usou
		};
	}

	*n = j;
	return palavras;
}

// Função que conta as palavras do arquivo
int conta_palavra_arquivo(char *palavra, char *nome){

	// Abre o arquivo
	FILE *f = fopen(nome, "r");

	// Varre até chegar o final do arquivo
	int c = 0;
	char palavra_arquivo[15];
	while(!feof(f)){

		// Pega a palavra
		fgets(palavra_arquivo, 15, f);
		palavra_arquivo[strlen(palavra_arquivo)-1] = '\0';

		// Se a palavra for igual aumenta o contador
		if(!strcmp(palavra, palavra_arquivo)) c++;
	}

	// Fecha o arquivo e retorna
	fclose(f);
	return c;
}

// Imprime o vetor
void imp_vet(char **vet, int n){
	for(int i=0; i<n; i++)
		printf("%s\n", vet[i]);
}

int main(void){
	int n, m;

	// Lê a frase do usuário e separa em um vetor
	char frase[100];
	fgets(frase, 100, stdin);

	// Separa em vetor
	char **vetor_palavras = separa_palavras(frase, &n);

	// // Varre o vetor de palavras
	for(int i=0; i<n; i++){
		printf("%s: %d\n", vetor_palavras[i], conta_palavra_arquivo(vetor_palavras[i], "arquivo_nomes"));
	}

	return 0;
}
