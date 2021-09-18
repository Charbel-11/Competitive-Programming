#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>
using namespace std;

vector<bitset<50000>> dp;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes[2]; int n;
	graph(int _n) : n(_n) { nodes[0].resize(n); nodes[1].resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[0][u].edges.push_back(e1);
		nodes[1][v].edges.push_back(e2);
	}

	void scc_dfs1(int v, vector<bool>& used, vector<int>& order) {
		used[v] = true;
		for (auto& x : nodes[0][v].edges)
			if (!used[x.v]) { scc_dfs1(x.v, used, order); }
		order.push_back(v);
	}

	void scc_dfs2(int v, vector<bool>& used, vector<int>& component) {
		used[v] = true;
		component.push_back(v);
		for (auto& x : nodes[1][v].edges)
			if (!used[x.v]) { scc_dfs2(x.v, used, component); }
	}

	//Returns a labeling of vertices such that u and v have the same label iff they are strongly connected
	vector<int> SCC(int& t) {
		vector<bool> used(n, false);
		vector<int> order, component, scc(n);
		for (int i = 0; i < n; i++)
			if (!used[i]) { scc_dfs1(i, used, order); }
		used.assign(n, false);
		for (int i = 0; i < n; i++) {
			int v = order[n - 1 - i];
			if (!used[v]) {
				scc_dfs2(v, used, component);
				for (auto& x : component) { scc[x] = t; }
				component.clear(); t++;
			}
		}
		return move(scc);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m, q; cin >> n >> m >> q;
	graph g(n); dp.resize(n, bitset<50000>(0));
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	int N = 0; vector<int> scc = g.SCC(N);
	vector<pair<int, int>> topSort;
	for (int i = 0; i < n; i++) { topSort.push_back({ scc[i], i }); }
	sort(topSort.rbegin(), topSort.rend());

	for (int i = 0; i < n; i++) {
		int u = topSort[i].second; dp[scc[u]][scc[u]] = 1;
		for (auto& e : g.nodes[0][u].edges) {
			dp[scc[u]] |= dp[scc[e.v]];
		}
	}

	while (q--) {
		int u, v; cin >> u >> v; u--; v--;
		if (dp[scc[u]][scc[v]]) { cout << "YES\n"; }
		else { cout << "NO\n"; }
	}
}