#include<bits/stdc++.h>
using namespace std;
struct s{
    string n;
    int y;
    int m;
    int e;
    int sum;
};
int main(){
    int t;
    cin>>t;
    s ss[t];
    for (int i=0;i<t;++i){
        string a;
        int b,c,d;
        cin>>a>>b>>c>>d;
        ss[i].n=a, ss[i].y=b,ss[i].m=c,ss[i].e=d;
        ss[i].sum =b+c+d;
    }
    for (int i=0;i<t-1;++i){
        for (int j=i+1;j<t;++j){
            if (abs(ss[i].y-ss[j].y)<=5 &&
                abs(ss[i].m-ss[j].m)<=5 &&
                abs(ss[i].e-ss[j].e)<=5 &&
                abs(ss[i].sum-ss[j].sum)<=10){
                cout<<ss[i].n<<' '<<ss[j].n<<endl;
                }
        }
    }
}