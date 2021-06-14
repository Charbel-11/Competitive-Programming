#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

struct edge {
	int u, v; ll w, k; edge() {}
	edge(int _u, int _v, ll _w, ll _k) :
		u(_u), v(_v), w(_w), k(_k) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<ll> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

	void add_edge(int u, int v, ll w, ll k) {
		edge e1(u, v, w, k), e2(v, u, w, k);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dijkstra_sp(int s) {
		vector<bool> visited(n, false);
		priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
		dist[s] = 0ll; pq.push({ 0, s });

		while (!pq.empty()) {
			int cur = pq.top().second; pq.pop();
			if (visited[cur]) { continue; }
			visited[cur] = true;

			for (auto& e : nodes[cur].edges) {
				ll newD = dist[cur] + (e.k - (dist[cur] % e.k)) + e.w;
				if (dist[cur] % e.k == 0) { newD -= e.k; }
				if (dist[e.v] > newD) {
					dist[e.v] = newD;
					pq.push({ dist[e.v], e.v });
				}
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int N, M, X, Y; cin >> N >> M >> X >> Y; X--; Y--;
	graph g(N);
	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v; u--; v--;
		ll w, k; cin >> w >> k;
		g.add_edge(u, v, w, k);
	}

	g.dijkstra_sp(X);
	if (g.dist[Y] == INF) { cout << -1 << '\n'; }
	else { cout << g.dist[Y] << '\n'; }
}