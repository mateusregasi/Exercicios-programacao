// (a) Implemente o tipo abstrato de dados lista simplesmente encadeada genérica, usando void *.
// (b) Dada a seguinte representação de uma árvore binária:
// typedef struct ab{
//     int info;
//     struct ab *esq, *dir;
// } TAB;

typedef struct node{
    void *dado;
    struct node *prox;
} NO;
typedef struct ab{
    int info;
    struct ab *esq, *dir;
} TAB;


// (Q7) se esta estrutura TAB tivesse um campo cor (int cor), defina uma função em C que, ao
// receber uma árvore binária “sem cor” e totalmente balanceada (isto é, a distância da raiz a qualquer
// folha da árvore é sempre a mesma), retorne esta árvore com os nós coloridos somente de vermelho e
// preto, sendo que o nó pai NUNCA pode ter a mesma cor de seus filhos. A função deve possuir o
// seguinte protótipo: void colore (TAB* arv);
