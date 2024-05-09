#include <stdio.h>
#include <stdlib.h>

// Faça um programa em que leia uma frase do usuário e conte qual o número de vezes que cada palavra ocorre em um arquivo que contenha uma palavra por linha.

char **adiciona_palavras(char *palavra, char **palavras, int n){

	// Se a palavra não tiver sido alocada aloca ela
	if(n == 0) 
		palavras = (char **) malloc(sizeof(char *));

	// Se já tiver sido realoca
	else 
		palavras = (char **) realloc(palavras, sizeof(char *)*(n+1));

	// Adiciona a palavra no vetor e altera o realloc
	palavras[n] = palavra;

	return palavras;
}
char *adiciona_caractere(char c, char *palavra, int m){

	// Se iniciar a palavra agora: aloca memória pra ela
	if(m == 0)
		palavra = (char *) malloc(sizeof(char));
	// Se a palavra já tiver sido inicializada: realoca a memória
	else
		palavra = (char *) realloc(palavra, sizeof(char)*(m+1));

	// Adiciona o caractere
	palavra[m] = c;

	return palavra;
}
// Algoritmo super mal-otimizado que lê uma frase sem saber o tamanho
char **ler_frase_em_vetor(int *num){

	// m = número de caracteres na palavra
	// n = número de palavras
	int m = 0, n = 0; 
	char *palavra = NULL, 
		 **palavras = NULL,
		 c;
	while((c = getc(stdin)) && (c != '\n')){

		// Se os primeiros espaços forem em branco vai pulando a iteração
		if((m == 0) && (c == ' ')) continue;

		// Se for um caractere
		if(c != ' '){
			palavra = adiciona_caractere(c, palavra, m);
			m++;

		// Se não for um caractere
		} else{
			palavras = adiciona_palavras(palavra, palavras, n);
			n++;
			m = 0;
		}
	}
	// Se saiu do loop e tem palavra
	if(m > 0){
		palavras = adiciona_palavras(palavra, palavras, n);
		n++;
	}

	*num = n;
	return palavras;
}
void imp_vet(char **vet, int n){
	for(int i=0; i<n; i++)
		printf("%s\n", vet[i]);
}

int main(void){

	// Lê a frase do usuário
	int n;
	char **frase = ler_frase_em_vetor(&n);
	imp_vet(frase, n);

	return 0;
}
