#include<iostream>
int main()
{
    using namespace std;
    for (int n = 6; n>0; n--)
        cout << n << endl;
    cout << "use \"--n\"" << endl;
    for (int n = 6; n>0; --n)
        cout << n << endl;
    double prices[5] ={4.99,10.99,6.87,7.99,8.49};
    for (double x : prices)
        cout << x << endl;
    cout << "After" << endl;
    for (double &x : prices)
    {
        x *= 0.8;
        cout << x << endl;
    }
    return 0;
}