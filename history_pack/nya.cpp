#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    cin.get();
    char a;
    while (cin.get(a)){
        if (a>='a' && a<='z'){
            if (a=='n')
                cout<<"nya";
            else
                cout<<a;
        }
        if (a>='A' && a<='Z'){
            if (a=='N')
                cout<<"NYA";
            else
                cout<<a;
        }
        if (a=='\n')
            cout<<endl;
        
    }
    return 0;
}