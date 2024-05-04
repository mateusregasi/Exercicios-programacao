#include <stdio.h>
#include <stdlib.h>

// Todo ano um concurdo de programação premia os participantes que obtêm a maior média ponderada em uma bateria de dois testes. Escreva uma função que recebe sete parâmetros: o inteiro n indicando a quantidade de participantes do concurdo, o pontiero inscr pra o vetor de inteiros que contém as inscrições desses participantes, o ponteiro t1 para o vetor de reais que contém a nota de cada participantes no primeiro teste, e o inteiro p1 que indica o peso dessa nota na média ponderada, o ponteiro t2 para o vetor de reais que contem a nota de cada participante do segundo teste, o inteiro p2 que indica o peso dessa nota na média ponderada, e um ponteiro para a variável inteira tam. A função deve:
// - Calcular a média ponderada de cada participante
// - Criar um novo vetor de inteiros alocado dinâmicamente com o tamanho exato para conter apenas as inscruções dos participantes que obtiveram a maior media (pode haver empate);
// - Armazenar no novo vetor as inscriçẽos correspondentes (em qualquer ordem)
// - Armazenar o tamanho do novo vetor na variável tam; e
// - Retornar o ponteiro para o novo vetor
// Considere que para uma mesma posição do vetor (mesmo índice), a inscrição e as notas se referem a um mesmo participante. O protótipo da função é:

// int *premiados(int n, int *inscr, float *t1, int p1, flaot *t2, int p2, int *tam);

int *premiados(int n, int *inscr, float *t1, int p1, float *t2, int p2, int *tam){

    // Media ponderada de cada participante
    float *media = (float *) malloc(sizeof(n)), maior = 0;
    for(int i=0; i<n; i++){
        
        // Calcula a média
        media[i] = ((t1[i] * p1) + (t2[i] * p2)) / (p1 + p2);

        // Procura a maior media
        if(media[i] > maior) maior = media[i];
    }

    // Conta o número de maiores notas
    (*tam) = 0;
    for(int i=0; i<n; i++)
        if(media[i] == maior) 
            (*tam)++;
    
    // Cria o vetor alocado dinâmicamente
    int *nova_inscr = (int *) malloc(sizeof(int) * (*tam));

    // Coloca as inscrições em outro vetor
    int c = 0;
    for(int i=0; i<n; i++)
        if(media[i] == maior){
            nova_inscr[c] = inscr[i];
            c++;
        }

    // Retorna o novo vetor
    return nova_inscr;
}


void imp_vet(int *vet, int n){
    for(int i=0; i<n; i++)
        printf("%d ", vet[i]);
}
int main(void){

    int n = 5, p1 = 3, p2 = 1, tam;
    float t1[5] = {4, 1, 2, 5, 3},
        t2[5] = {5, 4, 3, 2, 1};
    int inscr[5] = {1, 2, 3, 4, 5};

    // 12   3   6   15  9
    // 5    4   3   2   1
    // 17   7   9   16  10
    // 4    7/4 9/4 4   2,4

    // Então o resultado era pra ser 1 e 4
    int *insc_maior_nota = premiados(n, inscr, t1, p1, t2, p2, &tam);

    imp_vet(insc_maior_nota, tam);

    return 0;
}