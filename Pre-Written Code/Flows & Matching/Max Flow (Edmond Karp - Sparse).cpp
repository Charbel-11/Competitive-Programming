#include <bits/stdc++.h>
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
	vector<int> parent;

	graph(int _n) : n(_n), nodes(_n), parent(_n) {}

	void add_edge(const int u, const int v, const ll c1, const ll c2 = 0) {
		nodes[u].edges.emplace_back(m++);
		nodes[v].edges.emplace_back(m++);
		edges.emplace_back(u, v, c1);
		edges.emplace_back(v, u, c2);
	}

	//O(VE^2)
	ll maxFlow(const int s, const int t) {
		ll flow = 0, newFlow = findAugmentingPath(s, t);

		while (newFlow) {
			flow += newFlow; int cur = t;
			while (cur != s) {
				int &e = parent[cur];
				edges[e].flow += newFlow;
				edges[e ^ 1].flow -= newFlow;
				cur = edges[e].u;
			}
			newFlow = findAugmentingPath(s, t);
		}
		return flow;
	}

	ll findAugmentingPath(const int s, const int t) {
		fill(parent.begin(), parent.end(), -1); parent[s] = -2;
		queue<pair<int, ll>> q; q.push({ s, INF }); 

		while (!q.empty()) {
			int cur = q.front().first; ll flow = q.front().second; q.pop();
			for (auto& e : nodes[cur].edges) {
				int next = edges[e].v;
				if (parent[next] != -1 || edges[e].cap == edges[e].flow) { continue; }
				parent[next] = e;

				ll newFlow = min(flow, edges[e].cap - edges[e].flow);
				if (next == t) { return newFlow; }
				q.push({ next, newFlow });
			}
		}
		return 0ll;
	}

	//Assumes we already called maxFlow()
	vector<edge> getMinCut() {
		vector<edge> ans;
		for (int i = 0; i < m; i += 2) {
			int u = edges[i].u, v = edges[i].v;
			if ((parent[u] != -1) ^ (parent[v] != -1)) {
				ans.push_back(edges[i]);
			}
		}
		return move(ans);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

}