#include<iostream>
const int arSize = 16;
int main()
{
    using namespace std;
    long long factorials[arSize];
    factorials[0] = factorials[1] = 1LL;
    for (int i =2; i<arSize; i++)
        factorials[i] = i * factorials[i-1];
    for (int i = 0; i<arSize; i++)
        cout << i << "!= " << factorials[i] << endl;
    return 0;
}