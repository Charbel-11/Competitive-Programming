#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
const ll INF = 1e17;

vector<bool> color;
vector<int> res;

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		if (color[u]) { res[u]++; }
		else { res[u]--; }

		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }

			dfs(e.v, u);
			if (res[e.v] > 0) { res[u] += res[e.v]; }
		}
	}

	void dfs2(int u, int p) {
		if (p != -1 && res[p] > 0) { 
			int deduct = (res[u] > 0 ? res[u] : 0);
			res[u] = max(res[u], res[u] + (res[p] - deduct));
		}

		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs2(e.v, u);
		}
	}
};

int main() {
	int n; cin >> n;
	tree t(n);

	color.resize(n);
	for (int i = 0; i < n; i++) {
		int temp; cin >> temp;
		color[i] = temp;
	}

	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	res.resize(n, 0);
	t.dfs(0, -1);
	t.dfs2(0, -1);

	for (int i = 0; i < n; i++) {
		cout << res[i] << " ";
	}cout << endl;
}