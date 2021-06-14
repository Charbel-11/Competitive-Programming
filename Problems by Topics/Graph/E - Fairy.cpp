//https://codeforces.com/contest/19/problem/E
#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	int u, v, id; edge() {}
	edge(int _u, int _v, int _id) :
		u(_u), v(_v), id(_id) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<int> color, badEdges, goodEdges, tin, parentEdge;
	int n, bEIdx, totalBE;

	graph(int _n) : n(_n) {
		nodes.resize(n); color.resize(n, -1);
		badEdges.resize(n, 0); goodEdges.resize(n, 0);
		tin.resize(n, 0); parentEdge.resize(n, -1);
	}

	void add_edge(int u, int v, int id) {
		edge e1(u, v, id); nodes[u].edges.push_back(e1);
		edge e2(v, u, id); nodes[v].edges.push_back(e2);
	}

	bool bipartite(int u) {
		bool OK = true;
		for (auto &e : nodes[u].edges) {
			if (color[e.v] != -1) {
				if (color[e.v] == color[u]) { OK = false; }
				continue;
			}
			color[e.v] = !color[e.u];
			bool b = bipartite(e.v);
			OK = OK & b;
		}
		return OK;
	}

	int findStateOfComponents() {
		int notB = -1;
		for (int i = 0; i < n; i++) {
			if (color[i] != -1) { continue; }

			color[i] = 0;
			bool b = bipartite(i);
			if (!b) {
				if (notB == -1) { notB = i; }
				else { return -2; }
			}
		}
		return notB;
	}

	void dfs(int u, int p, int &tS, vector<bool> &vis) {
		vis[u] = 1; tin[u] = tS++;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			if (vis[e.v]) { 
				if (tin[e.v] < tin[u]) {
					if (color[e.v] == color[e.u]) { totalBE++; bEIdx = e.id; badEdges[u]++; badEdges[e.v]--; }
					else { goodEdges[u]++; goodEdges[e.v]--; }
				}
				continue; 
			}		
			parentEdge[e.v] = e.id;
			dfs(e.v, u, tS, vis);
			badEdges[e.u] += badEdges[e.v];
			goodEdges[e.u] += goodEdges[e.v];
		}
	}

	void fix(int u) {
		int tS = 0; totalBE = 0;
		vector<bool> vis(n, 0);
		dfs(u, -1, tS, vis);

		vector<int> ans;
		if (totalBE == 1) { ans.push_back(bEIdx); }
		for (int i = 0; i < n; i++) {
			if (badEdges[i] == totalBE && goodEdges[i] == 0) { ans.push_back(parentEdge[i]); }
		}

		sort(ans.begin(), ans.end());
		cout << ans.size() << '\n';
		for (auto &x : ans) { cout << x << ' '; }
		cout << '\n';
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v, i + 1);
	}

	int state = g.findStateOfComponents();
	if (state == -2) { cout << 0 << '\n'; }
	else if (state == -1) { 
		cout << m << '\n';
		for (int i = 1; i <= m; i++) { cout << i << " "; }
		cout << '\n';
	}
	else { g.fix(state); }
}