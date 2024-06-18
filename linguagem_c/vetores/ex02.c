// Implemente um programa para controlar as despesas de um condomínio de 40
// apartamentos. Cada apartamento será uma estrutura e os apartamentos serão
// armazenados em um vetor de estruturas. Para cada apartamento temos os seguintes dados
// ● nome (do responsável)
// ● número (do apartamento)
// ● área (em m2)
// ● número de moradores
// ● valor (a ser pago no mês)
// Implemente operações para:
// - ler os valores do vetor de apartamentos (exceto o valor, que inicialmente
// deve estar zerado)
// - retornar a área total ocupada pelo condomínio
// - receber as despesas do condomínio e calcular o valor a ser pago por cada
// apartamento, proporcional a sua área
// - Imprimir os dados do apartamento que tem o maior número de moradores
#include <stdio.h>
#include <stdlib.h>

typedef struct apto
{
    int area;
    int qtd_moradores;
    float aluguel;
} infos;

int main(void)
{
    int tamanho;
    scanf("%d", &tamanho);
    infos **vetor = (infos **) malloc(tamanho * sizeof(infos*));
    int soma_areas = 0;
    int soma_moradores = 0;
    float arrecadacao_total = 0;
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = (infos *) malloc(sizeof(infos));
        scanf ("%d %d %f", &vetor[i] -> area, &vetor[i] -> qtd_moradores, &vetor[i] -> aluguel);
    }

    for (int i = 0; i < tamanho; i++)
    {
        soma_areas += vetor[i] -> area;
        soma_moradores += vetor[i] -> qtd_moradores;
        arrecadacao_total += vetor[i] -> aluguel;
    }

    printf("\nArea total = %d", soma_areas);
    printf("\nMoradores totais = %d", soma_moradores);
    printf("\nArrecadacao total = %.2f\n", arrecadacao_total);
}