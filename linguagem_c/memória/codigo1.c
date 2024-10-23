#include <stdio.h>

// Qual é a saída do código?
// O que está acontecendo na memória?

int somar1();
int main(){
	for(int i=0; i<10; i++)
		somar1();
	return 0;
}
int somar1(){
	static int n = 0;
	printf("%d + 1 = ", n);
	printf("%d\n", ++n);
}