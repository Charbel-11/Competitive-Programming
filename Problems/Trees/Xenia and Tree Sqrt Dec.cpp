#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <queue>
#include <math.h>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
const int cut = 316;	//root of 1e5
struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; bool red; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> bLift;
	vector<node> nodes;
	vector<int> depth;
	vector<int> dist;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = int(log2(n));
		nodes.resize(n);
		bLift.resize(n + 1); for (auto &x : bLift) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0);
		dist.resize(n);
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	//Preprocessing takes O(nlogn) time
	//First call p should be equal to u
	void dfs(int u, int p) {
		bLift[u][0] = p;

		for (int i = 1; i <= lg2; i++)
			bLift[u][i] = bLift[bLift[u][i - 1]][i - 1];

		for (auto e : nodes[u].edges) {
			if (e.v == p) { continue; }

			depth[e.v] = 1 + depth[u];
			dfs(e.v, u);
		}
	}

	//Need to preprocess before using!
	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = bLift[u][i];
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (bLift[u][i] != bLift[v][i]) {
				u = bLift[u][i];
				v = bLift[v][i];
			}
		}

		return bLift[u][0];
	}

	void findDist() {
		queue<int> Q; vector<bool> visited(n, 0);
		for (int i = 0; i < n; i++) {
			if (nodes[i].red) { Q.push(i); visited[i] = 1; dist[i] = 0; }
		}

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				Q.push(e.v); visited[e.v] = 1;
				dist[e.v] = dist[cur] + 1;
			}
		}
	}
};

int main() {
	int n, m; cin >> n >> m;
	tree t(n); t.nodes[0].red = 1;

	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b; a--; b--;
		t.add_edge(a, b);
	}

	t.dfs(0, 0);
	int done = 0;
	while (done < m) {
		t.findDist();

		vector<int> changed;
		for (int i = 0; i < cut; i++) {
			if (done == m) { break; }

			int type, v; cin >> type >> v; v--;
			if (type == 1) {
				t.nodes[v].red = 1;
				changed.push_back(v);
			}
			else {
				int ans = t.dist[v];
				for (int& c : changed) {
					int l = t.LCA(c, v);
					ans = min(ans, t.depth[c] + t.depth[v] - 2 * t.depth[l]);
				}

				cout << ans << endl;
			}

			done++;
		}
	}
}