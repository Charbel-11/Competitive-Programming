#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; int w; edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph() {}
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w) {
		edge e1(u, v, w); nodes[u].edges.push_back(e1);
	}
};

int n, m;
graph g;
vector<int> path;

bool check(double m) {
	vector<double> dist(n, 1e7); dist[0] = 0;
	vector<int> parent(n);
	for (int i = 0; i < n; i++) {
		for (auto& e : g.nodes[i].edges) {
			if (dist[e.v] > dist[e.u] + e.w - m) {
				dist[e.v] = dist[e.u] + e.w - m;
				parent[e.v] = e.u;
			}
		}
	}
	if (dist[n - 1] > 0) { return false; }

	path.clear();
	int cur = n - 1;
	while (cur != 0) {
		path.push_back(cur);
		cur = parent[cur];
	}
	path.push_back(0); 
	reverse(path.begin(), path.end());
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	g = graph(n);
	for (int i = 0; i < m; i++) {
		int u, v, c; cin >> u >> v >> c; u--; v--;
		g.add_edge(u, v, c);
	}

	double l = 0, r = 1e7, eps = 1e-6;
	while (r - l > eps) {
		double mid = (l + r) / 2.0;
		if (check(mid)) { r = mid; }
		else { l = mid; }
	}

	check(l);
	cout << path.size()-1 << '\n';
	for (auto& x : path) { cout << x + 1 << ' '; }
}