#include<iostream>
#include "stonewt.h"
using std::cout;
void display(const Stonewt & st, int n);
int main()
{
    Stonewt incognito = 275;
    Stonewt wolfe(285.7);
    Stonewt taft(21, 8);

    cout << "inco";
    incognito.show_stn();
    cout << "wolfe";
    wolfe.show_stn();
    cout << "taft";
    taft.show_lbs();

    incognito = 276.8;
    taft = 325;
    incognito.show_stn();
    taft.show_lbs();
    display(taft, 2);
    display(422, 2);
    return 0;
}

void display(const Stonewt & st, int n)
{
    for (int i = 0; i < n; i++)
    {
        st.show_stn();
    }
}