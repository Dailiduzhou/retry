#include<bits/stdc++.h>
using namespace std;
int main() {
    char a[5];
    for (int i = 0;i<5;++i){
        char c;
        scanf("%c", &c);
        a[i] = c;
    }
    for (int i=0,j=4;i<j;++i,--j){
        if (a[i] == a[j]){
            continue;
        } else {
            printf("No");
            return 0;
        }
    }
    printf("Yes");
    return 0;
}