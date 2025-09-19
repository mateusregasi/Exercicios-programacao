// https://codeforces.com/gym/106073/problem/A
#include <iostream>
using namespace std;

int main(){
    int n, m, aux;
    scanf("%d %d", &n, &m);

    int vet[m];
    for(int j=0; j<m; j++){
            scanf("%d", &aux);
            vet[j] = aux;
        }
    for(int i=1; i<n; i++)
        for(int j=0; j<m; j++){
            scanf("%d", &aux);
            if(aux > vet[j]) vet[j] = aux;
        }
    aux = vet[0];
    for(int i=1; i<m; i++)
        aux += vet[i];

    printf("%d\n", aux);
    return 0; 
}

// 3 3
// 20 15 14
// 12 20 12
// 18 5 10

// 2 3
// 5 2 4
// 4 3 6