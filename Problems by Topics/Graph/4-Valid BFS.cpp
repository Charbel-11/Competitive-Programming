#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

struct node {
	set<int> edges;
};

struct graph {
	vector<node> nodes;
	vector<bool> visited;

	graph(int n) { nodes.resize(n); visited.resize(n, false); }

	void add_edge(int u, int v) {
		nodes[u].edges.insert(v);
		nodes[v].edges.insert(u);
	}
};

int main() {
	int n; cin >> n;
	graph g(n);

	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; 
		u--; v--;
		g.add_edge(u, v);
	}

	vector<int> bfsI(n);
	for (auto &x : bfsI) { cin >> x; x--; }
	if (bfsI[0] != 0) { cout << "NO" << endl; return 0; }

	int j = 1, prevJ = 1;
	vector<int> visited(n, 0); visited[0] = true;
	for (int i = 0; i < n; i++) {
		for (auto &x : g.nodes[bfsI[i]].edges) {
			if (visited[x]) { continue; }
			visited[x] = true;
			if (g.nodes[bfsI[i]].edges.count(bfsI[j]) == 0) { cout << "NO" << endl; return 0; }
			j++;
		}
		prevJ = j;
	}
	cout << "YES" << endl;
}