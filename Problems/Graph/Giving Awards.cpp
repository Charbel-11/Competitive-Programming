//https://codeforces.com/contest/412/problem/D
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <string>
#include <climits>
#include <numeric>
using namespace std;

vector<set<int>> adj;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	adj.resize(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		adj[v].insert(u);
	}

	vector<int> ans(n); 
	iota(ans.begin(), ans.end(), 1);

	for (int i = 1; i < n; i++) {
		int u = i, v = i - 1;
		while (u > 0 && adj[ans[u]].count(ans[v])) {
			swap(ans[u], ans[v]);
			u--; v--;
		}
	}

	for (auto &x : ans) { cout << x << ' '; }
}