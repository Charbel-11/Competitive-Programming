//https://www.spoj.com/problems/QTREE2/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
#include <string>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc;
	vector<node> nodes;
	vector<int> depth, d;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n);
		anc.resize(n + 1); for (auto &x : anc) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0); d.resize(n, 0);
	}

	void add_edge(int u, int v, int w) {
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
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur;
				depth[e.v] = depth[cur] + 1;
				d[e.v] = d[e.u] + e.w;
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

	int dist(int u, int v) {
		int lca = LCA(u, v);
		return d[u] + d[v] - 2 * d[lca];
	}

	int findKthParent(int u, int k) {
		int pI = 0;
		while (k) {
			if (k & 1) { u = anc[u][pI]; }
			pI++; k /= 2;
		}
		return u;
	}

	int findKth(int k, int u, int v) {
		int lca = LCA(u, v);
		int diff = depth[u] - depth[lca];
		if (diff >= k) { return findKthParent(u, k); }
		int pathLen = diff + depth[v] - depth[lca];
		return findKthParent(v, pathLen - k);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		tree t(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v, w; cin >> u >> v >> w; u--; v--;
			t.add_edge(u, v, w);
		}
		t.preprocess();

		string s; cin >> s;
		while (s != "DONE") {
			if (s[0] == 'D') {
				int u, v; cin >> u >> v; u--; v--;
				cout << t.dist(u, v) << endl;
			}
			else {
				int k, u, v; cin >> u >> v >> k;
				u--; v--; k--;
				cout << t.findKth(k, u, v) + 1 << endl;
			}
			cin >> s;
		}
	}
}