#include <climits>
#include <iostream>
#include <string>
using namespace std;

struct Student {
  string name;
  int score;
};

int main(int argc, char **argv) {
  string name;
  int score;
  string maname;
  int mascore = INT_MIN;
  for (int i = 0; i < 3; ++i) {
    cin >> name;
    cin >> score;
    if (score > mascore) {
      mascore = score;
      maname = name;
    }
  }
  cout << maname;

  return 0;
}
