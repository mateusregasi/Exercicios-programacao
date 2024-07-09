#include "TABMJ.c"

//////////////////////////////////////////////////////////////////////////////////////////////

// Lê uma linha do arquivo "EURO.txt" e passa adequadamente para a tabela 
// Passa todas as informações do arquivo "EURO.txt" para a tabela
// Lê a informação requisitada da tabela e retorna um vetor (atualiza um contador externo)
// Substitui um ID da tabela pelo valor "-1"

void le_registro2tabela_selecoes(TJ *j, FILE *f, FILE *s, int* contador, int* pulo);
void arq2tabela_selecoes(char *nome, char *tabela);
int* le_tabela_selecao(char *tabela, char *selecao, int* c);
void retira_tabela_selecao(char *tabela, int num);

void le_registro2tabela_posicoes(TJ *j, FILE *f, FILE *s, int* contador, char *pos);
void arq2tabela_posicoes(char *nome, char *tabela);
int* le_tabela_posicao(char *tabela, char *pos, int* c);
void retira_tabela_posicao(char *tabela, int num);

//////////////////////////////////////////////////////////////////////////////////////////////

void le_registro2tabela_selecoes(TJ *j, FILE *f, FILE *s, int* contador, int* pulo){
    char l[100], *linha;

    fgets(l, 100, f);
    linha = l;

	// Se não é o registro de um jogador:
    if(!strchr(linha, '/')){
		if(!strchr(linha, '.')){
			
			// Caso não seja a primeira iteração:
			if((*contador)){
				
				// Volta para o contador da seleção anterior e reescrevo 
				fseek(s, (*pulo), SEEK_SET);
				fwrite(contador, sizeof(int), 1, s);
				
				// Atualizo os valores e ponteiros
				(*pulo) += (sizeof(int)*((*contador)+1)) + (sizeof(char)*20);
				(*contador) = 0;
				
				fseek(s, 0, SEEK_END);
			}
			
			// Escrevo o pais e seu contador (zerado)
			fwrite(linha, (sizeof(char)*20), 1, s);
			fwrite(contador, sizeof(int), 1, s);
		}
		return;
	}
	
	// Escrevo o id do jogador
    sscanf(l, "%d",  &j->id);
	fwrite(&j->id, sizeof(int), 1, s);
	
	// Atualizo o contador
	(*contador)++;
	return;
}

void arq2tabela_selecoes(char *nome, char *tabela){
	
	// Inicializo o contador e pulo que serão usados no "le_registro2tabela_selecoes"
	int contador = 0;
	int pulo = sizeof(char)*20;

	// Abro os arquivos
    FILE *f = fopen(nome, "r");
    if(!f) exit(1);
	
    FILE *t = fopen(tabela, "wb+");
    if(!t) exit(1);

	TJ *j = (TJ *) malloc(sizeof(TJ));
	
	// Leio as linhas do arquivo "EURO.txt" até que ele acabe
    while(!feof(f)){
		le_registro2tabela_selecoes(j, f, t, &contador, &pulo);
    }
	
	// CORREÇÃO PARA A ÚLTIMA SELEÇÃO LIDA //
	fseek(t, pulo, SEEK_SET);
	fwrite(&contador, sizeof(int), 1, t);
	
	// Atualizo os valores e ponteiros
	pulo += (sizeof(int)*(contador+1)) + (sizeof(char)*20);
	contador = 0;
	
	fseek(t, 0, SEEK_END);
	/////////////////////////////////////////

	free(j);
    fclose(f);
	fclose(t);
}

int* le_tabela_selecao(char *tabela, char *selecao, int* c){
	char pais[20];
	int contador;
	int *ids;
	
	char* s = (char*)malloc(sizeof(char)*20);
	strcpy(s, selecao);
	strcat(s, "\n");
	
    FILE *t = fopen(tabela, "rb");
    if(!t) exit(1);
	
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){

		// Leio os valores da tabela
		fread(&pais, sizeof(char), 20, t);
		fread(&contador, sizeof(int), 1, t);
		ids = (int*)malloc(sizeof(int)*contador);
		for(int i = 0; i<contador; i++) fread(&ids[i], sizeof(int), 1, t);
		
		// Se não for a seleção requisitada, passo para próxima, se sim, retorno.
		if(strcmp(pais, s)) free(ids);
		else break;
		
	}
	
	// Se não encontrei a seleção requisitada, retorno nulo 
	if((feof(t)) && (strcmp(pais, s))){
		fclose(t);
		(*c) = 0;
		return NULL;
	}
	
	// Retorno a lista de IDs da seleção requisitada
	fclose(t);
	(*c) = contador;
	return ids;
}

