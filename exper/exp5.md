``` cpp
// exp5_1.cpp
#include<iostream>
using namespace std;

int main(){
    int a, sum =0;
    scanf("%d", &a);
    int num[a];

    for (int i=1;;i += 2){
        for (int j = 0;j<a; j++) {
            sum += i + 2*j;
            num[j] = i + 2*j;
        }
        if (sum == a*a*a)
            break;
        sum=0;
    }
    
    printf("%d^3 = ", a);
    for (int i = 0; i<a-1; i++){
        printf("%d + ", num[i]);
    }
    printf("%d", num[a-1]);
}
```
---
``` cpp
// exp5_2.cpp
#include<iostream>
#include<math.h>
using namespace std;

int main(){
    int sum =0;
    int lvl = 0;
    for (int i=1;i<1001;++i){
        int a;
        int b;
        b = i;
        while (b){
            b/=10;
            lvl++;
        }
        b=i;
        while (b){
            a = b%10;
            b /= 10;
            sum += pow(a,3); // by difinition, is pow(a, lvl);
        }
        if (sum == i){
            printf("%d\n", i);
        }
        sum =0;
        lvl = 0;
    }
}
```