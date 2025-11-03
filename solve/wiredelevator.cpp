// 奇怪的电梯.cpp

#include<bits/stdc++.h>
using namespace std;
int n, a, b, k[205];
bool visited[205];
struct node { 
	int id, step; 
	node(int id_, int step_) {
		id = id_; step = step_;
	}
	node() {
		id = step = -1;
	}
};
queue<node> q;
node x;
int main()
{
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) cin>>k[i];
	node root(a,0);
	q.push(root);
	while (!q.empty())
	{
		x = q.front(); q.pop();
		if (x.id == b) break;
		if (x.id + k[x.id] <= n && !visited[x.id + k[x.id]])
		{
			node temp(x.id + k[x.id], x.step + 1);
			q.push(temp);
			visited[x.id + k[x.id]] = 1;
		}
		if (x.id - k[x.id] >= 1 && !visited[x.id - k[x.id]])
		{
			node temp(x.id - k[x.id], x.step + 1);
			q.push(temp);
			visited[x.id - k[x.id]] = 1;
		}
	}
	if (x.id == b) cout << x.step;
	else cout << -1;
	return 0;
}