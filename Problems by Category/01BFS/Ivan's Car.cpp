//https://acm.timus.ru/problem.aspx?space=1&num=1930

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;
typedef long long ll;
const int INF = 1 << 30;
int r, c;

struct edge {
	int u, v; bool up;
	edge() {}
	edge(int _u, int _v, bool b) :u(_u), v(_v), up(b) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) :n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v, 1), e2(v, u, 0);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	//Assumes all weights are either 0 or x for a fixed x >= 0
	//Returns the shortest distance from s to all nodes
	vector<vector<int>> bfs01(int s) {
		vector<vector<bool>> visited(n, vector<bool>(2, 0));
		vector<vector<int>> dist(n, vector<int>(2, INF)); dist[s][0] = dist[s][1] = 0;
		deque<pair<int, bool>> dq; dq.push_back({ s,0 }); dq.push_back({ s,1 });

		while (!dq.empty()) {
			int cur = dq.front().first; bool b = dq.front().second; dq.pop_front();
			while (visited[cur][b] && !dq.empty()) { cur = dq.front().first; b = dq.front().second; dq.pop_front(); }
			if (visited[cur][b]) { break; } visited[cur][b] = 1;
			
			for (auto &e : nodes[cur].edges) {
				int w = e.up != b;
				if (visited[e.v][e.up] || dist[e.v][e.up] < dist[cur][b] + w) { continue; }
				dist[e.v][e.up] = dist[cur][b] + w;
				if (w) { dq.push_back({ e.v,e.up }); }
				else { dq.push_front({ e.v,e.up }); }
			}
		}

		return move(dist);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}
	int s, d; cin >> s >> d; s--; d--;
	auto v = g.bfs01(s);

	cout << min(v[d][0], v[d][1]) << '\n';
}
