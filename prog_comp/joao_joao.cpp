// https://codeforces.com/gym/106073/problem/J
#include <iostream>
#include <set>
using namespace std;

int main(){
    int aux;
    set<int> conj;
    for(int i=0; i<10; i++){
        scanf("%d", &aux);
        conj.insert(aux);
    }
    printf("%d\n", 4-conj.size());
    return 0;
}

// 1 3 4 1 3 4 1 3 4 1
// 4 1 1 4 3 1 2 1 2 2
