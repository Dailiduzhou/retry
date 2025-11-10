#include<bits/stdc++.h>
int main() {
    using namespace std;
    int n,a,b=1;
    cin>>n;
    a=(n+1)*n/2;
    int i;
    for (i=1;i<a+1;i++) {
        if (i<10) {
            printf("0%d",&i);
        }
        else
            cout<<i;
        b++;
        if (b==n) {
            b=1;
            --n;
            cout<<'\n';
        }
    }
    return 0;
}