// https://codeforces.com/gym/106073/problem/C
#include <iostream>
#include <deque>
using namespace std;

int main(){
    int n, c=0;
    scanf("%d", &n);
    deque<int> vec(n+1);
    for(int i=n; i>=0; i--) 
        scanf("%d", &vec[i]);

    while(vec.size() > 1){
        if(vec[0]){
            for(int i=vec.size()-1; i>=0; i--){
                if(vec[i]){
                    if(i == vec.size()-1){
                        vec.push_back(1);
                    } else{
                        vec[i+1] = vec[i+1] ? 0 : 1;
                    }
                }
            }
            vec[0] = vec[0] ? 0 : 1;
        } else{
            vec.pop_front();
        }
        c++;
    }

    printf("%d\n", c);
    return 0;
}

// 3
// 1 0 0 1

// 2
// 1 0 1

// 2
// 1 0 0