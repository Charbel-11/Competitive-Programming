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
	int u, v; int ID;
	edge() {}
	edge(int _u, int _v, int id) :
		u(_u), v(_v), ID(id) {}
};

struct node { int val = 0; vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<int> edgesVal;
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
		edgesVal.resize(n - 1, 0);
	}

	void add_edge(int u, int v, int curID) {
		edge e1(u, v, curID); edge e2(v, u, curID);
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

	void markPath(int a, int b) {
		int lca = LCA(a, b);

		nodes[a].val++; nodes[b].val++; nodes[lca].val -= 2;
	}

	//Works because each node has a unique parent
	int getMarks(int u, int p) {
		int curSum = 0;

		for (auto e : nodes[u].edges) {
			if (e.v == p) { continue; }

			int childSum = getMarks(e.v, u);
			edgesVal[e.ID] = childSum;
			curSum += childSum;
		}

		curSum += nodes[u].val;
		return curSum;
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v, i);
	}

	t.dfs(0, 0);

	int k; cin >> k;
	for (int i = 0; i < k; i++) {
		int a, b; cin >> a >> b; a--; b--;
		t.markPath(a, b);
	}

	t.getMarks(0, -1);

	for (auto &x : t.edgesVal) { cout << x << " "; } cout << endl;
}