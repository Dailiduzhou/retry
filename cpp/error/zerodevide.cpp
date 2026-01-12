#include <cstdlib>
#include <iostream>

double hmean(double a, double b) {
    if (a == -b) {
        std::cout << "zero divide";
        std::abort();
    }

    return 2.0 * a * b / (a + b);
}

int main() {
    double x, y, z;

    using std::cin;
    using std::cout;
    using std::endl;

    cout << "Enter 2 numbers:" << endl;
    while (cin >> x >> y) {
        z = hmean(x, y);
        cout << "The harmonic mean of " << x << " and " << y << " is " << z
             << endl;
        cout << "Enter next set of numbers <q to quit>" << endl;
    }
    cout << "Bye!" << endl;
    return 0;
}