#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = (ll)1e17;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n, diameter;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); diameter = 0; }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	int dfs(int u, int p) {
		int max1 = -1, max2 = -1;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			int cur = dfs(e.v, u);
			if (cur > max1) { max2 = max1; max1 = cur; }
			else if (cur > max2) { max2 = cur; }
		}

		diameter = max(diameter, max1 + max2 + 2);
		return max1 + 1;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	t.dfs(0, -1);
	cout << t.diameter << '\n';
}