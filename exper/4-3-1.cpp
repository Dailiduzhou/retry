#include<stdio.h>
int main() {
    int a,b,c,d;
    scanf("%1X%1X%1X%1X",&a,&b,&c,&d);
    printf("%X", (d|c|b|a));
}