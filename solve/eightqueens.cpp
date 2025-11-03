// 八皇后.cpp 
#include<iostream>
using namespace std;
const int n = 8;
char a[n][n] = {};//棋盘
bool b[n], c[2 * n - 1], d[2 * n - 1];//表示这一列、两个对角线有没有皇后 
int cnt = 0;

bool inline check(int x, int y) {
	return !b[y] && !c[x + y] && !d[x - y + n - 1];//加上偏置n-1使下标为非负
}
void print_() {
	//cout << "Solution " << cnt << endl;
	cout << cnt << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] ;//行和列和题中相反了qwq
			if (j != n - 1) cout << ' ';
		}
		cout << endl;
	}
}
void dfs(int x) {
	if (x == n) {//找到了一种摆法
		cnt++;
		print_();
		return;
	}
	for (int i = 0; i < n; i++) {
		if (check(x, i)) {
			b[i] = c[x + i] = d[x - i + n - 1] = true;
			a[x][i] = '*';
			dfs(x + 1);
			//回溯
			b[i] = c[x + i] = d[x - i + n - 1] = false;
			a[x][i] = '.';

		}
	}
}

int main() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = '.';
	dfs(0);//从0行开始摆放； 
	//cout << cnt << endl;
	return 0;
}