#include <stdio.h>
#include <stdlib.h>

// (3,5 pontos) Uma matriz ortogonal Q é uma matriz quadrada que obedece a seguinte propriedade: Q^tQ = QQ^tT = I, onde Q^T é a matriz transposta de Q e I é a matriz identidade. A matriz transposta é obtida a partir da troca das linhas por colunas de uma dada matriz. Escreva um programa que decide se uma matriz quadrada é ortogonal. Você pode assumir que a função de leitura da matriz já existe, ou seja, existe uma função void leia matriz(int n, int matriz[n][n]); que você não precisa mostrar a implementação, mas pode usa-la.

int **leia_matriz(int n){

    // Aloca o primeiro ponteiro da matriz na reap
    int **mat = (int **) malloc(sizeof(int *) * n);

    // Lê os valores
    for(int i=0; i<n; i++){ 

        // Aloca os demais vetores na reap
        mat[i] = (int *) malloc(sizeof(int) * n);

        // Lê cada elemento e coloca no lugar devido
        for(int j=0; j<n; j++)
            scanf("%d", &mat[i][j]);
    }

    return mat;
}
void imprime_matriz(int **mat, int n){
     for(int i=0; i<n; i++){ 
        for(int j=0; j<n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
     }
}

int e_ortogonal(int **mat, int n){

    // Calcular a matriz transposta
    int **matt = (int **) malloc(sizeof(int *) * n);
    for(int i=0; i<n; i++){
        matt[i] = (int *) malloc(sizeof(int) * n);
        for(int j=0; j<n; j++)
            matt[i][j] = mat[j][i];
    }

    // Multiplica a matriz
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){

            // QQt
            int soma = 0;
            for(int k=0; k<n; k++)
                soma += mat[i][k] * matt[k][j];

            // Se algum elemento do meio (diagonal principal) não for 1 retorna que não é ortogonal
            if((i == j) && (soma != 1)) return 0;
            
            // Se algum elemento fora da diagonal não for 0 retorna que a matriz não é ortogonal 
            else if((i != j) && (soma != 0)) return 0; 

            // QtQ
            soma = 0;
            for(int k=0; k<n; k++)
                soma += matt[i][k] * mat[k][j];

            // Se algum elemento do meio (diagonal principal) não for 1 retorna que não é ortogonal
            if((i == j) && (soma != 1)) return 0;
            
            // Se algum elemento fora da diagonal não for 0 retorna que a matriz não é ortogonal 
            else if((i != j) && (soma != 0)) return 0; 
        }
    }

    // Se tiver chegado até aqui quer dizer que é ortogonal
    return 1;
}

int main(void){

    // Entrada de dados
    int n, **mat;
    printf("Indique a ordem da matriz: ");
    scanf("%d", &n);
    printf("Agora indique os elementos da matriz:\n");
    mat = leia_matriz(n);

    // Imprime a matriz
    imprime_matriz(mat, n);

    // Responde se a matriz é ortogonal
    printf("A matriz lida é ortogonal?: %s\n", (e_ortogonal(mat, n)) ? "sim" : "nao");

    return 0;
}