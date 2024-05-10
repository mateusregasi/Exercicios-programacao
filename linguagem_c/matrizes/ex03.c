#include <stdio.h>
#include <stdlib.h>

// Dada uma matriz nxn e uma dimensão de submatriz mxm. Crie uma função que que crie uma outra matriz a partir da primeira com os maiores elementos de cada submatriz. 

// Função que imprime a matriz
void imp_mat(int **mat, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}
// Dado i e j como a posição inical de uma submatriz, 
// ela analiza a submatriz mxm à partir dessa posição inicial
// e retorna o maior elemento 
int pegar_maior_elemento(void *matp, int i, int j, int m, int n){
	int (*mat)[n] = (int (*)[n]) matp;

	// Define o inicial como o menor elemento
	int maior = mat[i][j];

	// Define os limites i e j (caso m não divida n)
	int lim_i = (i+m <= n) ? i+m : n, 
		lim_j = (j+m <= n) ? j+m : n;
	// printf("%d %d", lim_i, lim_j);

	// Acha o maior
	for(int k=i; k<lim_i; k++)
		for(int l=j; l<lim_j; l++)
			if(maior < mat[k][l]) 
				maior = mat[k][l];

	return maior;
}
int **cria_submatriz(void *matp, int n, int m){
	int (*mat)[n] = (int (*)[n]) matp;

	// Calcula o número de linhas e colunas da matriz resultante
	int nmat = n/m + (n % m > 0);

	// Cria a matriz que vai ser retornada
	int **matr = (int **) malloc(sizeof(int *) * nmat);
	for(int i=0; i<nmat; i++)
		matr[i] = (int *) malloc(sizeof(int) * nmat);

	// Acha os índices iniciais da submatriz
	for(int i=0; i<n; i+=m){
		for(int j=0; j<n; j+=m){
			int k = (i == 0) ? 0 : i / m,
				l = (j == 0) ? 0 : j / m;
			matr[k][l] = pegar_maior_elemento(mat, i, j, m, n);
		}
	}

	return matr;
}

int main(void){

	int mat[7][7] = {{1,5,3,8,2,4,2},
					 {7,9,6,2,4,3,7},
					 {2,6,1,7,5,9,8},
					 {8,3,4,5,6,2,9},
					 {9,7,8,1,3,5,1},
					 {4,2,6,9,8,7,8},
					 {1,2,3,4,5,6,7}};

	int **mat2 = cria_submatriz(mat, 7, 2);
	imp_mat(mat2, 4);

	return 0;
}