#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
const ll mod = 1e9 + 7;

vector<bool> colors;
ll DP[(int)1e5 + 1][2];

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
		if (colors[u]) { DP[u][1] = 1; DP[u][0] = 0; }
		else { DP[u][1] = 0; DP[u][0] = 1; }

		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);

			ll w = DP[u][0], b = DP[u][1];

			DP[u][0] = w * DP[e.v][0]; DP[u][0] %= mod;
			DP[u][0] += w * DP[e.v][1]; DP[u][0] %= mod;

			DP[u][1] = w * DP[e.v][1]; DP[u][1] %= mod;
			DP[u][1] += b * DP[e.v][0]; DP[u][1] %= mod;
			DP[u][1] += b * DP[e.v][1]; DP[u][1] %= mod;
		}
	}
};

int main() {
	int n; cin >> n;
	tree g(n); colors.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int p; cin >> p;
		g.add_edge(i + 1, p);
	}

	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		colors[i] = a;
	}

	g.dfs(0, -1);
	cout << DP[0][1] << endl;
}