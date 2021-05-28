#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
vector<int> a;
ll res;
ll bits[21];

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> sz;
	int root, n;
	ll pathCount;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); sz.resize(n, 1); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void centroidDecomposition() {
		vector<bool> dead(n, false);
		CDRec(0, dead);
	}
	void CDRec(int start, vector<bool>& dead) {
		int c = getCentroid(start, dead);
		dead[c] = true;
		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			CDRec(e.v, dead);
		}

		pathCount = 0; resetBits();
		dfs(c, -1, 0, dead, 1);
		updateRes(); res += a[c];
		for (auto &e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			dfs(e.v, c, a[c], dead, 0);
			add(e.v, c, 0, dead);
			dfs(e.v, c, a[c], dead, 1);
		}

		dead[c] = false;
	}

	void dfs(int u, int p, int cur, vector<bool>& dead, bool dir) {
		cur ^= a[u];
		updateBits(cur, dir); 
		pathCount += (dir ? 1 : -1);

		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			dfs(e.v, u, cur, dead, dir);
		}
	}

	void add(int u, int p, int cur, vector<bool>& dead) {
		cur ^= a[u];
		updateResWithCur(cur);

		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			add(e.v, u, cur, dead);
		}
	}
	
	void resetBits() {
		for (int i = 0; i < 21; i++) { bits[i] = 0; }
	}

	void updateBits(int cur, bool dir) {
		for (int i = 0; i < 21; i++) {
			if (dir) bits[i] += ((cur >> i) & 1);
			else bits[i] -= ((cur >> i) & 1);
		}
	}

	void updateRes() {
		for (int i = 0; i < 21; i++) {
			res += (1ll << i)*bits[i];
		}
	}

	void updateResWithCur(int cur) {
		for (int i = 0; i < 21; i++) {
			if (cur >> i & 1) 
				res += (1ll << i)*(pathCount - bits[i]);
			else
				res += (1ll << i)*bits[i];
		}
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
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n); a.resize(n); res = 0;
	for (auto &x : a) { cin >> x; }

	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.resetBits();

	t.centroidDecomposition();
	cout << res/2 << endl;
}