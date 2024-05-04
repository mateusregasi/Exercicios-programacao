#include <stdio.h>

// Faça uma função que dada uma frase, retorna o número de palaras da frase. Considere que a frase pode ter espaços no início e no final e que entre duas palavras você pode ter vários espaços.

// Lê de dois em dois caracteres e soma em determinadas condições
int conta_rec(char *palavra, int i){

	// Caso base
	// Se a palavra não existir ou se a letra atual for um caracter nulo
	if((!palavra) || (palavra[i] == '\0')) return 0;

	// Caso base: primeira iteração
	if(i == 0){

		// Se os dois forem espaço vazio não soma
		if((palavra[0] == ' ') && (palavra[1] == ' ')) 
			return conta_rec(palavra, i+1);

		// Se forem soma
		return conta_rec(palavra, i+1) + 1;

	// Demais casos
	} else{

		// Se o primeiro caractere for espaço em branco e o outro preenchido soma
		if((palavra[i] == ' ') && (palavra[i+1] != ' '))
			return conta_rec(palavra, i+1) + 1;

		// Se não, vai para o próximo
		else  return conta_rec(palavra, i+1);
	}
}
// Função que chama a recursiva
int conta(char *palavra){
	return conta_rec(palavra, 0);
}

int main(void){
	
	char *nome = "Mateus Regasi Gomes Martins";
	printf("%d\n", conta(nome));

	return 0;
}