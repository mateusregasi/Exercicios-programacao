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
char *escolhe_posicao(char *s){
	printf("LISTA DE POSIÇÕES:\n");
	printf("1 - GK\n");
	printf("2 - FW\n");
	printf("3 - DF\n");
	printf("4 - MF\n");
	printf("\nDigite o número de 1 a 4: ");
	int n;
	scanf("%d", &n);
	if(n==1){
		strcpy(s, "GK");
	}
	else if(n==2){
		strcpy(s, "FW");
	}
	else if(n==3){
		strcpy(s, "DF");
	}
	else if(n==4){
		strcpy(s, "MF");
	}
	else{
		printf("Opção invalida!");
		s = escolhe_posicao(s);	
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
		printf("15 - Remoção de jogadores a partir de uma determinada idade\n");
		printf("16 - Retirada de todos os jogadores de uma seleção que atuam num determinado país\n");
		printf("17 - Retirada de todos os os jogadores de uma seleção que não atuam no país de origem\n");
		printf("18 - Retirada de todos os os jogadores de uma seleção atuam fora do país de origem\n");
		printf("19 - Retirada de todos os os jogadores de uma seleção\n");
		printf("20 - Remoção de jogadores, dado um conjunto contendo suas chaves primárias\n");
		printf("21 - Sair\n");
		
		printf("\nDigite o número de 1 a 21: ");
		scanf("%d", &opcao);
		
		if(opcao == 1){
			int op1;
			printf("O que deseja fazer?\n");
			printf("1 - Retorno do jogador mais novo e mais velho da competição\n"); //////
			printf("2 - Retorno do jogador mais novo e mais velho de uma determinada seleção\n");
			printf("3 - Retorno do jogador mais novo e mais velho de uma determinada posição\n");
			printf("\nDigite o número de 1 a 3: ");
			scanf("%d", &op1);
			TLSE *Q1 = NULL;

			if(op1 == 1){
				Q1 = jogadores_mais_novos_e_mais_velhos(raiz, t);
			} else if(op1 == 2){
				char *str1 = (char *) malloc(sizeof(char) * 30);
				str1 = escolhe_selecao(str1);
				Q1 = jogadores_mais_novos_e_mais_velhos_por_selecao(raiz, t, str1);
				free(str1);
			} else if(op1 == 3){
				char *str1 = (char *) malloc(sizeof(char) * 30);
				str1 = escolhe_posicao(str1);
				Q1 = jogadores_mais_novos_e_mais_velhos_por_posicao(raiz, t, str1);
				free(str1);
			}

			if(!Q1){
				printf("Inválido!!!\n");
			}else{
				printf("Mais novo:");
	    		imprime_jog((TJ*)TLSE_get(Q1, 0));
				printf("Mais velho:");
				imprime_jog((TJ*)TLSE_get(Q1, 1));
	            TLSE_libera(Q1);
			}

			printf("\n--------------------------------------------------------------------------\n");
		}
		
		else if(opcao == 2){
            char *Q2 = malloc(sizeof(char)*50);
			Q2 = escolhe_selecao(Q2);
			TJ J3, J4;
			mais_e_menos_selecao(raiz, t, selecoes, Q2, &J3, &J4);
			
    		imprime_jog(&J3);
			imprime_jog(&J4);
            free(Q2);
			printf("\n--------------------------------------------------------------------------\n");

		}
		
		else if(opcao == 3){

			TJ* J5 = (TJ *) malloc(sizeof(TJ));
            J5->n_partidas = INT_MIN;
            TJ* J6 = (TJ *) malloc(sizeof(TJ));
            J6->n_partidas = INT_MAX;
            
			mais_e_menos_atuaram_total(raiz, t, J5, J6);
			
			printf("Mais atuou:");
			imprime_jog(J5);
            free(J5);
			printf("Menos atuou:");
			imprime_jog(J6);
            free(J6);
 
			printf("\n--------------------------------------------------------------------------\n");
		}
		
		else if(opcao == 4){
			char* menor = menor_selecao(selecoes);
			char* maior = maior_selecao(selecoes);
	
			printf("Menor: %s\n", menor);
			printf("\nMaior: %s", maior);
	
			free(menor);
			free(maior);
		}
		
		else if(opcao == 5){
			TLSE* l1 = jogadores_fora_do_pais_de_origem(raiz, t);
	
			TLSE_imp(l1, func);
			free(l1);
		}
		
		else if(opcao == 6){
			TLSE* l2 = jogadores_no_pais_de_origem(raiz, t);
	
			TLSE_imp(l2, func);
			free(l2);
		}
		
		else if(opcao == 7){
			int anoQ7;
			
			printf("\nDigite um ano: ");
			scanf("%d", &anoQ7);
			
			TLSE* l3 = jogadores_do_mesmo_ano(raiz, t, anoQ7);
	
			TLSE_imp(l3, func);
			free(l3);
		}
		
		else if(opcao == 8){
			int mesQ8;
			
			printf("\nDigite um mês: ");
			scanf("%d", &mesQ8);
			
			TLSE* l4 = jogadores_do_mesmo_mes(raiz, t, mesQ8);
	
			TLSE_imp(l4, func);
			free(l4);
		}
		
		else if(opcao == 9){
            char* s9 = selecao_com_mais_jogadores_fora_do_pais(raiz, t);
            printf("\n%s\n", s9);
            free(s9);
		}
		
		else if(opcao == 10){
            char* s10 = selecao_com_mais_jogadores_do_pais_de_origem(raiz, t);
            printf("\n%s\n", s10);
            free(s10);
		}
		
		else if(opcao == 11){
			int id;
			printf("Digite o id do jogador: ");
			scanf("%d", &id);

			TJ *jog = busca_jog(raiz, t, id);
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
				printf("Opção inválida!\n");
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
			scanf("%d", &idade);
			raiz = remove_jogadores_pela_idade(raiz, t, idade);
			imprime(raiz, t);
		}
		
		else if(opcao == 16){
			printf("Escolha a seleção: \n");
			char *sel1 = malloc(sizeof(char)*50);
			sel1 = escolhe_selecao(sel1);
			printf("Escolha o país de atuação: \n");
			char *sel2 = malloc(sizeof(char)*50);
			scanf("%s", sel2);
			raiz = retira_jog_selecao_pais(raiz, selecoes, sel1, sel2, t);
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
			int *id20 = (int*)malloc(sizeof(int));
			printf("Insira um id, insira -1 para parar: \n");
			scanf("%d", id20);
			
			TLSE* l20 = TLSE_cria(id20); 
			
			while((*id20)!=-1){
				id20 = (int*)malloc(sizeof(int));
				printf("Insira um id, insira -1 para parar: \n");
				scanf("%d", id20);
				l20 = TLSE_insini(l20, id20);
			}
			
			raiz = remocao_por_chaves(raiz, t, l20);
			imprime(raiz, t);
			TLSE_libera(l20);

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
	}
    return 0;
}