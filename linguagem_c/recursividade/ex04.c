// https://judge.beecrowd.com/pt/problems/view/1252

#include <stdio.h>
#include <stdlib.h>

int cmp(int n1, int n2, int m){
    int modn1 = n1 % m,
        modn2 = n2 % m;

    // Caso haja empate
    if(modn1 == modn2){
        int parn1 = (n1 % 2 == 0) ? 1 : 0,
            parn2 = (n2 % 2 == 0) ? 1 : 0;

        if((!parn1) && (!parn2)) 
            return (n1 < n2) ? 1 : -1;

        if((parn1) && (parn2))
            return (n1 < n2) ? -1 : 1;
        
        return (!parn1) ? -1 : 1;
    }

    // Caso não haja empate
    return modn1 - modn2;
}

// void selection_sort(int *vet, int n, int m){
//     if(n == 1) return;

//     int menor = 0;
//     for(int i=0; i<n; i++){
//         if(cmp(vet[menor], vet[i], m) > 0)
//             menor = i;
//     }
//     if(menor != vet[0]){
//         int t = vet[0];
//         vet[0] = vet[menor];
//         vet[menor] = t;
//     }

//     selection_sort(&vet[1], n-1, m);
// }

// void quick_sort(int *vet, int n, int m){
//   if(n <= 1) return;
//   int x = vet[0], a = 1, b = n - 1;
//   do{
//      while((a < n) && (cmp(vet[a], x, m) <= 0 )) a++;
//      while(cmp(vet[b], x, m) > 0) b--;
//      if(a < b){
//        int temp = vet[a];
//        vet[a++] = vet[b];
//        vet[b--] = temp;
//      }
//   } while(a <= b);
//   vet[0] = vet[b];
//   vet[b] = x;
//   quick_sort(vet, b,m);
//   quick_sort(&vet[b+1], n - b - 1, m);
// }

int main(void) {

    // Entrada de dados
    int n = 1, m = 1;

    while(n && m){
        scanf("%d %d", &n, &m);
        int *vet = (int *) malloc(sizeof(int) * n);
        for(int i=0; i<n; i++)
            scanf("%d", &vet[i]);

        // Chama a função de ordenação
        selection_sort(vet, n, m);
        // quick_sort(vet, n, m);
        // qsort_r(vet, n, sizeof(int), cmp, m);

        // Printa o vetor
        printf("\n%d %d\n", n, m);
        for(int i=0; i<n; i++)
        printf("%d\n", vet[i]);
    }
  
    return 0;
}

// 15 3
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 10
// 11
// 12
// 13
// 14
// 15
// 3 3
// 9
// 12
// 10
// 0 0

// 15 3
// 15
// 9
// 3
// 6
// 12
// 13
// 7
// 1
// 4
// 10
// 11
// 5
// 2
// 8
// 14
// 3 3
// 9
// 12
// 10
// 0 0