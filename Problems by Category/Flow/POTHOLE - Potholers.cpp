//https://www.spoj.com/problems/POTHOLE

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <climits>
using namespace std;

typedef long long ll;
int INF = INT_MAX;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) : u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<vector<int>> capacity;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); capacity.resize(n, vector<int>(n, 0)); }

	void add_edge(int u, int v, int c) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
		capacity[u][v] = c;	//directed edge
	}

	//O(VE^2)
	int maxflow(int s, int t) {
		vector<int> parent(n);
		int flow = 0, new_flow = bfs(s, t, parent);

		while (new_flow) {
			flow += new_flow;
			int cur = t;
			while (cur != s) {
				int prev = parent[cur];
				capacity[prev][cur] -= new_flow;
				capacity[cur][prev] += new_flow;
				cur = prev;
			}
			new_flow = bfs(s, t, parent);
		}

		return flow;
	}
private:
	int bfs(int s, int t, vector<int>& parent) {
		fill(parent.begin(), parent.end(), -1);
		parent[s] = -2;
		queue<pair<int, int>> q; q.push({ s, INF });

		while (!q.empty()) {
			int cur = q.front().first, flow = q.front().second; q.pop();
			for (auto &e : nodes[cur].edges) {
				int next = e.v;
				if (parent[next] == -1 && capacity[cur][next]) {
					parent[next] = cur;
					int new_flow = min(flow, capacity[cur][next]);
					if (next == t) { return new_flow; }
					q.push({ next, new_flow });
				}
			}
		}
		return 0;
	}
};

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		graph g(n);
		for (int i = 0; i < n - 1; i++) {
			int tmp; cin >> tmp;
			while (tmp--) {
				int v; cin >> v; v--;
				if (i==0 || v == n-1) g.add_edge(i, v, 1);
				else { g.add_edge(i, v, n + 1); }
			}
		}

		cout << g.maxflow(0, n-1) << endl;
	}
}