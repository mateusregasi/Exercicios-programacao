#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// (Q1) Desenvolva um procedimento que receba o nome de um arquivo texto e retire deste texto palavras consecutivas repetidas. O seu programa deve retornar, no arquivo de saída, informado como parâmetro dessa função, a resposta desta questão. Por exemplo, se o conteúdo de um arquivo texto for: "Isto e um texto texto repetido repetido repetido . Com as repeticoes repeticoes fica fica sem sem sentido . Sem elas elas elas melhora melhora um um pouco .", a saída do seu programa será um arquivo com o seguinte texto: "Isto e um texto repetido . Com as repeticoes fica sem sentido . Sem elas melhora um um pouco ." - 

// void RetRepet(char *ArqEnt, char *ArqSaida).

// Função auxiliares
void imp_palavra_arq(char *palavra, FILE *f);
char *get_palavra(FILE *f);
void imp_arq(char *nome);

// Função do exercício
void ret_rep(char *arq_ent, char *arq_saida);

int main(void){

    // Imprime o arquivo inicial
    printf("O arquivo inicialmente está assim:\n\n");
    imp_arq("arqex01.1");

    // Aplica a função e imprime
    printf("\n\nApós aplicar a função fica assim:\n\n");
    ret_rep("arqex01.1", "arqex01.2");
    imp_arq("arqex01.2");

    return 0;
}

// Funções auxiliares
void imp_palavra_arq(char *palavra, FILE *f){
    fputs(palavra, f);
    fputc(' ', f);
}
char *get_palavra(FILE *f){

    // i = inicio da palavra e j = espaço a frente do fim da palavra
    long int i, j;
    int n;
    char c;

    // Procura o início da palavra
    while((c = getc(f)) == ' ');
    fseek(f, -1l, SEEK_CUR);
    i = ftell(f);

    // Se o início da palavra não existir, quer dizer que o arquivo acabou
    if(c == EOF) return NULL;

    // Procura o final da palavra
    while(((c = getc(f)) != ' ') && (c != EOF));
    if(c != EOF) fseek(f, -1l, SEEK_CUR);
    j = ftell(f);

    // Conta a quantidade de caracteres na palavra
    n = j - i + 1;

    // Aloca espaço na reap
    char *palavra = (char *) malloc(sizeof(char) * n);

    // Lê a palavra
    fseek(f, i, SEEK_SET);
    fgets(palavra, n, f);

    return palavra;
}
void imp_arq(char *nome){
    FILE *f = fopen(nome, "r");
    char c;
    while(!feof(f)){
        c = getc(f);
        if(c != EOF)
            printf("%c", c);
    }
    fclose(f);
}

// Função do exercício
void ret_rep(char *arq_ent, char *arq_saida){

    // Abre os dois arquivos
    FILE *fw = fopen(arq_saida, "w"),
         *fr = fopen(arq_ent, "r");

    // Pega a primeira palavra no arquivo de entrada, se não tiver palavras no arquivo, sai
    char *anterior = get_palavra(fr), *atual = (char *) 1;
    if(!anterior) return;                       
    imp_palavra_arq(anterior, fw);

    // Enquanto existir palavras
    while(atual){

        // Pega a palavra atual
        atual = get_palavra(fr);

        // Se a palavra existir 
        if(atual){

            // Se as palavras forem diferentes, adiciona no arquivo de escrita
            if(strcmp(anterior, atual))
                imp_palavra_arq(atual, fw);
        }
       
        // Apaga a anterior e troca pela atual
        free(anterior);
        anterior = atual;
    }
    free(atual);

    // Fecha os dois arquivos
    fclose(fr);
    fclose(fw);
}