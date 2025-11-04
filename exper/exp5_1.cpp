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