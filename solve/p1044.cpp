#include<bits/stdc++.h>
using namespace std;
long long a[40][20];
int n;

int way(int k,int many)
{
    int t=0;//计数
    if(k==2*n)//如果步数已满，返回
    {
        if(many==0)
            return 1;
        else
            return 0;
    }
    if(a[k][many]!=0)
        return a[k][many];
    if(many<=n)
        t+=way(k+1,many+1);
    if(many>0)
        t+=way(k+1,many-1);
    a[k][many]=t;
    return t;
}


int main(){
    scanf("%d", &n);
    printf("%d", way(0,0));
}