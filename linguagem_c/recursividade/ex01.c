#include <stdio.h>

// Escreva uma função para ver se os algarismos de um número estão em ordem crescente

int verord(int n){
	if(n < 10) return 1;
	int n1, n2;
	n2 = n % 10;
	n1 = (n % 100) / 10;
	if(n1 > n2) return 0;
	return verord(n/10);
}

int main(void){
	int n;
	printf("Digite um número: ");
	scanf("%d", &n);
	printf("O número %d está em ordem?: %s\n", n, (verord(n)) ? "sim" : "não");

	return 0;
}

