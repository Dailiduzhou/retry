#include<bits/stdc++.h> 
using namespace std;
int m,s,c,ans;
int a[210],b[210];
int main()
{
    scanf("%d%d%d",&m,&s,&c);
    for (int i = 1;i <= c;i++)
        scanf("%d",&a[i]);
    sort(a + 1,a + c + 1);
    ans = a[c] - a[1] + 1;
    for (int i = 1;i <= c - 1;i++)
        b[i] = a[i + 1] - a[i] - 1;
    sort(b + 1,b + c);
    for (int i = c - 1;i >= c-m+1 && i>0;i--)
        ans -= b[i];
    printf("%d\n",ans);
}
