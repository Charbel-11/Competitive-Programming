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
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> bLift;
	vector<node> nodes;
	vector<int> depth, size;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) { 
		lg2 = int(log2(n));
		nodes.resize(n); 
		bLift.resize(n + 1); for (auto &x : bLift) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0);
		size.resize(n, 1);
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
			bLift[u][i] = bLift[bLift[u][i - 1]][i-1];

		for (auto e : nodes[u].edges) {
			if (e.v == p) { continue; }

			depth[e.v] = 1 + depth[u];
			dfs(e.v, u);
			size[u] += size[e.v];						//For subtree size
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

	//Finds the child of ancestor which is in the ancestor path of u (could be u)
	int findChildOnPath(int u, int ancestor) {
		if (bLift[u][0] == ancestor) { return u; }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) > depth[ancestor])
				u = bLift[u][i];
		}

		return u;
	}

	int kthAncestor(int u, int k) {
		if (k == 0) { return u; }

		int target = depth[u] - k;
		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= target)
				u = bLift[u][i];
		}

		return u;
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	t.dfs(0, 0);

	int m; cin >> m;
	while (m--) {
		int x, y; cin >> x >> y; x--; y--;

		if (x == y) { cout << n << endl; continue; }

		int lca = t.LCA(x, y);
		int distX = t.depth[x] - t.depth[lca], distY = t.depth[y] - t.depth[lca];
		int dist = distX + distY;

		if (dist % 2) {
			cout << 0 << endl; continue;
		}

		if (distX == distY) {
			int childX = t.findChildOnPath(x, lca);
			int childY = t.findChildOnPath(y, lca);

			cout << n - t.size[childX] - t.size[childY] << endl;
			continue;
		}

		if (t.depth[x] < t.depth[y]) { swap(x, y); }

		dist /= 2;
		int kA = t.kthAncestor(x, dist);
		int kAChild = t.findChildOnPath(x, kA);
		cout << t.size[kA] - t.size[kAChild] << endl;
	}
}