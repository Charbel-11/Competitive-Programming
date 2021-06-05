#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;

int dp[(int)2e5 + 2][2];

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

	int findMax(int u, int p, bool used) {
		if (dp[u][used] != -1) { return dp[u][used]; }

		int res = 0, ss = 0;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			ss += findMax(e.v, u, 0);
			findMax(e.v, u, 1);
		}

		res = ss;
		if (!used) {
			for (auto &e : nodes[u].edges) {
				if (e.v == p) { continue; }
				int notTaken = dp[e.v][0], taken = dp[e.v][1] + 1;
				int cur = ss - notTaken + taken;
				res = max(res, cur);
			}
		}
		return dp[u][used] = res;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	for (int i = 0; i < n; i++)
		dp[i][0] = dp[i][1] = -1;
	cout << t.findMax(0, -1, 0) << '\n';
}