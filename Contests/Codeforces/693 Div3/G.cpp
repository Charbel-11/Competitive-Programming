#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	int u, v; int w; edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<int> dist;
	vector<vector<int>> dp;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n); dp.resize(n, vector<int>(2, -1)); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	void bfs0(int s) {
		queue<int> Q; vector<bool> vis(n, 0);
		Q.push(s); vis[s] = true; dist[s] = 0;

		while(!Q.empty()){
			int cur = Q.front(); Q.pop();
			for (auto& e : nodes[cur].edges) {
				if (vis[e.v]) { continue; }
				vis[e.v] = true; dist[e.v] = dist[e.u] + 1;
				Q.push(e.v);
			}
		}
	}

	int findMinDist(int u, bool b) {
		if (dp[u][b] != -1) { return dp[u][b]; }

		dp[u][b] = dist[u];
		for (auto& e : nodes[u].edges) {
			if (dist[u] < dist[e.v]){
				dp[u][b] = min(dp[u][b], findMinDist(e.v, b));
			}
			else {
				if (b) { continue; }
				dp[u][b] = min(dp[u][b], findMinDist(e.v, 1));
			}
		}

		return dp[u][b];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		graph g(n);
		for (int i = 0; i < m; i++) {
			int u, v; cin >> u >> v; u--; v--;
			g.add_edge(u, v);
		}

		g.bfs0(0);
		for (int i = 0; i < n; i++) {
			cout << g.findMinDist(i, 0) << ' ';
		}
		cout << '\n';
	}
}