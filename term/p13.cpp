#include<stdio.h>
#include<stdlib.h>

int gcd(int x, int y){
    if (x == y){
        return x;
    }
    if (x>y){
        return gcd(x-y, y);
    } else {
        return gcd(x, y-x);
    }
}

int main(){
    int m,n;
    scanf("%d%d", &m,&n);

    printf("\ngcd=%d", gcd(m,n));
}