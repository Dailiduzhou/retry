#include<iostream>
const int favorite = 27;
int main()
{
    using namespace std;
    int n;
    cout << "Enter a num in range 1-100 to find"
         << "my favorite number:";
    do
    {
        cin >> n;
        if (n > favorite)
            cout << "Too high, again:";
        else if (n < favorite)
            cout << "Too low, again:";
        else
            cout << favorite << " is right!";
    } while (n != favorite);
    return 0;
}