#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc;
	vector<node> nodes;
	vector<int> depth;
	vector<ll> sum;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 1.0)));
		nodes.resize(n); depth.resize(n, 0);
		sum.resize(n, 0);
		anc.resize(n + 1, vector<int>(lg2 + 1, -1));
	}

	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	//Copy the constructor
	//Need to call this first
	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur;
				depth[e.v] = depth[cur] + 1;
				q.push(e.v); visited[e.v] = true;
			}
		}
		for (int i = 1; i <= lg2; i++)
			for (int u = 0; u < n; u++)
				anc[u][i] = anc[anc[u][i - 1]][i - 1];
	}

	//Need to preprocess before using!
	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = anc[u][i];	//furthest parent found is 2^i
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				u = anc[u][i];
				v = anc[v][i];
			}
		}

		return anc[u][0];
	}

	void dfs(int u, int p, ll s) {
		sum[u] = s;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, e.u, s + e.w);
		}
	}

	int dist(int u, int v) {
		int lca = LCA(u, v);
		return sum[u] + sum[v] - 2 * sum[lca];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; ll w; cin >> u >> v >> w; u--; v--;
		t.add_edge(u, v, w);
	}
	t.preprocess(); t.dfs(0, -1, 0);

	vector<vector<ll>> dist(n, vector<ll>(n, 0));
	vector<vector<ll>> dp(n, vector<ll>(n, 0));
	vector<vector<int>> edges(n);
	for (int i = 0; i < n; i++) {
		ll curMax = LLONG_MIN; int maxIdx = -1;
		for (int j = 0; j < n; j++) {
			if (i == j) { continue; }

			dist[i][j] = t.dist(i, j);
			if (dist[i][j] > curMax) {
				curMax = dist[i][j];
				maxIdx = j;
			}
		}
		dp[i][maxIdx] = curMax;
		edges[i].push_back(maxIdx);
	}

	for (int i = 0; i < n; i++) {
		int start = i;
		int cur = edges[start].back();
		ll curVal = dp[start][cur];

		while (edges[cur].back() != start) {
			int nxt = edges[cur].back();
			dp[start][nxt] = max(dp[start][nxt], min(curVal, dp[cur][nxt]));
			cur = nxt; if (cur == nxt) { break; }
		}
	}

	while (q--) {
		int x, y; cin >> x >> y; x--; y--;

		ll cur = max(dist[x][y], dp[x][y]);
		for (int k = 0; k < n; k++) {
			cur = max(cur, min(dist[x][k], dist[k][y]));
		}
		
		cout << cur << '\n';
	}
}