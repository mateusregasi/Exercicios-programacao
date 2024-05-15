#include <stdio.h>

<<<<<<< HEAD
int res(int n, int k){
    if(n == 1) return 0;
    return (res(n - 1, k) + k) % n;
=======
int f(int n, int k){
    if(n == 1) return 1;
    return (f(n-1, k) + k-1) % n + 1;   
>>>>>>> 1ed5de3e6fa52ba3c1f98314ae412aa680e3844d
}


int main(void){

    int n, m, r;
    scanf("%d", &n);
    while(n != 0){
        m = 1;
        while(1){
            r = f(n-1, m)+1;
            if(r == 13) break;
            m++;
        }
        printf("%d\n", m);

        scanf("%d", &n);
    }
    return 0;
}