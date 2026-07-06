#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n) || n <= 0)
    return 0;

  vector<int> scores(n);
  for (int i = 0; i < n; ++i) {
    cin >> scores[i];
  }

  int max_score = *max_element(scores.begin(), scores.end());
  int min_score = *min_element(scores.begin(), scores.end());

  int sum_score = accumulate(scores.begin(), scores.end(), 0);

  double average = static_cast<double>(sum_score) / n;

  // 按要求输出格式
  cout << max_score << "\n";
  cout << min_score << "\n";
  cout << fixed << setprecision(2) << average << "\n";

  return 0;
}
