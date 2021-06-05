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
	vector<int> comp;
	graph(int _n) : n(_n) { nodes[0].resize(n); nodes[1].resize(n); comp.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[0][u].edges.push_back(e1);
		nodes[1][v].edges.push_back(e2);
	}
	//Adds u or v
	void addOr(int u, int v) {
		edge e1, e2;
		if (u % 2) { e1 = edge(u - 1, v); }
		else { e1 = edge(u + 1, v); }
		if (v % 2) { e2 = edge(v - 1, u); }
		else { e2 = edge(v + 1, u); }

		nodes[0][u].edges.push_back(e1);
		nodes[1][v].edges.push_back(e2);
	}

	void scc_dfs1(int v, vector<bool> &used, vector<int> &order) {
		used[v] = true;
		for (auto &x : nodes[0][v].edges)
			if (!used[x.v]) { scc_dfs1(x.v, used, order); }
		order.push_back(v);
	}
	void scc_dfs2(int v, vector<bool> &used, int cnt) {
		used[v] = true; comp[v] = cnt;
		for (auto &x : nodes[1][v].edges)
			if (!used[x.v]) { scc_dfs2(x.v, used, cnt); }
	}

	void SCC() {
		vector<bool> used(n, false);
		vector<int> order; int cnt = 0;
		for (int i = 0; i < n; i++)
			if (!used[i]) { scc_dfs1(i, used, order); }
		used.assign(n, false);
		for (int i = 0; i < n; i++) {
			int v = order[n - 1 - i];
			if (!used[v]) { scc_dfs2(v, used, cnt++); }
		}
	}

	//returns false if impossible
	bool SAT2() {
		SCC();

		vector<bool> assignment(n / 2, false);
		for (int i = 0; i < n; i += 2) {
			if (comp[i] == comp[i + 1]) { return false; }
			assignment[i / 2] = comp[i] > comp[i + 1];
		}
		return true;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	
}