#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  long long n;
  cin >> n;

  vector<long long> divisors;
  for (long long i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      divisors.push_back(i);
      if (i != n / i) {
        divisors.push_back(n / i);
      }
    }
  }
  sort(divisors.begin(), divisors.end());

  int count = 0;
  int d = divisors.size();
  for (int i = 0; i < d; ++i) {
    long long a = divisors[i];
    for (int j = i; j < d; ++j) {
      long long b = divisors[j];
      if (a > n / b)
        continue;
      long long ab = a * b;
      if (n % ab != 0)
        continue;
      long long c = n / ab;
      if (c >= b) {
        ++count;
      }
    }
  }

  cout << count << endl;
  return 0;
}
