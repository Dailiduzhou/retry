#include<iostream>
#include<ctime>
int main()
{
    using namespace std;
    cout << "Enter delay time(in seconds):" << endl;
    float secs;
    cin >> secs;
    clock_t delay = secs * CLOCKS_PER_SEC;
    cout << "Starting\n";
    clock_t start = clock();
    while (clock() - start <delay)
        ;
    cout << "Done!\n";
    return 0;
}