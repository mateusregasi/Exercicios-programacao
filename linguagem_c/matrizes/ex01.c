#include <stdio.h>

// Os elementos Aij de uma martriz Anxm representam os custos de transporte da cidade i para a cidade j. Dados n ininerários, cada um com k cidades, calcular o custo total para cada itinário. Exmeplo:
// O custo do itinerário 0 3 1 3 3 2 1 0 é a03 + a31 + a13 + a33 + a32 + a21 + a10 = 3 + 1 + 400 + 5 + 2 + 1 + 5 = 417
// {{4,1,2,3}, {5,2,1,400}, {2,1,3,8}, {7,1,2,5}}

int soma_itinerario(int *itinerario, int n, void *matriz, int k){
    
    // Transforma matriz de ponteiro pra void para ponteiro de vetor estático
    int (*mat)[k] = (int (*)[k]) matriz;

    // Vai lendo de dupla em dupla itinerario[i] e itinerario[i+1]
    // Vai fazer uma iteração a menos porque vai verificar duplas
    // Acumula tudo na variável soma
    int soma = 0;
    for(int i=0; i<n-1; i++)
        soma += mat[itinerario[i]][itinerario[i+1]];
    
    return soma;
}

int main(void){

    // Pegando o exemplo do exercício
    int mat[4][4] = {{4,1,2,3}, {5,2,1,400}, {2,1,3,8}, {7,1,2,5}};
    int itinerario[8] = {0,3,1,3,3,2,1,0};

    // Chamando a função
    int soma = soma_itinerario(itinerario, 8, mat, 4);

    // Saída de dados
    printf("Soma: %d\n", soma);

    return 0;
}