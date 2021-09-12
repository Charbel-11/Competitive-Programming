#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	bool dead = false;
	int u, v, idx;
	edge() {}
	edge(int _u, int _v, int _idx) :
		u(_u), v(_v), idx(_idx) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes;
	vector<edge> edges;
	int n, m;

	graph(int _n, int _m) : n(_n), m(_m) { nodes.resize(n); }

	void add_edge(int u, int v, int idx) {
		edge e1(u, v, idx); nodes[u].edges.push_back(idx);
		edges.push_back(e1);
	}

	int bfs(vector<int>& path) {
		queue<int> Q; vector<bool> vis(n, false);
		vector<int> dist(n, n + 1);
		vector<int> parentEdge(n, -1), parentNode(n, -1);
		dist[0] = 0; Q.push(0); vis[0] = true;

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto& e : nodes[cur].edges) {
				if (edges[e].dead) { continue; }
				int curV = edges[e].v;

				if (!vis[curV]) { 
					dist[curV] = dist[cur] + 1;
					vis[curV] = true; Q.push(curV); 
					parentEdge[curV] = edges[e].idx;
					parentNode[curV] = cur;
				}
			}
		}

		if (dist[n - 1] == n + 1) { return -1; }

		path.clear(); int curNode = n - 1;
		while (curNode != 0) {
			path.push_back(parentEdge[curNode]);
			curNode = parentNode[curNode];
		}

		return dist[n - 1];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n, m);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v, i);
	}

	vector<int> ans(m, -1);

	vector<int> path;
	int minD = g.bfs(path);

	unordered_set<int> usedInPath;
	for (auto& p : path) { usedInPath.insert(p); }
	for (int i = 0; i < m; i++) {
		if (usedInPath.count(i)) {
			g.edges[i].dead = true;
			ans[i] = g.bfs(path);
			g.edges[i].dead = false;
		}
		else { ans[i] = minD; }
	}

	for (int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}
}