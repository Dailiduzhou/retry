#include<cstdio>
int n,ans;
int main(){
    scanf("%d",&n);
    for(int i=1,j;i<=n;i=j+1){
        j=n/(n/i);
        ans+=(n/i)*(j-i+1);
    }
    printf("%d",ans);
return 0;
}
