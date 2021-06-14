#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
vector<int> ans;

struct edge {
	int u, v;
	int w;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node {
	int id; vector<edge> edges;
};

struct graph {
	vector<node> nodes;
	vector<int> dist;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	void bfs(int start) {
		vector<bool> visited(n, 0); 
		queue<int> q; q.push(start); visited[start] = 1;
		dist[start] = 0;
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				visited[e.v] = 1; q.push(e.v);
				dist[e.v] = dist[e.u] + 1;
				ans[dist[e.v]]++;
			}
		}
	}
};

int main() {
	int N; cin >> N;
	graph g(N);
	for (int i = 1; i < N; i++) {
		g.add_edge(i - 1, i);
	}
	int X, Y; cin >> X >> Y; X--; Y--;
	g.add_edge(X, Y);
	ans.resize(N, 0);
	for (int i = 0; i < N; i++) {
		g.bfs(i);
	}

	for (int i = 1; i < N; i++) {
		cout << ans[i]/2 << endl;
	}
}