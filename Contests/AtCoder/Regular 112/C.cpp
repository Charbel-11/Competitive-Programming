#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

int dp[(int)2e5][2];
int subS[(int)2e5];

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}
	
	void dfs0(int u, int p) {
		subS[u] = 1;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs0(e.v, u);
			subS[u] += subS[e.v];
		}
	}

	void dfs(int u, int p, bool c) {
		if (c) { 
			dfs(u, p, !c); 
			dp[u][c] = subS[u] - dp[u][!c];
			return;
		}

		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u, 1);
		}
 
		vector<pair<int, int>> valE, valO;

		int ans = 0; bool t = 0;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			if (subS[e.v] % 2) { valO.push_back({ subS[e.v] - 2 * dp[e.v][1], e.v }); }
			else { valE.push_back({ subS[e.v] - 2 * dp[e.v][1], e.v }); }
		}

		sort(valE.begin(), valE.end());
		sort(valO.begin(), valO.end());
		while (!valE.empty() && valE.back().first >= 0) {
			int v = valE.back().second;
			ans += subS[v] - dp[v][1];
			valE.pop_back();
		}
		while (!valO.empty()){
			int v = valO.back().second;
			if (!t) { ans += subS[v] - dp[v][1]; }
			else { ans += dp[v][1]; }
			valO.pop_back(); t = !t;
		}
		while (!valE.empty()) {
			int v = valE.back().second;
			if (!t) { ans += subS[v] - dp[v][1]; }
			else { ans += dp[v][1]; }
			valE.pop_back();
		}

		dp[u][c] = ans;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 1; i <= n - 1; i++) {
		int p; cin >> p; p--;
		t.add_edge(i, p);
	}

	t.dfs0(0, -1);
	t.dfs(0, -1, 1);
	cout << dp[0][1] << '\n';
}