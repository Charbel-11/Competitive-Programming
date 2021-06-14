#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { 
	vector<edge> edges;
	int dist;
	set<int> possibleNext;

	node() : dist(INT_MAX) {}
};

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v);
		nodes[u].edges.push_back(e1);
	}

	void bfs(int u) {
		vector<int> visited(n, 0);
		queue<int> q; q.push(u);
		visited[u] = true; nodes[u].dist = 0;
		while (!q.empty()) {
			int f = q.front(); q.pop();
			for (auto &x : nodes[f].edges) {
				int dest = x.v;
				if (visited[dest] == false) {
					q.push(dest); visited[dest] = true;
					nodes[dest].dist = nodes[f].dist + 1;
					nodes[dest].possibleNext.insert(f);
				}
				else {
					if (nodes[dest].dist == nodes[f].dist + 1) {
						nodes[dest].possibleNext.insert(f);
					}
				}
			}
		}
	}

	int minRebuild(vector<int>& path) {
		int ans = 0; int k = path.size();
		for (int i = 0; i < k - 1; i++) {
			int cur = path[i];
			int pathDist = k - i - 1;
			
			if (nodes[cur].possibleNext.count(path[i+1]) == 0) { ans++; }
		}
		return ans;
	}

	int maxRebuild(vector<int>& path) {
		int ans = 0;  int k = path.size();
		for (int i = 0; i < k - 1; i++) {
			int cur = path[i];
			int pathDist = k - i - 1;

			if (nodes[cur].possibleNext.count(path[i + 1]) == 0) { ans++; }
			else if (nodes[cur].possibleNext.size() > 1) { ans++; }
		}
		return ans;
	}
};

int main() {
	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(v, u);		//reverse edge
	}

	int k; cin >> k;
	vector<int> path(k);
	for (auto &x : path) { cin >> x; x--; }
	
	g.bfs(path.back());

	cout << g.minRebuild(path) << " " << g.maxRebuild(path) << endl;
}