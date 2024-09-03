#include <stdio.h>

// Beecrowd 1686
// String[1 até n]
// p -> tamanho do palíndromo
// d -> deslocamento (distância entre caracteres diferentes no palíndromo)
// k -> número de substrings
// valor = k * p = numero de palindromos * tamanho dos palíndromos

// Explicando a questão (que tá bem difícil de interpretar)
// tu tem uma string de tamanho n
// você pode separar essas strings em substrings baseadas em um pulo que a questão chama de d
// por exemplo a string XXXXXXXXXX poderia ser separada em pulo d3
// resultando em 4 substrings XXX XXX XXX X
// também existe p, que é o tamanho do palíndromo
// a questão não dá o tamanho do palíndromo, então ele pode ter qualquer tamanho, mas um tamanho só
// então se você procurar palíndromos na hora de contar, todos tem que ser do mesmo tamanho
// o objetivo é encontrar o maior número possível de strings que componham um palíndromo tendo o pulo fixo e podendo variar duas coisas:
// - o tamanho do palíndromo
// - a posição do primeiro elemento das substrings
// 		por exemplo, a substring XXXXXXXXXX dividida por pulo 3 e tamanho 3 poderia ser analisada da seguinte forma
// 		XXX XXX XXX X
// 		XX XXX XXX XX ou
// 		X XXX XXX XXX

// 		se o tamanho fosse 2
// 		XX XX XX XX XX
// 		X XX XX XX XX X

// 		se o tamanho fosse 1
// 		X X X X X X X X X X X

// Função que verifia se uma string é um palíndromo
int eh_palindromo(char *vet, int n){
	for(int i=0; i<n/2; i++)
		if(vet[0] != vet[n-i-1])
			return 0;
	return 1;
}

// Dada uma string e um pulo, verifica a maior soma de palíndromos possíveis (varia o tamanho da substring)
int define_maior_palindromo(char *vet, int n, int d){
	int c = 0, maior = 0;

	// Esse for define o tamanho da substring
	for(int p=d; p>0; p--){

		// Conta o número de substrings de determinado tamanho
		c = 0;
		for(int i=0; i+p-1<n; i+=d){
			if(eh_palindromo(&vet[i], p)) c += p;
		}

		// Altera se for a maior
		if(c > maior)
			maior = c;
	}
	return maior;
}

// Dado um vetor de caracteres e um pulo define qual é o maior número
int max_palindromo(char *vet, int n, int d){
	int maior = 0, c = 0;
	maior = define_maior_palindromo(vet, n, d);
	for(int i=1; i<d; i++){
		c = define_maior_palindromo(&vet[i], n-i, d);
		if(c > maior)
			maior = c;
	}
	return maior;
}
int main(void){
	int n = 1, d = 1, maior, c = 0;
	char s[100000];

	// LOOP
	scanf("%d %d", &n, &d);
	while((n != 0) || (d != 0)){
		scanf("%s", s);

		// Processamento
		maior = max_palindromo(s, n, d);

		// Saída de dados
		printf("%d\n", maior);

		// Entrada de dados
		scanf("%d %d", &n, &d);

	}

	return 0;
}

// 5 1
// abbbc
// 4 2
// aacd
// 7 4
// babaaba
// 0 0

// 5
// 2
// 6