#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll INF = 1ll << 40;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :	u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<vector<ll>> capacity;
	vector<int> parent; int n;

	graph(int _n) : n(_n), parent(_n), nodes(_n), capacity(_n, vector<ll>(_n, 0)) {}

	void add_edge(const int u, const int v, const ll c1, const ll c2 = 0) {
		nodes[u].edges.emplace_back(u, v);
		nodes[v].edges.emplace_back(v, u);
		capacity[u][v] += c1; 
		capacity[v][u] += c2;
	}

	//O(VE^2)
	ll maxFlow(const int s, const int t) {
		ll flow = 0, newFlow = findAugmentingPath(s, t);

		while (newFlow) {
			flow += newFlow; int cur = t;
			while (cur != s) {
				int prev = parent[cur];
				capacity[prev][cur] -= newFlow;
				capacity[cur][prev] += newFlow;
				cur = prev;
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
				int next = e.v;
				if (parent[next] != -1 || capacity[cur][next] <= 0) { continue; }
				parent[next] = cur;

				ll new_flow = min(flow, capacity[cur][next]);
				if (next == t) { return new_flow; }
				q.push({ next, new_flow });
			}
		}
		return 0ll;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

}