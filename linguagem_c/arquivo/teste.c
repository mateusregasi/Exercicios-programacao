#include <stdio.h>

int main(void){

    // Abertura de arquivo
    FILE *f = fopen("nome", "w");
    // r (read) -> leitura (se o arquivo não existir returna null)
    // w (write) -> escrita/leitura (abre no início do arquivo) (se o arquivo não existir ele cria)
    // a (append) -> escrita/leitura (abre no final do arquivo) (se o arquivo não existir ele cria)
    // + -> r+ -> leitura e alterar posição
    // b -> binário 
    // r w a r+ (w+ a+) rb wb ab

    // Fechamento de arquivo
    fclose(f);

    // Excluir o arquivo
    remove("nome");

    // Renomear o arqvuivo
    rename("nome", "novo_nome");

    // EOF -> constante do final do arquivo
    // fscanf(cursor, "%seletor", &variável): lê igual o scanf a partir do cursor
    // fgets(endereço variável, n, arquivo): 


    // feof(cursor); retorna 1 se tiver chegado no final do arquivo

    return 0;
}


// FUNÇÕES QUE A GENTE NÃO VIU MAS EXISTEM
// fprintf 

// fgets(endereço_variável, quant_max_caracteres, cursor): significa **file get string**. Lê a entrada dada pelo teclado do usuário ou por meio de um arquivo. 
// fputs(string, cursor): significa **file put string**. Pega uma string e imprime a partir da posição do cursor. 
// fwrite(endereço_entrada, tamanho_elemento, n, cursor)`: lê os primeiros n índices de um vetor e joga em um arquivo.

// `fread(endereço_saída, tamanho_elemento, n, cursor)`: lê os primeiros n bytes de um arquivo e joga em uma variável.
// `fseek(cursor, offset, origem)`: aponta o ponteiro para uma posição do arquivo.
// `origem`: a origem é onde inicialmente será apontado o cursor 
// - `SEEK_SET`: início
// - `SEEK_END`: fim
// - `SEEK_CUR`: atual (onde o cursor já está)
// `offset`: vai ser o pulo de bytes que o cursor vai fazer após a origem.
// `ftell(cursor)`: passa o endereço do cursor relativo ao arquivo (dentro do arquivo)
// `rewind(cursor)`: volta o ponteiro para o início do arquivo