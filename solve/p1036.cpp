#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000000; // 5e6
int n, k;
bool isp[MAXN + 1];
vector<int> primes;

void sieve() {
    memset(isp, true, sizeof(isp));
    isp[0] = isp[1] = false;
    primes.clear();
    
    for (int i = 2; i <= MAXN; i++) {
        if (isp[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && (long long)i * primes[j] <= MAXN; j++) {
            isp[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

void dfs(vector<long long>& res, long long csum, long long a[], int st, int k) {
    if (k == 0) {
        res.push_back(csum);
        return;
    }
    
    for (int i = st; i < n; i++) {
        dfs(res, csum + a[i], a, i + 1, k - 1);
    }
}

int main() {
    sieve(); // 初始化素数筛
    
    scanf("%d%d", &n, &k);
    long long a[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    
    vector<long long> sums;
    dfs(sums, 0, a, 0, k);
    
    int ans = 0;
    for (auto it : sums) {
        // 只检查在范围内的和
        if (it <= MAXN && it >= 0 && isp[it]) {
            ++ans;
        }
    }
    printf("%d", ans);
    return 0;
}