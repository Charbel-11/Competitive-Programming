#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>
#include <climits>
using namespace std;

typedef long long ll;

int lg2;
struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct Tree {
	vector<node> nodes;
	vector<int> sz;
	vector<int> depth, size, parent;
	vector<vector<int>> bLift;
	vector<int> ans;
	int root, n;

	Tree(int _n, int _r = 0) : n(_n), root(_r) { 
		lg2 = int(log2(n));
		nodes.resize(n); sz.resize(n, 1); ans.resize(n, INT_MAX/4); parent.resize(n, 0);
		bLift.resize(n + 1); for (auto &x : bLift) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0);
		size.resize(n, 1);
	}

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
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

	void centroidDecomposition() {
		vector<bool> dead(n, false);
		CDRec(0, dead);
	}

	Tree build_CDT() {
		Tree CDT(n);
		vector<bool> dead(n, false);
		CDUtil(0, -1, dead, CDT);
		return move(CDT);
	}

	void update(int v, Tree& t) {
		ans[v] = 0;
		int cur = parent[v];
		while (cur != -1) {
			ans[cur] = min(ans[cur], t.dist(cur, v));
			cur = parent[cur];
		}
	}

	void query(int v, Tree& t) {
		int res = ans[v];
		int cur = parent[v];
		while (cur != -1) {
			res = min(res, ans[cur] + t.dist(cur, v));
			cur = parent[cur];
		}

		cout << res << endl;
	}

private:
	int subtreeN;
	int getCentroid(int root, vector<bool>& dead) {
		getSize(root, -1, dead);
		subtreeN = sz[root];
		return findCentroid(root, -1, dead);
	}
	void getSize(int u, int p, vector<bool>& dead) {
		sz[u] = 1;
		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			getSize(e.v, u, dead);
			sz[u] += sz[e.v];
		}
	}
	int findCentroid(int u, int p, vector<bool>& dead) {
		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			if (sz[e.v] > subtreeN / 2) { return findCentroid(e.v, u, dead); }
		}
		return u;
	}

	//DOES NOT BUILD A TREE
	void CDRec(int start, vector<bool>& dead) {
		int c = getCentroid(start, dead);
		dead[c] = true;

		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			CDRec(e.v, dead);
		}
		//ADD REQUIRED CODE
		//...
		dead[c] = false;
	}

	//BUILD THE CENTROID TREE
	void CDUtil(int start, int par, vector<bool>& dead, Tree &CDT) {
		int c = getCentroid(start, dead);
		if (par != -1) { CDT.add_edge(c, par); CDT.parent[c] = par; }
		else { CDT.root = c; CDT.parent[c] = -1; }

		dead[c] = true;
		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			CDUtil(e.v, c, dead, CDT);
		}
		dead[c] = false;
	}

	int dist(int u, int v) {
		int l = LCA(u, v);
		return depth[u] + depth[v] - 2 * depth[l];
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	Tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.dfs(0, 0);
	Tree centroidTree = t.build_CDT();
	centroidTree.update(0, t);
	for (int i = 0; i < m; i++) {
		int t1, v; cin >> t1 >> v; v--;
		if (t1 == 1)centroidTree.update(v, t);
		else centroidTree.query(v, t);
	}
}