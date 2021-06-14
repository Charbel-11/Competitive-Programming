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
	vector<int> depth;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = int(log2(n));
		nodes.resize(n);
		bLift.resize(n + 1); for (auto &x : bLift) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0);
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	//Preprocessing takes O(nlogn) time
	//First call p should be equal to u
	//Copy the constructor lines
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

	int distance(int u, int v) {
		int lca = LCA(u, v);
		int res = depth[u] + depth[v] - 2 * depth[lca];

		return res;
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

	int q; cin >> q;
	while (q--) {
		int x, y, a, b, k; cin >> x >> y >> a >> b >> k;
		x--; y--; a--; b--;

		int originalPath = t.distance(a, b);
		if (originalPath % 2 == k % 2 && k >= originalPath) { cout << "YES" << endl; continue; }

		int p1 = t.distance(a, x), p2 = t.distance(b, y);
		int newPath1 = p1 + p2 + 1;
		if (newPath1 % 2 == k % 2 && k >= newPath1) { cout << "YES" << endl; continue; }

		p1 = t.distance(a, y); p2 = t.distance(b, x);
		int newPath2 = p1 + p2 + 1;
		if (newPath2 % 2 == k % 2 && k >= newPath2) { cout << "YES" << endl; continue; }

		int minPath = min(originalPath, min(newPath1, newPath2));

		int joker1 = t.distance(a, x), joker2 = t.distance(a, y);
		int jj = joker1 + joker2 + 1;
		if (jj % 2 && k>=(jj+minPath)) { cout << "YES" << endl; continue; }

		joker1 = t.distance(b, x); joker2 = t.distance(b, y);
		jj = joker1 + joker2 + 1;
		if (jj % 2 && k>=(jj+minPath)) { cout << "YES" << endl; continue; }

		cout << "NO" << endl;
	}
}