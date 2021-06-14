#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int INF = 1 << 30;

vector<vector<int>> adj, dist, root;
vector<set<int>> reach;
int n;

void bfs(int u) {
	reach.resize(n); queue<int> Q;
	for (auto& v : adj[u]) { reach[v].insert(v); Q.push(v); }

	while (!Q.empty()) {
		int cur = Q.front(); Q.pop();
		for (auto& v : adj[cur]) {
			if (v == u || reach[v].size() >= 2) { continue; }

			int pS = reach[v].size();
			for (auto& x : reach[cur])
				reach[v].insert(x);
			
			if (reach[v].size() > pS) { Q.push(v); }
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int m, s; cin >> n >> m >> s;
	adj.resize(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		adj[v].push_back(u);
	}

	vector<int> ans;
	bfs(s);
	for (int i = 0; i < n; i++) {
		if (reach[i].size() == 1 && *reach[i].begin() == i) { ans.push_back(i); }
	}

	cout << ans.size() << '\n';
	for (auto& x : ans) { cout << x << '\n'; }
}