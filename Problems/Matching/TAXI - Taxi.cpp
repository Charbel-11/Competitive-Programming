#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

struct edge {
	int u, v; bool matched = 0; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool matched = 0; vector<edge> edges; };

struct bipartiteGraph {
	vector<node> nodes; int n, m;
	vector<int> match;
	vector<bool> vis;

	//Vertices on the left should have indices 0..n-1
	//Vertices on the right should have indices n..n+m-1
	bipartiteGraph(int _n, int _m) : n(_n), m(_m) {
		nodes.resize(n + m);
		match.resize(n + m, -1); vis.resize(n + m, 0);
	}
	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	bool augment(int v) {
		if (vis[v]) { return 0; }
		vis[v] = 1;
		for (auto &e : nodes[v].edges) {
			if (match[e.v] == -1 || augment(match[e.v])) {
				match[e.v] = v; match[v] = e.v;
				return 1;
			}
		}
		return 0;
	}

	int matching() {	//With greedy initialization
		int w = 0;
		for (int x = 0; x < n; x++) {
			if (match[x] != -1) { continue; }
			for (auto &e : nodes[x].edges) {
				if (match[e.v] == -1) {
					match[e.v] = x; match[x] = e.v;
					w++;  break;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (match[i] != -1) { continue; }
			for (int j = 0; j < n; j++) { vis[j] = 0; }
			w += augment(i);
		}
		return w;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int k; cin >> k;
	while (k--) {
		int p, t; ll s, tl; cin >> p >> t >> s >> tl;
		bipartiteGraph g(p, t);
		
		vector<pair<int, int>> persons(p);
		for (int i = 0; i < p; i++) {
			int x, y; cin >> x >> y; 
			persons[i] = { x,y };
		}
		vector<pair<int, int>> taxis(t);
		for (int i = 0; i < t; i++) {
			int x, y; cin >> x >> y;
			taxis[i] = { x,y };
		}

		for (int i = 0; i < p; i++) {
			for (int j = 0; j < t; j++) {
				ll dist = 200ll * (abs(persons[i].first - taxis[j].first) + abs(persons[i].second - taxis[j].second));
				if (dist <= s * tl) { g.add_edge(i, j + p); }
			}
		}

		cout << g.matching() << endl;
	}
}