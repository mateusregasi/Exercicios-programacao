#include <stdio.h>

// Qual é a saída do código?
// O que está acontecendo na memória?

int n = 0;

int somar1();
int main(){
	for(int i=0; i<10; i++)
		somar1();
	printf("O número final é: %d\n", n);
	return 0;
}
int somar1(){
	printf("%d + 1 = ", n);
	printf("%d\n", ++n);
}
