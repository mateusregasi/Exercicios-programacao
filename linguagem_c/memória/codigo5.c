#include <stdio.h>

// Vai ser printado a variável n?

void verificar_variavel();
int main(){
	int n = 10;

    verificar_variavel();

	return 0;
}

void verificar_variavel(){
    printf("%d\n", n);
}
