#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int n,len=1,f[5003][5003];
void hp(int k)
{    
    int i;
    for(i=1;i<=len;i++)
     f[k][i]=f[k-1][i]+f[k-2][i];
    for(i=1;i<=len;i++)            
     if(f[k][i]>=10)
     {
         f[k][i+1]+=f[k][i]/10;
         f[k][i]=f[k][i]%10;
         if(f[k][len+1])len++;
    }
}
int main()
{
    int i;
    scanf("%d",&n);
    f[1][1]=1; f[2][1]=2;       
    for(i=3;i<=n;i++)             
     hp(i);                         
    for(i=len;i>=1;i--)             
     printf("%d",f[n][i]);
    return 0;
}
