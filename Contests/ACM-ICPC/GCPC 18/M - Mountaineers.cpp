#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

struct DSU {
	vector<int> rank, parent;
	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}
	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
	bool operator < (const edge &rhs) const { return w < rhs.w; }
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n = 0;
	vector<edge> edges; int m = 0;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
		edges.push_back(e1); m++;
	}

	void KruskalMST(vector<edge> &res) {
		sort(edges.begin(), edges.end());
		DSU dsu(n); res.clear(); int i = 0;
		while (i < m && res.size() != n - 1) {
			edge &e = edges[i];
			if (!dsu.merge(e.u, e.v)) { i++; continue; }
			res.push_back(e);
		}
		if (res.size() != n - 1) { res.clear(); }
	}
};

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc, heavy;
	vector<node> nodes;
	vector<int> depth;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n);
		anc.resize(n + 1, vector<int>(lg2 + 1, -1));
		heavy.resize(n + 1, vector<int>(lg2 + 1, -1));
		depth.resize(n, 0);
	}

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w); nodes[u].edges.push_back(e1);
		edge e2(v, u, w); nodes[v].edges.push_back(e2);
	}

	//Copy the constructor
	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root; heavy[root][0] = -INT_MAX;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur; heavy[e.v][0] = e.w;
				depth[e.v] = depth[cur] + 1;
				q.push(e.v); visited[e.v] = true;
			}
		}
		for (int i = 1; i <= lg2; i++) {
			for (int u = 0; u < n; u++) {
				anc[u][i] = anc[anc[u][i - 1]][i - 1];
				heavy[u][i] = max(heavy[u][i - 1], heavy[anc[u][i - 1]][i - 1]);
			}
		}
	}

	//Need to preprocess before using
	//Returns the LCA of nodes u and v with the largest weight on the path between u and v in O(logn)		
	pair<int, int> find(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		int maxWeight = -INT_MAX;
		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v]) {
				maxWeight = max(maxWeight, heavy[u][i]);
				u = anc[u][i];
			}
		}

		if (u == v) { return { u, maxWeight }; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				maxWeight = max(maxWeight, heavy[u][i]); u = anc[u][i];
				maxWeight = max(maxWeight, heavy[v][i]); v = anc[v][i];
			}
		}
		maxWeight = max(maxWeight, heavy[u][0]);
		maxWeight = max(maxWeight, heavy[v][0]);

		return { anc[u][0], maxWeight };
	}
};

int main() {
	int m, n, q; cin >> m >> n >> q;
	vector<vector<int>> grid(m);
	for (auto &x : grid) {
		x.resize(n);
		for (auto &y : x) { cin >> y; }
	}
	graph g(m*n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i < m - 1) {
				int w = max(grid[i][j], grid[i + 1][j]);
				g.add_edge(i*n + j, (i + 1)*n + j, w);
			}
			if (j < n - 1) {
				int w = max(grid[i][j], grid[i][j + 1]);
				g.add_edge(i*n + j, i*n + j + 1, w);
			}
		}
	}

	vector<edge> MST;
	g.KruskalMST(MST);

	tree t(m*n);
	for (auto &e : MST) { t.add_edge(e.u, e.v, e.w); }
	t.preprocess();

	while (q--) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;

		int startNode = x1 * n + y1;
		int targetNode = x2 * n + y2;
		if (startNode == targetNode) { cout << grid[x1][y1] << endl; }
		else { cout << t.find(startNode, targetNode).second << endl; }
	}
}