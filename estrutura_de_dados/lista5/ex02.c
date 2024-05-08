#include <stdio.h>
#include <stdlib.h>

// (Q2) Implemente um algoritmo que receba como parâmetro de entrada, o nome de um arquivo
// texto, cujo conteúdo são o nome do aluno e as duas notas dos alunos do curso, uma em cada linha, e
// que ordene o arquivo de saída em ordem crescente pela média do aluno. Isto é, se eu tiver como
// entrada o arquivo: "P C/10.0/10.0-J J/3.0/4.0-G G/7.0/7.0-A A/0.5/1.5-I I/5.0/6.0", a
// saída será um arquivo com o seguinte texto: "A A/1.0-J J/3.5-I I/5.5-G G/7.0-P C/10.0" -
// void media(char *ArqEnt, char *ArqSaida).

typedef struct registro{
    char *nome;
    float n1, n2;
} REG;
typedef struct node{
    REG *reg;
    struct node *prox;
} NO;

// Funções auxiliares
char *get_nome(FILE *f);
float get_nota(FILE *f);
REG *get_registro(FILE *f);
void imp_reg(REG *reg);
void imp_reg(REG *reg);
NO *add(NO *no, REG *reg);
NO *arq_reg2lista_reg(FILE *f);
void imp_lista_reg(NO *n);
float cmed(REG *reg);
void ord_lista_reg_med(NO *n);

// Função do exercício
void media(char *f1, char *f2);

int main(void){
    media("arqex02.1", "arqex02.2");
    return 0;
}

// Funções auxiliares
char *get_nome(FILE *f){
    char c, *nome;
    int i, j, n;

    // Acha i e j
    i = ftell(f);
    while((c = getc(f)) != '/');
    j = ftell(f);

    // Aloca a string
    n = j - i;
    nome = (char *) malloc(sizeof(char *) * (n + 1));

    // Colhe a string
    fseek(f, i, SEEK_SET);
    fgets(nome, n+1, f);
    nome[n-1] = '\0';

    return nome;
}
float get_nota(FILE *f){
    float nota;
    fscanf(f, "%f", &nota);
    getc(f);
    return nota;
}
REG *get_registro(FILE *f){

    // Verifica se chegou no EOF
    if(feof(f)) return NULL;
        
    // Aloca e colhe o registro
    REG *reg = (REG *) malloc(sizeof(REG));
    reg->nome = get_nome(f);
    reg->n1 = get_nota(f);
    reg->n2 = get_nota(f);

    // Retorna o registro
    return reg;
}
void imp_reg(REG *reg){
    printf("%s %.1f %.1f\n", reg->nome, reg->n1, reg->n2);
}
NO *add(NO *no, REG *reg){
    NO *add = (NO *) malloc(sizeof(NO));
    add->reg = reg;
    add->prox = NULL;

    if(!no) return add;
    NO *a;
    for(a=no; a->prox; a = a->prox);
    a->prox = add;
    return no;
}
NO *arq_reg2lista_reg(FILE *f){
    NO *lista = NULL;
    REG *reg = get_registro(f);
    while(reg){
        lista = add(lista, reg);
        reg = get_registro(f);
    }
    return lista;
}
void imp_lista_reg(NO *n){
    if(!n) return;
    while(n){
        imp_reg(n->reg);
        n = n->prox;
    }
}
float cmed(REG *reg){
    return (reg->n1 + reg->n2)/2;
}
void ord_lista_reg_med(NO *n){
    NO *i, *j, *menor;
    for(i=n; i; i = i->prox){
        menor = i;
        for(j=i; j; j = j->prox)
            if(cmed(menor->reg) > cmed(j->reg)) menor = j;
        if(menor != i){
            REG *t = menor->reg;
            menor->reg = i->reg;
            i->reg = t;
        }
    }
}
void destroi_lista(NO *lista){
    while(lista){
        NO *r = lista;
        lista = r->prox;
        free(r->reg);
        free(r);
    }
}

// Função do exercício
void media(char *f1, char *f2){
    FILE *fr = fopen(f1, "r"),
         *fw = fopen(f2, "w");
    
    // Coloca os registros em uma lista
    NO *lista = arq_reg2lista_reg(fr);

    // Ordena a lista
    ord_lista_reg_med(lista);

    // Põe a lista no arquivo
    for(NO *i=lista; i; i=i->prox){
        fprintf(fw, "%s/%.1f", i->reg->nome, cmed(i->reg));
        if(i->prox) fprintf(fw, "-");
    }

    // Apaga os registros e a lista
    destroi_lista(lista);

    // Fecha os arquivos
    fclose(fr);
    fclose(fw);
}