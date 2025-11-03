#include<bits/stdc++.h>
using namespace std;
int n, ans=0x7fffffff;
int a[15],b[15];
void dfs(int i,int x,int y){
    if (i>n){
        if (x==1 && y==0) return;
        ans = min(abs(x-y),ans);
        return;
    }

    dfs(i+1,x*a[i],y+b[i]);
    dfs(i+1,x,y);
}
int main(){
    cin>>n;
    

    for (int i=1;i<=n;++i){
        scanf("%d%d", &a[i], &b[i]);
    }
    dfs(1,1,0);
    cout<<ans;
}

