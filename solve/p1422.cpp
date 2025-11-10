#include<bits/stdc++.h>
int main(){
    using namespace std;
    int a;
    cin>>a;
    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout.precision(1);
    if (a<=150)
        cout<<a*0.4463;
    else if (a>150 && a<=400)
        cout<< 150*0.4463+(a-150)*0.46663;
    else
        cout<< 150*0.4463+250*0.4663+(a-400)*0.5663;
    return 0;
}