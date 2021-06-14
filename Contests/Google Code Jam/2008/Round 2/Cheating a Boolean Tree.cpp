#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool val = false, canChange = false; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<vector<int>> dp;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); dp.resize(n, vector<int>(2, 1e6)); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p, bool v) {
		if (nodes[u].edges.size() == 1) {
			dp[u][nodes[u].val] = 0;
			return;
		}

		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u, 0); dfs(e.v, u, 1);
		}

		int lC = u << 1, rC = u << 1 | 1;
		if ((v && nodes[u].val == 0) || (!v && nodes[u].val == 1)) {
			dp[u][v] = min(dp[lC][v], dp[rC][v]);
		}
		else {
			dp[u][v] = min(dp[lC][v] + dp[rC][v], (int)1e6);
			if (nodes[u].canChange) {
				dp[u][v] = min({ dp[u][v], 1 + min(dp[lC][v], dp[rC][v]), (int)1e6 });
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, v; cin >> n >> v;
		tree t(n + 1);
		for (int i = 1; i <= n; i++) {
			int v1 = i << 1;
			int v2 = i << 1 | 1;
			if (v1 <= n) { t.add_edge(i, v1); }
			if (v2 <= n) { t.add_edge(i, v2); }
		}

		for (int i = 1; i <= (n - 1) / 2; i++) {
			int b1, b2; cin >> b1 >> b2;
			t.nodes[i].val = b1;
			t.nodes[i].canChange = b2;
		}
		for (int i = (n - 1) / 2 + 1; i <= n; i++) {
			int b1; cin >> b1;
			t.nodes[i].val = b1;
		}

		t.dfs(1, -1, v);

		cout << "Case #" << qq << ": ";
		if (t.dp[1][v] == 1e6) { cout << "IMPOSSIBLE\n"; }
		else { cout << t.dp[1][v] << '\n'; }
	}
}