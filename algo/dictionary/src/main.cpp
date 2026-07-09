#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  string s = "WHERETHEREISAWILLTHEREISAWAY";
  vector<char> strv(s.size());
  for (int i = 0; i < s.size(); ++i) {
    strv[i] = s[i];
  }
  sort(strv.begin(), strv.end());
  for (const auto &ch : strv) {
    cout << ch;
  }
  return 0;
}
