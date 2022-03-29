#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;
typedef long long ll;

const ll mod = 998244353;

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

ll dp[2002][2002][2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m; graph g(n);
	int K, s, t, x; cin >> K >> s >> t >> x; s--; t--; x--;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	dp[s][0][0] = 1;
	for (int k = 1; k <= K; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2; j++) {
				for (auto& e : g.nodes[i].edges) {
					bool flip = (e.v == x);
					dp[i][k][j] += dp[e.v][k - 1][j ^ flip];
					dp[i][k][j] %= mod;
				}
			}
		}
	}

	cout << dp[t][K][0] << '\n';
}