#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<bool> isGood;

	graph(int _n) :n(_n) { nodes.resize(n); isGood.resize(n, 0); }

	void addEdge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	void cycleDFS(int u, vector<int>& color) {
		color[u] = 1;
		for (auto& e : nodes[u].edges) {
			int v = e.v;
			if (color[v] == 0) {
				cycleDFS(v, color);
				if (isGood[v]) { isGood[u] = 1; }
			}
			else if (color[v] == 1) { isGood[u] = 1; }
			else{ 
				if (isGood[v]) { isGood[u] = 1; }
			}
		}
		color[u] = 2;
	}
	int numGoodVertices() {
		vector<int> color(n, 0);
		for (int v = 0; v < n; v++) {
			if (color[v] != 0) { continue; }
			cycleDFS(v, color);
		}

		int ans = 0;
		for (int i = 0; i < n; i++) { ans += isGood[i]; }
		return ans;
	}


};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n); 
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.addEdge(u, v);
	}

	cout << g.numGoodVertices() << '\n';
}