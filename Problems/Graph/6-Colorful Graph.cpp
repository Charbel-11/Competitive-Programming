#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

vector<int> colors;

struct edge {
	int u, v;
	edge(int nu, int nv) { u = nu; v = nv; }
};

struct node { vector<edge> edges; };

struct graph{
	vector<node> nodes;
	map<int, set<int>> freq;

	graph(int n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void checkAdj(int u) {
		for (auto &e : nodes[u].edges) {
			if (colors[u] != colors[e.v]) {
				freq[colors[u]].insert(colors[e.v]);
			}
		}
	}
};

int main() {
	int n, m; cin >> n >> m;
	colors.resize(n); for (auto &x : colors) { cin >> x; }
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		u--; v--;
		g.add_edge(u, v);
	}

	for (int i = 0; i < n; i++) { g.checkAdj(i); }

	int curMax = 0, color = INT_MAX;
	if (g.freq.empty()) { color = *min_element(colors.begin(), colors.end()); }
	for (auto el : g.freq) {
		if (el.second.size() > curMax) {
			curMax = el.second.size();
			color = el.first;
		}
		else if (el.second.size() == curMax) {
			color = min(color, el.first);
		}
	}

	cout << color << endl;
}