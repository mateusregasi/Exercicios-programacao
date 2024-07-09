#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TABMJ.c"

void func(void *v){
    TJ *j = (TJ *) v;
    printf("%s\n", j->nome);
}

char *escolhe_selecao(char *s){
	printf("LISTA DE SELEÇÕES:\n");
	printf("1 - Germany\n");
	printf("2 - Scotland\n");
	printf("3 - Croatia\n");
	printf("4 - Albania\n");
	printf("5 - Slovenia\n");
	printf("6 - Denmark\n");
	printf("7 - Netherlands\n");
	printf("8 - France\n");
	printf("9 - Ukraine\n");
	printf("10 - Georgia\n");
	printf("11 - Portugal\n");
	printf("\nDigite o número de 1 a 11: ");
	int n;
	scanf("%d", &n);
	if(n==1){
		strcpy(s, "Germany");
	}
	else if(n==2){
		strcpy(s, "Scotland");
	}
	else if(n==3){
		strcpy(s, "Croatia");
	}
	else if(n==4){
		strcpy(s, "Albania");
	}
	else if(n==5){
		strcpy(s, "Slovenia");
	}
	else if(n==6){
		strcpy(s, "Denmark");
	}
	else if(n==7){
		strcpy(s, "Netherlands");
	}
	else if(n==8){
		strcpy(s, "France");
	}
	else if(n==9){
		strcpy(s, "Ukraine");
	}
	else if(n==10){
		strcpy(s, "Georgia");
	}
	else if(n==11){
		strcpy(s, "Portugal");
	}
	else{
		printf("Opção invalida!");
		s = escolhe_selecao(s);	
	}
	return s;
}