void retira_tabela_selecao(char *tabela, int num){
	char pais[20];
	int contador;
	int pulo;
	
	// O valor -1 é escolhido para representar IDs que não existem mais.
	int del = -1;
	int id;
	
    FILE *t = fopen(tabela, "rb+");
    if(!t) exit(1);
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){
		
		// Leio os valores da tabela
		fread(&pais, sizeof(char), 20, t);
		fread(&contador, sizeof(int), 1, t);
		
		for(int i = 0; i<contador; i++){
			fread(&id, sizeof(int), 1, t);
			
			// Se encontro o ID requisitado
			if(id==num){
				
				
				// Reescrevo ele como "-1"
				pulo = (ftell(t)-sizeof(int));
				fseek(t, pulo, SEEK_SET);
				fwrite(&del, sizeof(int), 1, t);
				fclose(t);
				return;
				
			}
		}
	}

	fclose(t);
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void le_registro2tabela_posicoes(TJ *j, FILE *f, FILE *s, int* contador, char *pos){
	char l[100], *linha;

    fgets(l, 100, f);
    linha = l;

	// Se não é o registro de um jogador:
    if (!strchr(linha, '/')) return;
	
	// Escrevo o id do jogador se ele for da posição requisitada
    sscanf(l, "%d/%d/",  &j->id, &j->camisa);
    for(int i=0; i<2; i++){
        linha = strchr(linha, '/');
        linha++;
    }
	
    linha = le_string(linha, j->posicao, '/');
	if (!strcmp(j->posicao, pos)){
		fwrite(&j->id, sizeof(int), 1, s);
		
		// Atualizo o contador
		(*contador)++;
	}
	
	return;
}

void arq2tabela_posicoes(char *nome, char *tabela){
	
	// Inicializo o contador e pulo que serão usados no "le_registro2tabela_posicoes"
	int contador = 0;
	int pulo = sizeof(char)*3;
	
	char* pos[4] = {"GK", "DF", "MF", "FW"};

	// Abro os arquivos
    FILE *f = fopen(nome, "r");
    if(!f) exit(1);
	
    FILE *t = fopen(tabela, "wb+");
    if(!t) exit(1);

	TJ *j = (TJ *) malloc(sizeof(TJ));
	
	for (int i = 0; i<4; i++){
		
		// Escrevo a posição e inicio o contador no arquivo
		fwrite(pos[i], (sizeof(char)*3), 1, t);
		fwrite(&contador, sizeof(int), 1, t);
		
		// Leio as linhas do arquivo "EURO.txt" até que ele acabe
		while(!feof(f)){
			le_registro2tabela_posicoes(j, f, t, &contador, pos[i]);
		}
		
		// Atualizo o contador no arquivo (tabela)
		fseek(t, pulo, SEEK_SET);
		fwrite(&contador, sizeof(int), 1, t);
		pulo += (sizeof(char)*3) + (sizeof(int)*(contador+1));
		contador = 0;
		fseek(t, 0, SEEK_END);
		
		
		fseek(f, 0, SEEK_SET);
	}

	free(j);
    fclose(f);
	fclose(t);
}

int* le_tabela_posicao(char *tabela, char *pos, int* c){
	char p[3];
	int contador;
	int *ids;
	
    FILE *t = fopen(tabela, "rb");
    if(!t) exit(1);
	
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){

		// Leio os valores da tabela
		fread(&p, sizeof(char), 3, t);
		fread(&contador, sizeof(int), 1, t);
		ids = (int*)malloc(sizeof(int)*contador);
		for(int i = 0; i<contador; i++) fread(&ids[i], sizeof(int), 1, t);
		
		// Se não for a posição requisitada, passo para próxima, se sim, retorno.
		if(strcmp(p, pos)) free(ids);
		else break;
		
	}
	
	// Se não encontrei a posição requisitada, retorno nulo 
	if((feof(t)) && (strcmp(p, pos))){
		fclose(t);
		(*c) = 0;
		return NULL;
	}
	
	// Retorno a lista de IDs da seleção requisitada
	fclose(t);
	(*c) = contador;
	return ids;
}

void retira_tabela_posicao(char *tabela, int num){
	char pos[3];
	int contador;
	int pulo;
	
	// O valor -1 é escolhido para representar IDs que não existem mais.
	int del = -1;
	int id;
	
    FILE *t = fopen(tabela, "rb+");
    if(!t) exit(1);
	
	// Enquanto o arquivo não termina:
	while(!feof(t)){
		
		// Leio os valores da tabela
		fread(&pos, sizeof(char), 3, t);
		fread(&contador, sizeof(int), 1, t);
		
		for(int i = 0; i<contador; i++){
			fread(&id, sizeof(int), 1, t);
			
			// Se encontro o ID requisitado
			if(id==num){
				
				
				// Reescrevo ele como "-1"
				pulo = (ftell(t)-sizeof(int));
				fseek(t, pulo, SEEK_SET);
				fwrite(&del, sizeof(int), 1, t);
				fclose(t);
				return;
				
			}
		}
	}

	fclose(t);
	return;
}