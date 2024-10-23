#include <stdio.h>

// Qual é a saída do código?
// O que está acontecendo na memória?
// Conseguiremos acessar n?

int *somar1();
int main(){
	int *p;
	for(int i=0; i<10; i++){
		p = somar1();
		printf("%p\n", p);
	}
	printf("O endereço final é: %p\n", p);
	printf("O número final é: %d\n", *p);
	return 0;
}
int *somar1(){
	static int n = 0;
	printf("%d + 1 = ", n);
	printf("%d\n", ++n);
	return &n;
}
