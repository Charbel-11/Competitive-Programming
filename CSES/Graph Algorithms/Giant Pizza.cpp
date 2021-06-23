#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

//variable k has idx 2k and not k has idx 2k+1
struct graph {
	vector<node> nodes[2]; int n;
	graph(int _n) : n(_n) { nodes[0].resize(n); nodes[1].resize(n); }

	//Adds bu or bv
	void add_edge(int u, int v, bool bu, bool bv) {
		int pu = u << 1 | !bu, pv = v << 1 | !bv;
		int nu = u << 1 | bu, nv = v << 1 | bv;
		add_edge(nu, pv); add_edge(nv, pu);
	}
	void add_edge(int u, int v) {
		nodes[0][u].edges.emplace_back(u, v);
		nodes[1][v].edges.emplace_back(v, u);
	}

	void scc_dfs1(int v, vector<bool> &used, vector<int> &order) {
		used[v] = true;
		for (auto &x : nodes[0][v].edges)
			if (!used[x.v]) { scc_dfs1(x.v, used, order); }
		order.push_back(v);
	}

	void scc_dfs2(int v, vector<bool> &used, vector<int> &component) {
		used[v] = true;
		component.push_back(v);
		for (auto &x : nodes[1][v].edges)
			if (!used[x.v]) { scc_dfs2(x.v, used, component); }
	}

	vector<int> SCC(int &t) {
		vector<bool> used(n, false);
		vector<int> order, component, scc(n);
		for (int i = 0; i < n; i++)
			if (!used[i]) { scc_dfs1(i, used, order); }
		used.assign(n, false);
		for (int i = 0; i < n; i++) {
			int v = order[n - 1 - i];
			if (!used[v]) {
				scc_dfs2(v, used, component);
				for (auto &x : component) { scc[x] = t; }
				component.clear(); t++;
			}
		}
		return move(scc);
	}

	vector<int> TWOSAT() {
		int t = 0; vector<int> scc = SCC(t);
		vector<int> res(n >> 1);
		for (int i = 0; i < n; i += 2) {
			if (scc[i] == scc[i + 1]) { return vector<int>(); }
			res[i >> 1] = scc[i] > scc[i + 1];
		}
		return move(res);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(2 * m);
	for (int i = 0; i < n; i++) {
		char c1; cin >> c1;
		int x; cin >> x; x--;
		char c2; cin >> c2;
		int y; cin >> y; y--;

		bool bx = 1, by = 1;
		if (c1 == '-') { bx = 0; }
		if (c2 == '-') { by = 0; }

		g.add_edge(x, y, bx, by);
	}

	vector<int> res = g.TWOSAT();
	if (res.empty()) { cout << "IMPOSSIBLE\n"; }
	else {
		for (int i = 0; i < m; i++) {
			cout << (res[i] ? '+' : '-') << ' ';
		}
		cout << '\n';
	}
}