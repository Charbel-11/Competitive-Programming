#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;
typedef long long ll;

string label;
vector<ll> res, partial;
int total = 't' - 'a' + 1;
vector<int> occ;
vector<bool> good;

struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> sz;
	int n;

	tree(int _n) : n(_n){ nodes.resize(n); sz.resize(n, 1); partial.resize(n+1, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
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

		dfs(c, -1, 1, 0, dead, 1);
		int cur = 1 << (label[c] - 'a');

		//Disabling then enabling the subtrees are here needed since we need to count for each vertices how
		//many pathes go through it. If we keep the first subtree disabled, the vertices of the other subtrees
		//won't have counted paths passing through them and going to the first subtree
		//We still need to deal with double counting on the root
		ll bef = res[c]; occ[cur]--;
		for (auto& e : nodes[c].edges) {
			if (dead[e.v]) { continue; }
			dfs(e.v, c, 1, cur, dead, 0);

			addNeeded(e.v, c, 1, 0, dead);
			res[c] += partial[1];

			dfs(e.v, c, 1, cur, dead, 1);		
		}
		res[c] -= bef; res[c] /= 2; res[c] += bef;

		occ[cur]++;
		dfsReset(c, -1, 0, dead);

		dead[c] = false;
	}

	void dfs(int u, int p, int level, int cur, vector<bool>& dead, bool dir) {
		partial[level] = 0;
		
		int now = label[u] - 'a';
		cur ^= (1 << now);
		if (good[cur])
			partial[level] += (dir ? 1 : -1);
		
		occ[cur] += (dir ? 1 : -1);

		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			dfs(e.v, u, level+1, cur, dead, dir);
			partial[level] += partial[level + 1];
		}

		res[u] += partial[level];
	}

	void dfsReset(int u, int p, int cur, vector<bool>& dead) {
		int now = label[u] - 'a';
		cur ^= (1 << now);
		occ[cur]--;

		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			dfsReset(e.v, u, cur, dead);
		}
	}
	
	void addNeeded(int& u, int& p, int level, int cur, vector<bool>& dead) {
		partial[level] = 0;
		int now = label[u] - 'a';
		cur ^= (1 << now);
		partial[level] += occ[cur];

		int finish = 1 << total;
		for (int target = 1; target < finish; (target <<= 1)) {
			partial[level] += occ[cur^target];
		}

		for (auto& e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			addNeeded(e.v, u, level + 1, cur, dead);
			partial[level] += partial[level + 1];
		}

		res[u] += partial[level];
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
	tree t(n); res.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	cin >> label;
	int finish = 1 << total;
	good.resize(finish + 1, 0);
	occ.resize(finish + 1, 0);
	good[0] = 1;
	for (int target = 1; target < finish; (target <<= 1)) { good[target] = 1; }

	t.centroidDecomposition();

	for (auto &x : res) { cout << x << " "; } cout << endl;
}