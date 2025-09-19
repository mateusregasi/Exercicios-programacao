// https://codeforces.com/gym/106073/problem/I
#include <stdio.h>
#include <cmath>
using namespace std;

#define dist max(abs(x - x1), abs(y - y1))

void falhar(){
    printf("-1\n");
    exit(0);
}

int main(){
    int n, f = 0;
    scanf("%d", &n);
    int x, x1, y, y1;
    scanf("%d %d", &x, &y);
    scanf("%d %d", &x1, &y1);

    // Calcula a primeira distância, se for menor que 2 falha
    int distancias[n-1];
    distancias[0] = dist;
    if(distancias[0] < 2) falhar();
    x = x1; y = y1;

    // Lê o vetor de distâncias
    for(int i=1; i<n-1; i++){
        scanf("%d %d", &x1, &y1);
        distancias[i] = dist;
        x = x1; y = y1;

        // Se uma distância consecutiva for maior que o dobro ou menor que 2 falha
        if(distancias[i-1] * 2 < distancias[i] || distancias[i-1] < distancias[i] * 2 || distancias[i] < 2){
            f = 1;
            break;
        }
    }
    if(f) falhar();

    // Acha os limites levando em consideração que:
    // 1) O raio da primeira órbita afeta os demais
    // 2) Raios de órbitas pares sobem 1 quando diminui 1 no raio inicial
    // 3) Raios de órbitas ímpares diminuem 1 quando diminui 1 no raio inicial
    int limsup = distancias[0] - 1, limite = std::numeric_limits<int>::max(), aux, raio;
    raio = limsup;

    for(int ri=limsup; ri>ri-limite; ri--){
        f = 1;
        raio = ri;
        for(int i=0; i<n-1; i++){
            raio = distancias[i] - raio; // Raio i+1
            if(raio < 1 || ((i < n-2) && (raio >= distancias[i+1]))){
                f = 0;
                break;
            }
            
            // Calcula o limite
            if(raio % 2 == 1){ // Quando sobe não pode passar da distância -1
                aux = distancias[i] - 1 - raio;
                if(aux < limite) limite = aux;
            } else{ // Quando desce não pode passar de 1
                aux = raio - 1;
                if(aux < limite) limite = aux;
            }
        }
        if(f){
            printf("%d\n", ri);
            exit(0);
        }
    }
    falhar();
    return 0;
}




// 3
// 0 0
// 4 0
// 4 4

// 3

// 5
// 0 0
// 4 0
// 4 2
// 4 6
// 6 6

// -1

// 4
// 0 0
// 4 0
// 4 4
// 4 7

// 2