#include<bits/stdc++.h>
using namespace std;
int n;
int factorial(int y){
    if (y==1) return 1;
    return y*factorial(y-1);
}

int dfs(int x){
    if (x==1) return 1;
    return factorial(2*x)/factorial(x)/factorial(x) / (x+1);
}

int main(){
    scanf("%d", &n);
    printf("%d\n", dfs(n));
}