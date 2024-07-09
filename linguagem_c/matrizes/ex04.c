
// https://judge.beecrowd.com/pt/problems/view/1190

#include <stdio.h>
 
int main() {
    
    // Le a opcao
    char op;
    scanf("%c", &op);
    
    // Acumulador e somador
    float s = 0;
    
    // Le a matriz
    int l;
    for(int i=0; i<12; i++){
        
        // Calcula a parte verde de acordo com i
        int aux = (i < 6) ? i : 11 - i;
            
        // Desconta a parte verde do total pra servir de auxiliar pro j 
        aux = 11 - aux;
        
        for(int j=0; j<12; j++){
            
            // Le o dado (nao guardamos a matriz porque pra essa questao nao precisa)
            scanf("%f", &l);
            
            // Usa o aux pra auxilidar a condiçao do somador
            if(j > aux) s += l;
        }
    }
    
    // Imprime a informaçao
    if(op == 'S') printf("%.1f\n", s);
    else if(op == 'M') printf("%.1f\n", s / 144.0);
 
    return 0;
}