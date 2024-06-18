// Lista
typedef struct node{
    void *dado;
    struct node *prox;
} NO;

typedef void impf(void *e);

// Cria um nó
NO *cria(void *e){
    NO *n = (NO *) malloc(sizeof(NO));
    n->prox = 0;
    n->dado = e;
    return n;
}

// Adiciona elemento na lista
NO *insini(NO *n, void *e){
    NO *novo = cria(e);
    novo->prox = n;
    return novo;
}

// Imprime os elementos da lista de acordo com uma função
void imp(NO *a, impf *f){
    while(a){
        f(a->dado);
        a = a->prox;
    }
}