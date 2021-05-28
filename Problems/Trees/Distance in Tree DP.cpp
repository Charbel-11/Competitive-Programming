#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

ll DP[50002][502];
int k; ll res;

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			for (int i = 1; i <= k; i++) { DP[u][i] += DP[e.v][i - 1]; }
		}

		res += DP[u][k];

		ll bef = res;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			for (int i = 1; i < k; i++) { res += DP[e.v][i - 1] * (DP[u][k - i] - DP[e.v][k - i - 1]); }
		}
		res -= bef; res /= 2; res += bef;

		DP[u][0] = 1;
	}
};

void resetDP() {
	for (int i = 0; i < 50002; i++)
		for (int j = 0; j < 502; j++)
			DP[i][j] = 0;
}

int main() {
	int n; cin >> n >> k;
	tree t(n); res = 0;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	resetDP();
	t.dfs(0, -1);
	cout << res << endl;
}