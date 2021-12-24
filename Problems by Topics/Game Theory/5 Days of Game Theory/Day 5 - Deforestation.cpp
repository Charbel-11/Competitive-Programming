#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> GN;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { 
		nodes.resize(n); GN.resize(n); 
	}

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		int curGN = 0;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			curGN ^= (GN[e.v] + 1);
		}
		GN[u] = curGN;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		tree t(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			t.add_edge(u, v);
		}

		t.dfs(0, -1);
		if (t.GN[0] > 0) { cout << "Alice" << '\n'; }
		else { cout << "Bob" << '\n'; }
	}
}