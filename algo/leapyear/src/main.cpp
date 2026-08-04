#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  int year;
  cin >> year;
  bool is_leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  if (is_leapyear) {
    cout << "Yes";
  } else {
    cout << "No";
  }
}
