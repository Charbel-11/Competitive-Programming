#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll ans = 0;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct Tree {
	vector<node> nodes;
	vector<int> sz;
	vector<ll> curP;
	int root = 0, n, k;

	Tree(int _n, int _k = 0) : n(_n), k(_k) { nodes.resize(n); sz.resize(n, 1); curP.resize(k + 1, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void centroidDecomposition() {
		vector<bool> dead(n, false);
		CDRec(0, dead);
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
		for (auto e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			if (sz[e.v] > subtreeN / 2) { return findCentroid(e.v, u, dead); }
		}
		return u;
	}

	void CDRec(int start, vector<bool>& dead) {
		int c = getCentroid(start, dead);
		dead[c] = true;

		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			CDRec(e.v, dead);
		}
		
		dfs(c, -1, 0, dead, 0);
		ans += curP[k]; curP[0] = 0;

		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			dfs(e.v, c, 1, dead, 1);
			addNeeded(e.v, c, 1, dead);
		}

		dead[c] = false;
	}

	void dfs(int u, int p, int level, vector<bool>& dead, bool dir) {
		curP[level] += (dir ? -1 : 1);
		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			dfs(e.v, u, level + 1, dead, dir);
		}
	}
	void addNeeded(int u, int p, int level, vector<bool>& dead) {
		if (level >= k) { return; }
		ans += curP[k - level];

		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			addNeeded(e.v, u, level + 1, dead);
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, k; cin >> n >> k;
	Tree t(n, k);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.centroidDecomposition();
	cout << ans << '\n';
}