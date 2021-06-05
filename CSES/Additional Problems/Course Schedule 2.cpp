#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int inD = 0; vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		nodes[v].inD++;
	}

	//Returns the lexicographically smallest top sort (needs the in degree of each node)
	vector<int> maxTopSort() {
		priority_queue<int> Q; vector<int> ans;
		for (int i = 0; i < n; i++) {
			if (nodes[i].inD == 0) { Q.push(i); }
		}
		while (!Q.empty()) {
			int cur = Q.top(); Q.pop();
			ans.push_back(cur);
			for (auto& e : nodes[cur].edges) {
				nodes[e.v].inD--;
				if (nodes[e.v].inD == 0) { Q.push(e.v); }
			}
		}
		return move(ans);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(v, u);
	}

	vector<int> ans = g.maxTopSort();
	reverse(ans.begin(), ans.end());
	for (auto& x : ans) { cout << x + 1 << ' '; }
	cout << '\n';
}