int main(void){

    int t, n = 0;
	printf("Digite o valor de t: ");
	scanf("%d", &t);

    char *nome = "EURO.txt";
	char *selecoes = "tabela_selecoes.dat";
	char *posicoes = "tabela_posicoes.dat";
    
	char *raiz = cria_arquivo(t, &n);
    raiz = arq2arvbmarq(nome, raiz, t, &n);
	
	arq2tabela_selecoes(nome, selecoes);
	arq2tabela_posicoes(nome, posicoes);
	
	int continua = 1, opcao;
	while(continua){
		printf("\n--------------------------------------------------------------------------\n\n");
		printf("Arvore atual: \n");
    	imprime(raiz, t);
		printf("\n--------------------------------------------------------------------------\n\n");
		printf("O que deseja fazer?\n");
		printf("1 - Retorno do jogador mais novo e mais velho da competição\n"); //////
		printf("2 - Os jogadores que mais e menos atuaram em suas equipes\n");
		printf("3 - Os jogadores que mais e menos atuaram no total\n");
		printf("4 - A menor e a maior seleção, isto é, com menos ou mais convocados\n");
		printf("5 - Busca de todos os jogadores que atuam fora do seu país de origem\n");
		printf("6 - Busca de todos os jogadores que atuam no seu país de origem\n");
		printf("7 - Busca de todos os jogadores que nasceram no mesmo ano\n");
		printf("8 - Busca de todos os jogadores que nasceram no mesmo mês\n");
		printf("9 - Busca da seleção com mais jogadores que atuam fora do seu país de origem\n");
		printf("10 - Busca da seleção com mais jogadores que atuam no seu país de origem\n");
		printf("11 - Busca das informações subordinadas, dadas a chave primária (identificador único do jogador)\n");
		printf("12 - Alteração SOMENTE de algumas informações\n");
		printf("13 - Busca de todos os jogadores de uma seleção\n");
		printf("14 - Busca e remoção de todos os capitães\n");
		printf("15 - Remoção de jogadores a partir de uma determinada idade;\n");
		printf("16 - Retirada de todos os jogadores de uma seleção que atuam num determinado país\n");
		printf("17 - Retirada de todos os os jogadores de uma seleção que não atuam no país de origem\n");
		printf("18 - Retirada de todos os os jogadores de uma seleção atuam fora do país de origem\n");
		printf("19 - Retirada de todos os os jogadores de uma seleção\n");
		printf("20 - Remoção de jogadores, dado um conjunto contendo suas chaves primárias\n");
		printf("21 - Sair\n");
		printf("\nDigite o número de 1 a 11: ");
		scanf("%d", &opcao);
		if(opcao == 1){

		}
		else if(opcao == 2){
			TJ J3, J4;
			char *sel = malloc(sizeof(char)*50);
			sel = escolhe_selecao(sel);
			mais_e_menos_selecao(raiz, t, selecoes, "sel", &J3, &J4);
	
    		imprime_jog(&J3);
			imprime_jog(&J4);
			free(sel);
			printf("\n--------------------------------------------------------------------------\n");

		}
		else if(opcao == 3){

		}
		else if(opcao == 4){

		}
		else if(opcao == 5){

		}
		else if(opcao == 6){

		}
		else if(opcao == 7){

		}
		else if(opcao == 8){
            int mes = 1;
            while(mes != -1){
                printf("Informe o mês (0 para sair): ");
                scanf("%d", mes);
                if(mes == 0 || mes < -1 || mes > 12){
                    printf("O mês informado foi inválido.");
                }

                TLSE *l = jogadores_do_mesmo_mes(raiz, t, mes);
                TLSE_imp(l, func);
                TLSE_libera(l);
            }
		}
		else if(opcao == 9){
            TLSE *l = selecao_com_mais_jogadores_fora_do_pais(raiz, t);
            TLSE_imp(l, func);
            TLSE_libera(l);
		}
		else if(opcao == 10){
            TLSE *l = selecao_com_mais_jogadores_do_pais_de_origem(raiz, t);
            TLSE_imp(l, func);
            TLSE_libera(l);
		}
		else if(opcao == 11){
			int id;
			printf("Digite o id do jogador: ");
			scanf("%d", &id);

			TJ *jog = busca_jog(id);
			if(jog){
				imprime_jog(jog);
				free(jog);
			}
			else{
				printf("Jogador inexistente.");
			}

		}
		else if(opcao == 12){
			int opcao_alt, id;
			printf("Digite o id do jogador a ser alterado: ");
			scanf("%d", &id);
			printf("O que você deseja alterar?:\n1 - Camisa\n2 - Posição\n3 - O número de partidas pela seleção\n4 - O número de gols\n5 - O jogador passar a (ou deixar de) ser capitão\n6 - O país do seu time atual\n7 - O nome do time atual\n\nDigite o número de 1 a 7: ");
			scanf("%d", &opcao_alt);
			if(opcao_alt == 1){
				int camisa;
				printf("Digite o novo número da camisa: ");
				scanf("%d", &camisa);
				alteracao_camisa(raiz, t, id, camisa);
			}
			else if(opcao_alt == 2){
				char *pos = malloc(sizeof(char)*10);
				printf("Escreva a nova posição(DF, MF ou FW): ");
				scanf("%s", pos);
				alteracao_pos(raiz, t, id, pos);
				free(pos);

			}
			else if(opcao_alt == 3){
				int partidas;
				printf("Digite o novo número da partidas: ");
				scanf("%d", &partidas);
				alteracao_n_partidas(raiz, t, id, partidas);
			}
			else if(opcao_alt == 4){
				int gols;
				printf("Digite o novo número de gols: ");
				scanf("%d", &gols);
				alteracao_n_gols(raiz, t, id, gols);
			}
			else if(opcao_alt == 5){
				int cap;
				printf("Digite se o jogador será ou não capitão (0 para não, 1 para sim): ");
				scanf("%d", &cap);
				alteracao_cap(raiz, t, id, cap);
			}
			else if(opcao_alt == 6){
				char *pais = malloc(sizeof(char)*10);
				printf("Escreva a nova país: ");
				scanf("%s", pais);
				alteracao_pais_atual(raiz, t, id, pais);
				free(pais);
			}
			else if(opcao_alt == 7){
				char *time = malloc(sizeof(char)*10);
				printf("Escreva a novo time: ");
				scanf("%s", time);
				alteracao_time(raiz, t, id, time);
				free(time);
			}
			else{
				printf("Opção inválida!\n")
			}


		}
		else if(opcao == 13){
			char *sel = malloc(sizeof(char)*50);
			sel = escolhe_selecao(sel);
			TLSE *p = jogadores_da_selecao(raiz, t, sel);
			while(p){
				imprime_jog((TJ *) p->dado);
				p = TLSE_retini(p, NULL);
			}
			free(sel);

		}
		else if(opcao == 14){
			raiz = remove_capitao(raiz, t);
			imprime(raiz, t);

		}
		else if(opcao == 15){
			int idade;
			printf("Digite a idade: ");
			scanf("%d\n", &idade);
			raiz = remove_jogadores_pela_idade(raiz, t, idade);
			imprime(raiz, t);
		}
		else if(opcao == 16){
			printf("Escolha a seleção: \n");
			char *sel1 = malloc(sizeof(char)*50);
			sel1 = escolhe_selecao(sel1);
			printf("Escolha o país de atuação: \n");
			char *sel2 = malloc(sizeof(char)*50);
			sel2 = escolhe_selecao(sel2);
			raiz = retira_jog_selecao_pais(raiz, selecoes, "sel1", "sel2", t);
			imprime(raiz, t);
			free(sel1);
			free(sel2);

		}
		else if(opcao == 17){
			char *sel = malloc(sizeof(char)*50);
			sel = escolhe_selecao(sel);
			raiz = retira_jog_selecao_Norigem(raiz, selecoes, sel, t);
			imprime(raiz, t);
			free(sel);

		}
		else if(opcao == 18){
			char *sel = malloc(sizeof(char)*50);
			sel = escolhe_selecao(sel);
			raiz = retira_jog_selecao_Norigem(raiz, selecoes, sel, t);
			imprime(raiz, t);
			free(sel);

		}
		else if(opcao == 19){
			char *sel = malloc(sizeof(char)*50);

			sel = escolhe_selecao(sel);
			raiz = retira_selecao(raiz, t, selecoes, sel);
			imprime(raiz, t);
			free(sel);

		}
		else if(opcao == 20){
			TLSE* l4 = jogadores_fora_do_pais_de_origem(raiz, t);
			raiz = remocao_por_chaves(raiz, t, l4);
			imprime(raiz, t);
			free(l4);

		}
		else if(opcao == 21){
			char *apagar = malloc(sizeof(char)*50);
			int iterador;
			for(iterador = 0; iterador<n; iterador++){
				sprintf(apagar, "%d.dat", iterador);
				remove(apagar);
			}
			free(apagar);
			free(raiz);
			break;

		}
/*		
	// Q1

	// Q2
	
	
	// Q3
	TJ J5, J6;
	
	printf("\n------------------------------------Q3------------------------------------\n\n");
	mais_e_menos_atuaram_total(raiz, t, &J5, &J6);
	
    imprime_jog(&J5);
	imprime_jog(&J6);
	printf("\n--------------------------------------------------------------------------\n"); 
	
	// Q4
	printf("\n------------------------------------Q4------------------------------------\n\n");
	char* menor = menor_selecao(selecoes);
	char* maior = maior_selecao(selecoes);
	
	printf("Menor: %s\n", menor);
	printf("\nMaior: %s", maior);
	
	free(menor);
	free(maior);
	printf("\n--------------------------------------------------------------------------\n");
	
	// Q5
	printf("\n------------------------------------Q5------------------------------------\n\n");
	
	TLSE* l1 = jogadores_fora_do_pais_de_origem(raiz, t);
	
	TLSE_imp(l1, func);
	free(l1);
	
	printf("\n--------------------------------------------------------------------------\n");
	
	// Q6
	printf("\n------------------------------------Q6------------------------------------\n\n");
	
	TLSE* l2 = jogadores_no_pais_de_origem(raiz, t);
	
	TLSE_imp(l2, func);
	free(l2);
	
	printf("\n--------------------------------------------------------------------------\n");
	
	// Q7
	
	printf("\n------------------------------------Q7------------------------------------\n\n");
	
	
	
	printf("\n--------------------------------------------------------------------------\n");
	
	// Q8
	
	// Q9
	
	// Q10
	
	// Q11
	printf("\n------------------------------------Q11-----------------------------------\n\n");
	
	TJ* J7 = busca_jog(raiz, t, 10);
    imprime_jog(J7);
	free(J7);
	
	printf("\n--------------------------------------------------------------------------\n");
	
	// Q12
	printf("\n------------------------------------Q12-----------------------------------\n\n");
	
	alteracao_camisa(raiz, t, 260, 28);
	alteracao_pos(raiz, t, 260, "MF");
	alteracao_n_partidas(raiz, t, 260, 9);
	alteracao_n_gols(raiz, t, 260, 2);
	alteracao_cap(raiz, t, 260, 1);
	alteracao_pais_atual(raiz, t, 260, "Scotland");
	alteracao_time(raiz, t, 260, "Celtic");
	
	TJ* J8 = busca_jog(raiz, t, 260);
    imprime_jog(J8);
	free(J8);
	
	printf("\n--------------------------------------------------------------------------\n");

	
	// Q13
	
	// Q14
	
	// Q15
	
	// Q16
	printf("\n------------------------------------Q16-----------------------------------\n\n");
	
	printf("\n--------------------------------------------------------------------------\n");
	
	// Q17
	printf("\n------------------------------------Q17-----------------------------------\n\n");

	printf("\n--------------------------------------------------------------------------\n");
	
	// Q19
	printf("\n------------------------------------Q19-----------------------------------\n\n");

	printf("\n--------------------------------------------------------------------------\n");
	
	// Q20
	printf("\n------------------------------------Q20-----------------------------------\n\n");
	
	printf("\n--------------------------------------------------------------------------\n");
	*/
    return 0;
}