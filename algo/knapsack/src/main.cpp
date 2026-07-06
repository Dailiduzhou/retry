#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, W;
  if (!(cin >> n >> W))
    return 0;

  vector<int> w(n), v(n);
  for (int i = 0; i < n; i++)
    cin >> w[i] >> v[i];

  long long ans = 0, curVal = 0, curWt = 0;
  int l = 0;
  for (int r = 0; r < n; r++) {
    curWt += w[r];
    curVal += v[r];
    while (curWt > W && l <= r) {
      curWt -= w[l];
      curVal -= v[l];
      l++;
    }
    ans = max(ans, curVal);
  }

  cout << ans << endl;
  return 0;
}
