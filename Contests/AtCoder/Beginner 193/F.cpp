#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const ll INF = 1ll << 40;

struct edge {
	int u, v; ll cap, flow = 0; edge() {}
	edge(int _u, int _v, ll _cap) :
		u(_u), v(_v), cap(_cap) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<edge> edges; int m = 0;
	vector<int> level, ptr;
	graph(int _n) : n(_n), nodes(_n), level(_n), ptr(_n) {}

	void add_edge(int u, int v, ll c1, ll c2) {
		nodes[u].edges.emplace_back(m++);
		nodes[v].edges.emplace_back(m++);
		edges.emplace_back(u, v, c1);
		edges.emplace_back(v, u, c1);
	}

	bool dinicBFS(const int& s, const int& t) {
		fill(level.begin(), level.end(), -1);
		queue<int> q; q.push(s); level[s] = 0;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& e : nodes[cur].edges) {
				if (edges[e].cap - edges[e].flow < 1) { continue; }
				if (level[edges[e].v] != -1) { continue; }
				level[edges[e].v] = level[cur] + 1;
				q.push(edges[e].v);
			}
		}
		return level[t] != -1;
	}

	ll dinicDFS(int cur, const int& t, ll flow) {
		if (!flow) { return 0; }
		if (cur == t) { return flow; }
		for (int& cid = ptr[cur]; cid < (int)nodes[cur].edges.size(); cid++) {
			int e = nodes[cur].edges[cid], v = edges[e].v;
			if (level[cur] + 1 != level[v] || edges[e].cap - edges[e].flow < 1) continue;
			ll new_flow = min(flow, edges[e].cap - edges[e].flow);
			new_flow = dinicDFS(v, t, new_flow); if (!new_flow) { continue; }
			edges[e].flow += new_flow; edges[e ^ 1].flow -= new_flow;
			return new_flow;
		}
		return 0;
	}

	ll maxFlow(int s, int t, ll prevFlow = 0) {
		ll res = prevFlow;
		while (dinicBFS(s, t)) {
			fill(ptr.begin(), ptr.end(), 0);
			while (ll flow = dinicDFS(s, t, INF)) { res += flow; }
		}
		return res;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n; cin >> n;
	vector<string> grid(n);
	for (auto& s : grid) { cin >> s; }

	graph g(n * n + 2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((i + j) % 2) {
				if (grid[i][j] == 'B') { grid[i][j] = 'W'; }
				else if (grid[i][j] == 'W') { grid[i][j] = 'B'; }
			}
			if (j < n - 1) { g.add_edge(i * n + j, i * n + j + 1, 1, 1); }
			if (i < n - 1) { g.add_edge(i * n + j, (i + 1) * n + j, 1, 1); }
			if (grid[i][j] == 'B') { g.add_edge(n * n, i * n + j, INF, 0); }
			if (grid[i][j] == 'W') { g.add_edge(i * n + j, n * n + 1, INF, 0); }
		}
	}

	cout << 2 * n * (n - 1) - g.maxFlow(n * n, n * n + 1) << '\n';
}