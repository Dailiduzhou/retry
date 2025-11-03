#include<bits/stdc++.h>
#define st first
#define nd second
using namespace std;
typedef pair<int,int> Pair;
int n,s,k,dis[100001],w[200001],tar[200001],nxt[200001],head[200001],tot;
bool u[100001];
priority_queue<Pair,vector<Pair>,greater<Pair> >q;
void add(int u,int v,int d){
    w[++tot]=d,tar[tot]=v,nxt[tot]=head[u],head[u]=tot;//邻接表存储
    return;
}
void dijkstra(int s){//Dijkstra
    q.push({0,s});
    dis[s]=0;
    while(!q.empty()){
        Pair p=q.top();
        q.pop();
        if(dis[p.nd]!=p.st)
            continue;
        for(int i=head[p.nd];i;i=nxt[i]){
            if(dis[tar[i]]>dis[p.nd]+w[i]){
                dis[tar[i]]=dis[p.nd]+w[i];
                q.push({dis[tar[i]],tar[i]});
            }
        }
    }
    return;
}
int main(){
    memset(dis,0x3f,sizeof(dis));//初始化无穷
    cin>>n>>s>>k;
    for(int i=1,v;i<=n;i++){
        cin>>v;
        if(i+v<=n)//判断越界
            add(i,i+v,1);
        if(1<=i-v)
            add(i,i-v,1);
    }
    dijkstra(s);
    cout<<(dis[k]==0x3f3f3f3f?-1:dis[k]);//注意-1
    return 0;
}
