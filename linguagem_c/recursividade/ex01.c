#include <stdio.h>

// Escreva uma função para verificar se os algarismos de um número estão em ordem crescente

// int verord(int n){
// 	if(n < 10) return 1;
// 	int n1, n2;
// 	n2 = n % 10;
// 	n1 = (n % 100) / 10;
// 	if(n1 > n2) return 0;
// 	return verord(n/10);
// }

int verord(int n, int b){
	int d, c;
	c = n / 10;
	d = n % 10;
	if(d > b)
		return 0;
	if(c == 0)
		return 1;
	else
		return verord(c, d);
}

int main(void){
	int n;
	printf("Digite um número: ");
	scanf("%d", &n);
	printf("O número %d está em ordem?: %s\n", n, (verord(n, n%10)) ? "sim" : "não");

	return 0;
}

