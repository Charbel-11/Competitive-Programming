#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;
const ll mod = 1000 * 1000 * 1000 + 7;
const ll INF = 1ll << 60;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { 
	int minLen, maxLen; ll numPath;
	vector<edge> edges;
	
	node() {minLen = maxLen = numPath = 0; }
};

struct graph {
	vector<node> nodes; int n;
	vector<ll> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w);
		nodes[u].edges.push_back(e1);
	}

	void dijkstra_sp(int s) {
		vector<bool> visited(n, false);
		priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
		dist[s] = 0ll; pq.push({ 0, s });
		nodes[s].minLen = nodes[s].maxLen = 0; nodes[s].numPath = 1;

		for (int i = 0; i < n; i++) {
			int cur = pq.top().second; pq.pop();
			while (visited[cur]) { cur = pq.top().second; pq.pop(); }
			visited[cur] = true;
			for (auto &e : nodes[cur].edges) {
				if (dist[e.v] > dist[cur] + e.w) {
					dist[e.v] = dist[cur] + e.w;
					nodes[e.v].minLen = nodes[e.u].minLen + 1;
					nodes[e.v].maxLen = nodes[e.u].maxLen + 1;
					nodes[e.v].numPath = nodes[e.u].numPath;
					pq.push({ dist[e.v], e.v });
				}
				else if (dist[e.v] == dist[cur] + e.w) {
					nodes[e.v].minLen = min(nodes[e.v].minLen, nodes[e.u].minLen + 1);
					nodes[e.v].maxLen = max(nodes[e.v].maxLen, nodes[e.u].maxLen + 1);
					nodes[e.v].numPath += nodes[e.u].numPath; nodes[e.v].numPath %= mod;
				}
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; ll w; cin >> u >> v >> w; u--; v--;
		g.add_edge(u, v, w);
	}

	g.dijkstra_sp(0);
	cout << g.dist[n - 1] << ' ' << g.nodes[n - 1].numPath << ' ' << g.nodes[n - 1].minLen << ' ' << g.nodes[n - 1].maxLen << '\n';
}