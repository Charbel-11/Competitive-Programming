#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v, w;
	edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc, heavy;
	vector<node> nodes;
	vector<int> depth;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n); depth.resize(n, 0);
		anc.resize(n + 1, vector<int>(lg2 + 1, -1));
		heavy.resize(n + 1, vector<int>(lg2 + 1, -1));
	}

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w); nodes[u].edges.push_back(e1);
		edge e2(v, u, w); nodes[v].edges.push_back(e2);
	}

	//Copy the constructor
	//Need to call this first (after adding the edges)
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
				u = anc[u][i]; v = anc[v][i];
			}
		}
		return anc[u][0];
	}

	int dist(int u, int v) {
		int lca = LCA(u, v);
		return depth[u] + depth[v] - 2 * depth[lca];
	}

	//Finds kth parent of u
	int findKthParent(int u, int k) {
		int pI = 0;
		while (k) {
			if (k & 1) { u = anc[u][pI]; }
			pI++; k >>= 1;
		}
		return u;
	}
};