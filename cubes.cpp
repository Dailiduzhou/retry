#include<iostream>
double cube(double & x);
double refcube(const double & ra);
int main()
{
    using namespace std;
    double num = 3.0;

    cout << "num = " << num << endl;
    cout << "cube(num) = " << cube(num) << endl;
    cout << "num = " << num << endl;
    cout << "refcube(num) = " << refcube(num) << endl;
    cout << "num = " << num << endl;
    return 0;
}

double cube(double & x)
{
    x *= x * x;
    return x;
}

double refcube(const double & ra)
{
    return ra * ra *ra;
}