#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

struct node {
	set<int> edges;
};

struct graph {
	vector<node> nodes; vector<int> deg;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); deg.resize(n, 0); }

	void add_edge(int u, int v) {
		nodes[u].edges.insert(v);
		nodes[v].edges.insert(u);
		deg[u]++; deg[v]++;
	}
};

int main() {
	int n, m; cin >> n >> m;
	graph g(n);

	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	int bestNode = 0;
	for (int i = 1; i < n; i++) {
		if (g.deg[i] < g.deg[bestNode]) {
			bestNode = i;
		}
	}

	set<int> left;
	for (auto &e : g.nodes[bestNode].edges) {
		left.insert(e);
	}

	queue<int> Q;
	for (int i = 0; i < n; i++) {
		if (i == bestNode) { continue; }
		if (left.count(i) == 0) {
			Q.push(i);
		}
	}

	while(!Q.empty()){
		int cur = Q.front(); Q.pop();
		set<int>::iterator it = left.begin();
		while(it != left.end()){
			if (g.nodes[cur].edges.count(*it) == 0) {
				Q.push(*it);
				it = left.erase(it);
				continue;
			}
			it++;
		}
	}

	int res = 0;

	while (!left.empty()) {
		Q.push(*left.begin()); res++; left.erase(left.begin());
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			set<int>::iterator it = left.begin();
			while (it != left.end()) {
				if (g.nodes[cur].edges.count(*it) == 0) {
					Q.push(*it);
					it = left.erase(it);
					continue;
				}
				it++;
			}
		}
	}

	cout << res << endl;
}