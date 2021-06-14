#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
int n, a, b;
struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> subtreeSize, parent, path;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); subtreeSize.resize(n, 0); parent.resize(n, -1); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		subtreeSize[u] = 1;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u); parent[e.v] = u;
			subtreeSize[u] += subtreeSize[e.v];
		}
	}

	void generatePath(int u) {
		path.push_back(u);
		while (parent[u] != -1) {
			path.push_back(parent[u]);
			u = parent[u];
		}
	}

	ll numCities() {
		int cur = a; ll res = 0;
		while (!path.empty()) {
			int child = path.back(); path.pop_back();
			res += ((ll)subtreeSize[child] * (ll)(subtreeSize[cur] - subtreeSize[child]));
			cur = child;
		}
		return res;
	}
};

int main() {
	int T; cin >> T;
	while (T--) {
		cin >> n >> a >> b; a--; b--;
		tree t(n, a);
		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			t.add_edge(u, v);
		}

		t.dfs(a, -1);
		t.generatePath(b);
		cout << t.numCities() << endl;
	}
}