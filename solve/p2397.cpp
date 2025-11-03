#include<bits/stdc++.h>
using namespace std;
int main(){
    int massn, n,i;
    int cnt =0;
    cin>>n;
    while (n--){
        cin>> i;
        if (cnt==0){
            massn = i;
            cnt++;
        }
        if (massn==i) cnt++;
        if (massn != i){
            cnt--;
        }
    }
    cout<<massn;
}