#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes[2]; int n;
	//_n considers both true and false variables, i.e. n = 2*number of variables
	graph(int _n) : n(_n) { nodes[0].resize(n); nodes[1].resize(n); }

	//Add the close bu(u) OR bv(v)
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

	//Returns a labeling of vertices such that u and v have the same label iff they are strongly connected
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

	//Returns a valid assignment or an empty vector if it is not satisfiable 
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
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin.ignore(2); return 0;
}