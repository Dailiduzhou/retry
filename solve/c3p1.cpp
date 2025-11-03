#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    vector<int> a, b;
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            int c;
            cin>>c;
            if (i == j){
                a.push_back(c);
            }
            if (i+j == n-1){
                b.push_back(c);
            }
        }
    }
    sort(a.begin(),a.end());
    sort(b.begin(), b.end());
    cout<<a[n-1]<<' '<< b[0];
    return 0;
}