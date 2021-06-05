#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
ll INF = 1ll << 40;

struct edge {
	int u, v, id, dual; edge() {}
	edge(int _u, int _v, int _id, int _d) :
		u(_u), v(_v), id(_id), dual(_id + _d) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<edge> edges;
	vector<ll> capacity, eflow;
	vector<int> parent;

	graph(int _n) : n(_n), nodes(_n), parent(_n) {}

	void add_edge(int u, int v, ll c) {
		nodes[u].edges.emplace_back(capacity.size());
		nodes[v].edges.emplace_back(capacity.size() + 1);
		edges.emplace_back(u, v, capacity.size(), 1);
		edges.emplace_back(v, u, capacity.size() + 1, -1);
		capacity.push_back(c); capacity.push_back(0); //Change if undirected
		eflow.push_back(0); eflow.push_back(0);
	}

	ll maxflow(int s, int t) {
		ll flow = 0, new_flow = maxFlowBFS(s, t, parent);

		while (new_flow) {
			flow += new_flow; int cur = t;
			while (cur != s) {
				edge &e = edges[parent[cur]];
				capacity[e.id] -= new_flow;
				capacity[e.dual] += new_flow;
				eflow[e.id] += new_flow;
				eflow[e.dual] -= new_flow;
				cur = e.u;
			}
			new_flow = maxFlowBFS(s, t, parent);
		}
		return flow;
	}

	ll maxFlowBFS(const int &s, const int &t, vector<int> &parent) {
		fill(parent.begin(), parent.end(), -1); parent[s] = -2;
		queue<pair<int, ll>> q; q.push({ s, INF });

		while (!q.empty()) {
			int cur = q.front().first; ll flow = q.front().second; q.pop();
			for (auto &e : nodes[cur].edges) {
				int next = edges[e].v, id = edges[e].id;
				if (parent[next] == -1 && capacity[id]) {
					parent[next] = e;
					ll new_flow = min(flow, capacity[id]);
					if (next == t) { return new_flow; }
					q.push({ next, new_flow });
				}
			}
		}
		return 0ll;
	}

	void dfs(int u, vector<int> &ans) {
		ans.push_back(u);
		for (auto &eIdx : nodes[u].edges) {
			auto &e = edges[eIdx];
			if (eflow[e.id] == 1) {
				eflow[e.id] = 0;
				int v = (e.v == u ? e.u : e.v);
				dfs(v, ans);
				return;
			}
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

	int ans = g.maxflow(0, n - 1);
	cout << ans << '\n';
	vector<int> cur;
	while (ans--) {
		g.dfs(0, cur);
		cout << cur.size() << '\n';
		for (auto &x : cur) { cout << x + 1 << ' '; } cout << '\n';
		cur.clear();
	}
}