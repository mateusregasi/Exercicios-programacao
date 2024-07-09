#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TABMJ.c"

void func(void *v){
    TJ *j = (TJ *) v;
    printf("%s\n", j->nome);
}

int main(void){

    int t = 2, n;

    char *nome = "EURO.txt";
	char *selecoes = "tabela_selecoes.dat";
	char *posicoes = "tabela_posicoes.dat";
    
	char *raiz = cria_arquivo(t, &n);
    raiz = arq2arvbmarq(nome, raiz, t, &n);
	
	arq2tabela_selecoes(nome, selecoes);
	arq2tabela_posicoes(nome, posicoes);
	
	// PADRÃO
	printf("\n ---------------------------------------------------------------------------- \n\n");
    imprime(raiz, t);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q1
	TJ J1, J2;
	mais_novo_e_mais_velho(raiz, t, &J1, &J2);
	
	printf("\n ---------------------------------------------------------------------------- \n\n");
    imprime_jog(&J1);
	imprime_jog(&J2);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q2
	mais_e_menos_selecao(raiz, t, selecoes, "Portugal", &J1, &J2);
	
	printf("\n ---------------------------------------------------------------------------- \n\n");
    imprime_jog(&J1);
	imprime_jog(&J2);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q3
	mais_e_menos_atuaram_total(raiz, t, &J1, &J2);
	
	printf("\n ---------------------------------------------------------------------------- \n\n");
    imprime_jog(&J1);
	imprime_jog(&J2);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q4
	char* menor = menor_selecao(selecoes);
	char* maior = maior_selecao(selecoes);
	printf("\n ---------------------------------------------------------------------------- \n\n");
	printf("Menor: %s\n", menor);
	printf("\nMaior: %s", maior);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q5
	TLSE* lista = jogadores_fora_do_pais_de_origem(raiz, t);
	printf("\n ---------------------------------------------------------------------------- \n\n");
	TLSE_imp(lista, func);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q6
	lista = jogadores_no_pais_de_origem(raiz, t);
	printf("\n ---------------------------------------------------------------------------- \n\n");
	TLSE_imp(lista, func);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q7
	lista = jogadores_do_mesmo_ano(raiz, t, 1999);
	printf("\n ---------------------------------------------------------------------------- \n\n");
	TLSE_imp(lista, func);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q16
	raiz = retira_jog_selecao_pais(raiz, selecoes, "Portugal", "Portugal", t);
	printf("\n ---------------------------------------------------------------------------- \n\n");
	imprime(raiz, t);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q17
	raiz = retira_jog_selecao_Norigem(raiz, selecoes, "Portugal", t);
	printf("\n ---------------------------------------------------------------------------- \n\n");
	imprime(raiz, t);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q19
	raiz = retira_selecao(raiz, t, selecoes, "Germany");
	printf("\n ---------------------------------------------------------------------------- \n\n");
	imprime(raiz, t);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	// Q20
	raiz = remocao_por_chaves(raiz, t, lista);
	printf("\n ---------------------------------------------------------------------------- \n\n");
	imprime(raiz, t);
	printf("\n ---------------------------------------------------------------------------- \n");
	
	free(lista);
	free(menor);
	free(maior);
    return 0;
}
