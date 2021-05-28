#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
typedef long long ll;
ll INF = 1ll << 40;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) : u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<vector<ll>> capacity;
	vector<int> parent; int n;

	graph(int _n) : n(_n), parent(_n), nodes(_n), capacity(_n, vector<ll>(_n)) {}

	void add_edge(int u, int v, ll c) {
		nodes[u].edges.emplace_back(u, v);
		nodes[v].edges.emplace_back(v, u);
		capacity[u][v] = c;	//directed edge
	}

	//O(VE^2)
	ll maxflow(int s, int t, int prevFlow = 0) {
		ll flow = prevFlow, new_flow = maxFlowBFS(s, t, parent);

		while (new_flow) {
			flow += new_flow; int cur = t;
			while (cur != s) {
				int prev = parent[cur];
				capacity[prev][cur] -= new_flow;
				capacity[cur][prev] += new_flow;
				cur = prev;
			}
			new_flow = maxFlowBFS(s, t, parent);
		}
		return flow;
	}

	ll maxFlowBFS(int s, int t, vector<int>& parent) {
		fill(parent.begin(), parent.end(), -1); parent[s] = -2;
		queue<pair<int, ll>> q; q.push({ s, INF });

		while (!q.empty()) {
			int cur = q.front().first; ll flow = q.front().second; q.pop();
			for (auto &e : nodes[cur].edges) {
				int next = e.v;
				if (parent[next] == -1 && capacity[cur][next]) {
					parent[next] = cur;
					ll new_flow = min(flow, capacity[cur][next]);
					if (next == t) { return new_flow; }
					q.push({ next, new_flow });
				}
			}
		}
		return 0ll;
	}
};

vector<string> v; int n;
int in(int i, int j, int d) { return 2 * (n * n * d + i * n + j); }
int out(int i, int j, int d) { return 2 * (n * n * d + i * n + j) + 1; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int test = 1; cin >> n; while (n) {
		v.resize(n); for (auto &x : v) { cin >> x; }
		graph g(2 * n * n * n * n + 2); int turns = n - 1;
		int source = g.n - 2, sink = g.n - 1;
		for (int i = 0; i < n; i++) {
			g.add_edge(source, in(i, 0, 0), 1);
			for (int j = 0; j < n; j++) {
				if (v[i][j] == 'X') { continue; }
				for (int t = 0; t <= turns; t++) {
					if (j == n - 1) { g.add_edge(out(i, j, t), sink, 1); }
					g.add_edge(in(i, j, t), out(i, j, t), 1); //Edge in->out
					g.add_edge(out(i, j, t), in(i, j, t + 1), 1); //Edge for waiting
					if (i != 0) { g.add_edge(out(i, j, t), in(i - 1, j, t + 1), 1); }
					if (j != 0) { g.add_edge(out(i, j, t), in(i, j - 1, t + 1), 1); }
					if (i != n - 1) { g.add_edge(out(i, j, t), in(i + 1, j, t + 1), 1); }
					if (j != n - 1) { g.add_edge(out(i, j, t), in(i, j + 1, t + 1), 1); }
				}
			}
		}
		int maxFlow = g.maxflow(source, sink);
		while (maxFlow != n) {
			turns++; for(int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					if (v[i][j] == 'X') { continue; }
					g.add_edge(in(i, j, turns), out(i, j, turns), 1); //Edge in->out
					g.add_edge(out(i, j, turns), in(i, j, turns + 1), 1); //Edge for waiting
					if (j == n - 1) { g.add_edge(out(i, j, turns), sink, 1); }
					if (i != 0) { g.add_edge(out(i, j, turns), in(i - 1, j, turns + 1), 1); }
					if (j != 0) { g.add_edge(out(i, j, turns), in(i, j - 1, turns + 1), 1); }
					if (i != n - 1) { g.add_edge(out(i, j, turns), in(i + 1, j, turns + 1), 1); }
					if (j != n - 1) { g.add_edge(out(i, j, turns), in(i, j + 1, turns + 1), 1); }
				}
			maxFlow = g.maxflow(source, sink, maxFlow);
		}
		cout << "Case " << test++ << ": " << turns << endl; cin >> n;
	}

	cin.ignore(2); return 0;
}