#include <bits/stdc++.h>

inline bool isprime(int x) { // 判断一个数是否是素数
	if (x == 1) return false; // 注意这步特判是必需的
	if (x%2==0) return false;
    for (int i = 3; i * i <= x; i+=2)
		if (x % i == 0)
			return false;
	return true;
}

const int N = 25;
int a[N], ans, n, k;

void dfs(int now, int sum, int sid) {
	// 现在已经选了 now 个数，当前总和为 sum
	// sid 是这次选数的起始下标，即我们从 a[sid] 开始选数枚举
	if (now == k) {
		if (isprime(sum))
			++ans;
		return ;
	}

	// 已经选了 now 个数，这次选完后，还有 k - now - 1 个数要选择
	// 因此 a[n - (k - now - 1)] 即 a[n - k + now + 1] 是枚举的终点
	for (int i = sid; i <= n - k + now + 1; ++i)
		dfs(now + 1, sum + a[i], i + 1);
	return ;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	dfs(0, 0, 1);
	printf("%d\n", ans);
	return 0;
}