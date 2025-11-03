#include<bits/stdc++.h>
using namespace std;
long long ht(long long x){
    if (x<=1) return 1;
    return 2*ht(x-1) + 1;
}
int main(){
    long long n;
    cin>>n;
    cout<<ht(n);
}