#include<iostream>
using namespace std;
struct antarctica
{
    int year;
};

int main()
{
    antarctica s01, s02, s03;
    s01.year = 1998;
    s03.year = 2002;
    antarctica* pa = &s02;
    pa->year = 1999;
    cout << "(*pa).year = " ;
    cout << (*pa).year << endl;
    antarctica trio[3];
    trio[0].year = 2003;
    cout << trio -> year << endl;
    const antarctica* arp[3] = {&s01,&s02,&s03};
    cout << arp[1]->year << endl;
    const antarctica** ppa = arp;
    auto ppb = arp;
    cout << (*ppa)->year << endl;
    cout << (*(ppa + 1))->year << endl;
    cout << (*ppb)->year << endl;
    cout << (*(ppb +1))->year << endl;
    return 0;
}