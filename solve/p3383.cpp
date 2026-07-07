#include <bits/stdc++.h>
int main() {
  using namespace std;
  std::ios::sync_with_stdio(0);
  int n, q, count = 0, k;
  cin >> n >> q;
  bool isprime[n + 1];
  int primes[n + 1];

  memset(isprime, true, sizeof(isprime));
  memset(primes, 0, sizeof(primes));

  if (n >= 1) {
    isprime[0] = false;
    isprime[1] = false;
  }

  for (int i = 2; i <= n; ++i) {
    if (isprime[i]) {
      primes[++count] = i;
    }
    for (int j = 1; j <= count && i <= n / primes[j]; ++j) {
      isprime[i * primes[j]] = false;
      if (i % primes[j] == 0) {
        break;
      }
    }
  }

  for (int i = 1; i <= q; ++i) {
    cin >> k;
    cout << primes[k] << '\n';
  }
  return 0;
}
