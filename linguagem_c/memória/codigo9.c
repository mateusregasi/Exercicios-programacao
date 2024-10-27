#include <stdio.h>

// Seremos capazes de alterar o vetor?

int main(){
	int vet[] = {1,2,3,4,5,6,7,8,9};
	vet[0] = 10;
			
	for(int i=0; i<9; i++){
		printf("%d ", vet[i]);
	}
	printf("\n");

	return 0;
}
