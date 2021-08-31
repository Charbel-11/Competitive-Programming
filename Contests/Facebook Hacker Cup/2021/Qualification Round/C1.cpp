#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>
#include <climits>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int val; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	int findMaxPath(int u, int p) {
		int bestChildVal = 0;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			int cur = findMaxPath(e.v, u);
			bestChildVal = max(bestChildVal, cur);
		}
		return bestChildVal + nodes[u].val;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		tree g(n);
		for (int i = 0; i < n; i++) { ifs >> g.nodes[i].val; }

		for (int i = 0; i < n - 1; i++) {
			int u, v; ifs >> u >> v; u--; v--;
			g.add_edge(u, v);
		}

		vector<int> cand;
		for (auto& e : g.nodes[0].edges) {
			cand.push_back(g.findMaxPath(e.v, 0));
		}
		sort(cand.rbegin(), cand.rend());
		int ans = g.nodes[0].val;
		if (cand.size() > 0) { ans += cand[0]; }
		if (cand.size() > 1) { ans += cand[1]; }

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}