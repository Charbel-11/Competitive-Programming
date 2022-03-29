#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	vector<vector<int>> dp((1 << n), vector<int>(n, INT_MAX));
	vector<vector<bool>> visited((1 << n), vector<bool>(n, false));

	queue<pair<int, int>> Q;
	for (int i = 0; i < n; i++) {
		dp[(1 << i)][i] = 1; 
		visited[(1 << i)][i] = 1;
		Q.push({ (1 << i), i });
	}

	while (!Q.empty()) {
		int curM = Q.front().first, u = Q.front().second; Q.pop();
		for (auto& e : g.nodes[u].edges) {
			int newM = curM ^ (1 << e.v);
			if (visited[newM][e.v]) { continue; }
			dp[newM][e.v] = dp[curM][u] + 1;
			visited[newM][e.v] = true;
			Q.push({ newM, e.v });
		}
	}


	int ans = 0;
	for (int i = 1; i < (1 << n); i++) {
		ans += *min_element(dp[i].begin(), dp[i].end());
	}
	cout << ans << '\n';
}