//https://codeforces.com/contest/1467/problem/E
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int freq[(int)2e5 + 5];
int curPath[(int)2e5 + 5];

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool isDistRoot = true; int val = 0; vector<edge> edges; };

struct Tree {
	vector<node> nodes;
	vector<int> sz;
	int root, n;

	Tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); sz.resize(n, 1); }

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
		
		int repCnt = 0;
		freq[nodes[c].val]++; 
		curPath[nodes[c].val]++;
		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			if (!dfs(e.v, c, dead, 1)) {
				nodes[c].isDistRoot = false;
				repCnt++;
			}
		}

		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			if (!dfs(e.v, c, dead, 0)) { repCnt--; }
			check(e.v, c, repCnt == 0, dead);
			if (!dfs(e.v, c, dead, 1)) { repCnt++; }
		}
		curPath[nodes[c].val]--;

		dfs(c, -1, dead, 0);

		dead[c] = false;
	}

	bool dfs(int u, int p, vector<bool>& dead, bool dir) {
		int val = nodes[u].val;
		freq[val] = freq[val] + (dir ? 1 : -1);

		bool OK = true;
		if (curPath[val]) { OK = false; }
		curPath[val]++;

		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			bool b = dfs(e.v, e.u, dead, dir);
			OK = OK && b;
		}

		curPath[val]--;
		return OK;
	}
	void check(int u, int p, bool dist, vector<bool>& dead) {
		if (!dist) { nodes[u].isDistRoot = false; }

		int val = nodes[u].val;
		if (freq[val] || curPath[val]) { nodes[u].isDistRoot = dist = false; }

		curPath[val]++;
		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			check(e.v, e.u, dist, dead);
		}
		curPath[val]--;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n; cin >> n;
	Tree t(n);
	vector<int> comp;
	for (int i = 0; i < n; i++) { cin >> t.nodes[i].val; comp.push_back(t.nodes[i].val); }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	for (int i = 0; i < n; i++) {
		t.nodes[i].val = lower_bound(comp.begin(), comp.end(), t.nodes[i].val) - comp.begin();
	}

	t.centroidDecomposition();

	int ans = 0;
	for (int i = 0; i < n; i++) { ans += t.nodes[i].isDistRoot; }
	cout << ans << '\n';
}