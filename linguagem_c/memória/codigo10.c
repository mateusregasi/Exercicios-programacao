#include <stdio.h>

// Qual será a saída do print (a) e do print (b)

int main(){
	int mat[][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
	
	// print (a)
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			printf("%d ", mat[i][j]);
		}
	}
	printf("\n");

	// print (b)
	int *a = &(mat[0][0]);
	for(int i=0; i<9; i++){
                printf("%d ", *a);
		a++;
        }
        printf("\n");
        
        return 0;
}
