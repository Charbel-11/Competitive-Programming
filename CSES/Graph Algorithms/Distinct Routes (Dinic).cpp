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

	void add_edge(const int u, const int v, const ll c1, const ll c2 = 0) {
		nodes[u].edges.emplace_back(m++);
		nodes[v].edges.emplace_back(m++);
		edges.emplace_back(u, v, c1);
		edges.emplace_back(v, u, c2);
	}

	bool getLevelGraph(const int s, const int t) {
		fill(level.begin(), level.end(), -1);
		queue<int> q; q.push(s); level[s] = 0;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& e : nodes[cur].edges) {
				if (edges[e].cap == edges[e].flow || level[edges[e].v] != -1) { continue; }
				level[edges[e].v] = level[cur] + 1;
				q.push(edges[e].v);
			}
		}

		return level[t] != -1;
	}

	ll findAugmentingPath(const int cur, const int t, const ll flow) {
		if (flow == 0) { return 0; }
		if (cur == t) { return flow; }

		for (int& eid = ptr[cur]; eid < (int)nodes[cur].edges.size(); eid++) {
			int e = nodes[cur].edges[eid], v = edges[e].v;
			if (level[v] != level[cur] + 1 || edges[e].cap == edges[e].flow) { continue; }

			ll newFlow = min(flow, edges[e].cap - edges[e].flow);
			newFlow = findAugmentingPath(v, t, newFlow);
			if (!newFlow) { continue; }

			edges[e].flow += newFlow; edges[e ^ 1].flow -= newFlow;
			return newFlow;
		}

		return 0;
	}

	// O(EV^2) for general graphs
	// O(Emin(V^2/3,E^1/2)) for unit-capacity networks (every edge has capacity 1)
	// O(Eroot(V)) for simple unit-capacity networks (network where every edge has capacity 1 and every node other than s,t has either 1 entering or 1 leaving edge)
	ll maxFlowDinic(const int s, const int t) {
		ll res = 0;
		while (getLevelGraph(s, t)) {
			fill(ptr.begin(), ptr.end(), 0);

			ll curFlow = findAugmentingPath(s, t, INF);
			while (curFlow) {
				res += curFlow;
				curFlow = findAugmentingPath(s, t, INF);
			}
		}
		return res;
	}

	void getPath(const int u, vector<int>& path) {
		path.push_back(u);
		for (int eId : nodes[u].edges) {
			auto& e = edges[eId];
			if (e.flow <= 0) { continue; }
			e.flow = 0; getPath(e.v, path);
			break;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v, 1);
	}

	int ans = g.maxFlowDinic(0, n - 1);
	cout << ans << '\n';

	while (ans--) {
		vector<int> cur; g.getPath(0, cur);
		cout << cur.size() << '\n';
		for (auto &x : cur) { cout << x + 1 << ' '; } 
		cout << '\n';
	}
}