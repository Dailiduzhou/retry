#include<bits/stdc++.h>
using namespace std;
int dfs(int x){
    if (x==1) return 1;
    return x * dfs(x-1);
}
int main(){
    int n;
    cin>>n;
    cout<<dfs(n);
}