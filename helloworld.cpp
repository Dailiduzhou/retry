#include<stdio.h>
#include <iostream>

int main()
{
    using namespace std;
    printf("hello world!");
    cout << R"(Jim "King" Tutt uses "\n" instead of endl.)" << "\n";
    cout << (int*) "home of jolly bytes." << endl;
    cout.setf(ios_base::boolalpha);
    cout << (bool) EOF << endl;
    return 0;
}