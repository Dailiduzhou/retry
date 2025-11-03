#include <iostream>
int main()
{
    using namespace std;
    int auks , bats, coots;
    auks = 19.99 + 11.99;
    bats = (int) 19.99 + (int) 11.99; // Explicit type cast
    coots = int(19.99) + int(11.99); // Another explicit type cast
    cout << "auks = " << auks << ", bats = " << bats
         << ", coots = " << coots << endl;
    char ch = 'Z';
    cout << "The code for" << ch << "is";
    cout << int(ch) << endl; // Implicit type cast
    cout << "Yes, the code for" << ch << "is"
         << static_cast<int>(ch) << endl; // Using static_cast
    return 0;

}