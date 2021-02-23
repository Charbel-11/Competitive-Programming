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

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void bfs(int u, vector<bool> &visited) {
		queue<int> q; q.push(u);
		visited[u] = true;
		while (!q.empty()) {
			int f = q.front(); q.pop();
			node& n = nodes[f];
			for (auto &x : n.edges) {
				int dest = x.v;
				if (visited[dest] == false) {
					q.push(dest); visited[dest] = true;
				}
			}
		}
	}

	void dfs(int u, vector<bool> &visited) {
		stack<int> s; s.push(u);
		visited[u] = true;
		while (!s.empty()) {
			int f = s.top(); s.pop();
			node& n = nodes[f];
			for (auto &x : n.edges) {
				int dest = x.v;
				if (visited[dest] == false) {
					s.push(dest); visited[dest] = true;
				}
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin.ignore(2); return 0;
}