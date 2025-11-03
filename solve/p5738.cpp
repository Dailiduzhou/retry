#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    int a[n][m], sc[n];
    int sum=0;
    for (int i=0;i<n;++i){
        for (int j=0;j<m;++j){
            int b;
            cin>>b;
            a[i][j]=b;
            sum+=b;
        }
        sort(a[i],a[i]+m);
        sum = sum-a[i][0]-a[i][m-1];
        sc[i]=sum/(m-2);
        sum=0;
    }
    sort(sc,sc+n);
    cout.setf(ios_base::showpoint);
    cout<<fixed<<setprecision(2)<<static_cast<double>(sc[n-1]);
}