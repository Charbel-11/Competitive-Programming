#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;
typedef long long ll;

vector<int> subsetNodes, depth;
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
	vector<int> size;

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

	int distance(int u, int v) {
		int lca = LCA(u, v);
		return depth[u] + depth[v] - 2 * depth[lca];
	}
};

static int comp(const int a, const int b) {
	return depth[a] > depth[b];
}

int main() {
	int n, m; cin >> n >> m;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.dfs(0, 0);
	while (m--) {
		int k; cin >> k;
		subsetNodes.clear();  subsetNodes.resize(k);
		for (auto &x : subsetNodes) { cin >> x; x--; }
		if (k == 1) { cout << "YES" << endl; continue; }
		sort(subsetNodes.begin(), subsetNodes.end(), comp);

		int curLCA = t.LCA(subsetNodes[0], subsetNodes[1]), prevLCA;
		if (depth[subsetNodes[0]] - depth[curLCA] > 1 && depth[subsetNodes[1]] - depth[curLCA] > 1) { cout << "NO" << endl; continue; }
		prevLCA = curLCA;
		bool OK = true;
		for (int i = 2; i < k; i++) {
			curLCA = t.LCA(prevLCA, subsetNodes[i]);
			if (depth[subsetNodes[i]] - depth[curLCA] > 1) { OK = false; break; }
			prevLCA = curLCA;
		}
		cout << (OK ? "YES" : "NO") << endl;
	}
}