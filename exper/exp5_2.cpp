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