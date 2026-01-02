#include<iostream>

inline double square(double x) { return x * x; }

int main()
{
    using namespace std;
    double c = 13.0;
    cout << "c = " << c << endl;
    cout << "c squared =" << square(c++) << endl;
    cout << "Now, c = " << c;
    return 0;
}