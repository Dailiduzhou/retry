#include<iostream>
int main()
{
    using namespace std;
    system("chcp 65001");
    int x;
    cout << "The expression x=100 has value";
    cout << "Now x=" << (x=100) << endl;
    cout << (100 < 3) << endl;
    cout << (x > 3) << endl;
    cout.setf(ios_base::boolalpha);
    cout << "After" << endl;
    cout << (100 < 3) << endl;
    cout << (x > 3) << endl;
    cout << "非零表达式" << endl;
    cout << (bool) 2 << endl;
    return 0;
}