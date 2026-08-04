#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  int n;
  char ch;
  cin >> n;
  vector<char> str(n);
  for (int i = 0; i < n; ++i) {
    scanf("%c", &ch);
    str[i] = ch;
  }

  for (int i = 0, j = n - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) {
      cout << "No";
      return 0;
    }
  }
  cout << "Yes";
  return 0;
}
