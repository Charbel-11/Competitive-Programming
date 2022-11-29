#include <bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<edge> edges; int m;
	vector<int> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

	void add_edge(int u, int v, int w) {
		nodes[u].edges.push_back(edges.size());
		edge e1(u, v, w); edges.push_back(e1);
		m++;
	}

	void bellman_ford() {
		vector<int> parent(n, -1), v;

		for (int i = 0; i < n; i++) {
			v.clear();
			for (edge &e : edges) {
				//could be = INF and e.w<0, leading to an incorrect update since the node is unreachable
				//If we don't care about reachability from a source, remove the first check
				if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
					dist[e.v] = dist[e.u] + e.w;
					parent[e.v] = e.u;
					v.push_back(e.v);
				}
			}
		}

		if (v.empty()){}	//No neg weight cycle
		else {
			//The negative cycle(s) might not reach the destination, we should check with all nodes in v if needed
			//We know that each node in v belongs to some negative weight cycle

			//Here, we are finding one negative weight cycle
			int x = v[0];
			for (int i = 0; i < n; ++i) { x = parent[x]; }
			vector<int> cycle;
			for (int u = x;; u = parent[u]) {
				cycle.push_back(u);
				if (u == x && cycle.size() > 1) { break; }
			}
			reverse(cycle.begin(), cycle.end());
			cout << "Negative cycle: ";
			for (int &u : cycle) { cout << u << ' '; }
			cout << '\n';
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

}