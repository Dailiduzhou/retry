#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const int M = 5;
const int N = 6;

bool guess(vector<vector<int>> &press, const vector<vector<int>> &initStatus);
void cleanPress(vector<vector<int>> &press);

int main() {
    vector<vector<int>> initStatus(M, vector<int>(N));
    vector<vector<int>> press(M, vector<int>(N, 0));

    // 输入处理
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> initStatus[i][j];
        }
    }

    press[0][0] = -1;
    for (int i = 0; i < (1 << N); i++) {
        press[0][0]++;
        int t = 0;
        while (t < N && press[0][t] > 1) {
            press[0][t] = 0;
            t++;
            if (t < N)
                press[0][t]++;
        }

        if (guess(press, initStatus)) {
            for (const auto &line : press) {
                for (int item : line) {
                    cout << item << " ";
                }
                cout << endl;
            }
            return 0;
        }
    }
    return 0;
}

bool guess(vector<vector<int>> &press, const vector<vector<int>> &initStatus) {
    for (int i = 1; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int sum = press[i - 1][j] + initStatus[i - 1][j];
            if (i - 2 >= 0)
                sum += press[i - 2][j];
            if (j - 1 >= 0)
                sum += press[i - 1][j - 1];
            if (j + 1 < N)
                sum += press[i - 1][j + 1];
            press[i][j] = sum % 2;
        }
    }

    for (int j = 0; j < N; j++) {
        int sum = initStatus[M - 1][j] + press[M - 1][j] + press[M - 2][j];
        if (j - 1 >= 0)
            sum += press[M - 1][j - 1];
        if (j + 1 < N)
            sum += press[M - 1][j + 1];
        if (sum % 2 != 0)
            return false;
    }
    return true;
}