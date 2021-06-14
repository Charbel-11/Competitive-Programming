#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <stack>

using namespace std;
typedef long long ll;

vector<int> robots;

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
	bool operator < (const edge &rhs) const { return w < rhs.w; }
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	ll dfs(int u, int p, int i, int j) {
		if (i > j) { return 0; }

		ll ans = 0;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			int cut = upper_bound(robots.begin() + i, robots.begin() + j + 1, e.w) - robots.begin();
			if (cut == j + 1) { continue; }
			ans += dfs(e.v, u, cut, j);	j = cut - 1;
		}
		ans += (ll)(j - i + 1)*(u + 1);

		return ans;
	}
};

int main() {
	int T; cin >> T;
	while (T--) {
		int n, q; cin >> n >> q; graph g(n);
		robots.clear(); robots.resize(q);
		for (int i = 0; i < n - 1; i++) {
			int u, v, w; cin >> u >> v >> w;
			u--; v--; g.add_edge(u, v, w);
		}

		for (auto &x : robots) { cin >> x; }
		sort(robots.begin(), robots.end());
		for (int i = 0; i < g.n; i++)
			sort(g.nodes[i].edges.rbegin(), g.nodes[i].edges.rend());

		cout << g.dfs(0, -1, 0, q - 1) << endl;
	}
}