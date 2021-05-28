//https://codeforces.com/contest/1473/problem/F
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 1 << 30;

struct edge {
	int u, v, cap, flow = 0; edge() {}
	edge(int _u, int _v, int _cap) :
		u(_u), v(_v), cap(_cap) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<edge> edges; int m = 0;
	vector<int> level, ptr;
	graph(int _n) : n(_n), nodes(_n), level(_n), ptr(_n) {}

	void add_edge(int u, int v, int c1, int c2 = 0) {
		nodes[u].edges.emplace_back(m++);
		nodes[v].edges.emplace_back(m++);
		edges.emplace_back(u, v, c1);
		edges.emplace_back(v, u, c2);
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

	int dinicDFS(int cur, const int& t, int flow) {
		if (!flow) { return 0; }
		if (cur == t) { return flow; }
		for (int& cid = ptr[cur]; cid < (int)nodes[cur].edges.size(); cid++) {
			int e = nodes[cur].edges[cid], v = edges[e].v;
			if (level[cur] + 1 != level[v] || edges[e].cap - edges[e].flow < 1) continue;
			int new_flow = min(flow, edges[e].cap - edges[e].flow);
			new_flow = dinicDFS(v, t, new_flow); if (!new_flow) { continue; }
			edges[e].flow += new_flow; edges[e ^ 1].flow -= new_flow;
			return new_flow;
		}
		return 0;
	}

	int maxFlow(int s, int t, int prevFlow = 0) {
		int res = prevFlow;
		while (dinicBFS(s, t)) {
			fill(ptr.begin(), ptr.end(), 0);
			while (int flow = dinicDFS(s, t, INF)) { res += flow; }
		}
		return res;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n; cin >> n; 
	vector<int> a(n); for (auto& x : a) { cin >> x; }
	vector<int> b(n); for (auto& x : b) { cin >> x; }

	vector<int> lastOcc(101, -1);
	graph g(n + 2); int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= a[i]; j++) {
			if (a[i] % j == 0 && lastOcc[j] != -1) { g.add_edge(i, lastOcc[j], INF); }
		}
		lastOcc[a[i]] = i;
		if (b[i] > 0) { g.add_edge(n, i, b[i]); ans += b[i]; }
		else { g.add_edge(i, n + 1, -b[i]); }
	}

	cout << ans - g.maxFlow(n, n + 1) << '\n';
}