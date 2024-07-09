// https://www.beecrowd.com.br/repository/UOJ_1285.html

#include <stdio.h>

int procura(int n, int d){

    // Se n for igual a 0 retorna falso
    if(n == 0) return 0;

    // Se o dígito que queremos verificar for igual ao 
    // dígito mais a direita de n retorna verdadeiro 
    if(d == n % 10) return 1;

    // Se não vai para o próximo valor 
    return procura(n/10, d);
}
int tem_repeticao(int n){

    // Se o número for menor que 10 retorna que não tem repetição
    if(n < 10) return 0;

    int d, r;
    // Pega o caractere mais a direita
    d = n % 10;
    n = n / 10;

    // Verifica se o número mais a direita se repete
    // Se sim tem repetição
    r = procura(n, d);
    if(r) return 1;

    // Se não retorna a próxima iteração
    return tem_repeticao(n);
}

int main(void){
    int m, n, c;

    // Entrada de dados
    while(scanf("%d %d", &n, &m) != EOF){
        c = 0;

        // Processamento
        for(int i=n; i<=m; i++)
            c += tem_repeticao(i) ? 0 : 1;

        // Saída de dados
        printf("%d\n", c);

        // Entrada de dados
        scanf("%d %d", &n, &m);
    }

    return 0;
}

// 87 104
// 989 1022
// 22 25
// 1234 1234

// 14
// 0
// 3
// 1