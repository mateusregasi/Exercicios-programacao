#include <stdio.h>

int res(int n, int k){
    if(n == 1) return 0;
    int w = (res(n - 1, k) + k) % n;
    return w;
}

int main(void){

    int n, r, i;
    scanf("%d", &n);
    while(n != 0){
        for(i=1; i<n-1; i++){
            r = res(n-1, i)+2;
            if(r == 13) break;
        }
        printf("%d\n", i);

        scanf("%d", &n);
    }
    return 0;
}


// #include <stdio.h>

// int Crise (int n, int k) {
//     if (n == 1)
//         return 1;
    
//     return (Crise(n - 1, k) + k - 2) % (n - 1) + 1;
// }

// int main (void) {
//     int g, n, c, i;

//     scanf("%d", &g);
//     while(g != 0) {
//         i = g;
//         while (Crise(g, i) != 13){
//             i--;
//         }
//         printf("%d\n", i);
//         scanf("%d", &g);
//     }
//     return 0;
// }