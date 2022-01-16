// https://codeforces.com/gym/100513/problem/L

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct edge {
	int u, v, idx; edge() {}
	edge(int _u, int _v, int _idx = -1) :
		u(_u), v(_v), idx(_idx) {}
};
struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> start, finish;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { 
		nodes.resize(n);
		start.resize(n, -1); finish.resize(n, -1);
	}

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p, int &t) {
		start[u] = t; t++;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u, t);
		}
		finish[u] = t; t++;
	}

	bool isAncestor(int u, int v) {
		return start[u] <= start[v] && start[v] <= finish[u];
	}
};

struct graph {
	int n; vector<node> nodes[2];
	vector<int> idxToOrder, orderToIdx;
	vector<int> dsuParent, minToDsuParIdx;
	vector<int> sdom, dom, parent;			
	vector<vector<int>> bucket;

	graph(int _n) : n(_n) {
		nodes[0].resize(n);
		idxToOrder.resize(n, -1); orderToIdx.resize(n, -1);
		parent.resize(n);  bucket.resize(n);

		minToDsuParIdx.resize(n); dsuParent.resize(n);
		iota(minToDsuParIdx.begin(), minToDsuParIdx.end(), 0);
		iota(dsuParent.begin(), dsuParent.end(), 0);

		sdom.resize(n); dom.resize(n);
		iota(sdom.begin(), sdom.end(), 0);
		iota(dom.begin(), dom.end(), 0);
	}

	void add_edge(int u, int v, int idx) {
		nodes[0][u].edges.push_back(edge(u, v, idx));
	}

	tree getDominatorTree(int S) {
		nodes[1].clear(); nodes[1].resize(n);
		int t = 0; dfs0(S, t);
		int initialN = n; n = t;

		buildDom(); tree T(initialN, S);
		for (int i = 1; i < n; i++) {
			T.add_edge(orderToIdx[i], orderToIdx[dom[i]]);
		}

		n = initialN;
		return move(T);
	}

private:
	void dfs0(int u, int& t) {
		idxToOrder[u] = t; orderToIdx[t] = u; t++;
		for (auto& e : nodes[0][u].edges) {
			if (idxToOrder[e.v] == -1) {
				dfs0(e.v, t);
				parent[idxToOrder[e.v]] = idxToOrder[e.u];
			}
			nodes[1][e.v].edges.push_back(edge(e.v, e.u));	
		}
	}

	int find(int u, int x = 0) {
		if (u == dsuParent[u]) { return x ? -1 : u; }
		int v = find(dsuParent[u], x + 1);
		if (v < 0) { return u; }

		if (sdom[minToDsuParIdx[dsuParent[u]]] < sdom[minToDsuParIdx[u]]) {
			minToDsuParIdx[u] = minToDsuParIdx[dsuParent[u]];
		}
		dsuParent[u] = v;
		return x ? v : minToDsuParIdx[u];
	}
	void merge(int u, int v) { dsuParent[v] = u; }

	void buildDom() {
		for (int i = n - 1; i >= 0; i--) {
			for (auto& e : nodes[1][orderToIdx[i]].edges) {
				sdom[i] = min(sdom[i], sdom[find(idxToOrder[e.v])]);
			}
			if (i > 0) { bucket[sdom[i]].push_back(i); }

			for (int w : bucket[i]) {
				int v = find(w);
				if (sdom[v] == sdom[w]) { dom[w] = sdom[w]; }
				else { dom[w] = v; }
			}
			if (i > 0) { merge(parent[i], i); }
		}

		for (int i = 1; i < n; i++) {
			if (dom[i] != sdom[i]) { dom[i] = dom[dom[i]]; }
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	while (true) {
		int n, m; cin >> n >> m;
		if (cin.fail()) { break; }

		graph g(n);
		for (int i = 0; i < m; i++) {
			int u, v; cin >> u >> v; u--; v--;
			g.add_edge(u, v, i + 1);
		}

		tree domT = g.getDominatorTree(0);
		int t = 0; domT.dfs(0, -1, t);

		vector<int> ans;
		for (int i = 0; i < n; i++) {
			if (domT.start[i] == -1) { continue; }
			for (auto& e : g.nodes[0][i].edges) {
				if (!domT.isAncestor(e.v, e.u)) { ans.push_back(e.idx); }
			}
		}

		sort(ans.begin(), ans.end());
		cout << ans.size() << '\n';
		for (auto& x : ans) { cout << x << ' '; }
		cout << '\n';
	}
}