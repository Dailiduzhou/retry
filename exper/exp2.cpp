#include<stdio.h>
#include<iostream>

int main(){
    long a,res;
    unsigned long b,c;
    scanf("%lx", &a);
    b= a & 0xFFFF;
    c= (a<<16);
    res= (b<<16) | c;
    printf("%lx", res);
    return 0;
}