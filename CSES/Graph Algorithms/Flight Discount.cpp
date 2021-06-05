#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<vector<ll>> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, vector<ll>(2, INF)); }

	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w);
		nodes[u].edges.push_back(e1);
	}

	void dijkstra_sp(int s) {
		vector<vector<bool>> visited(n, vector<bool>(2, false));
		priority_queue <pair<pair<ll, int>, bool>, vector<pair<pair<ll, int>, bool>>, greater<pair<pair<ll, int>, bool>>> pq;
		dist[s][0] = dist[s][1] = 0ll; pq.push({ { 0, s }, 0 });

		while(!pq.empty()){
			int cur = pq.top().first.second; 
			bool used = pq.top().second; pq.pop();
			while (!pq.empty() && visited[cur][used]) { cur = pq.top().first.second; used = pq.top().second; pq.pop(); }
			if (visited[cur][used]) { break; } visited[cur][used] = true;

			for (auto &e : nodes[cur].edges) {
				if (dist[e.v][used] > dist[cur][used] + e.w) {
					dist[e.v][used] = dist[cur][used] + e.w;
					pq.push({ { dist[e.v][used], e.v }, used });
				}
				if (!used) {
					if (dist[e.v][1] > dist[cur][0] + e.w / 2) {
						dist[e.v][1] = dist[cur][0] + e.w / 2;
						pq.push({ { dist[e.v][1], e.v }, 1 });
					}
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
		int u, v; ll c; cin >> u >> v >> c; u--; v--;
		g.add_edge(u, v, c);
	}

	g.dijkstra_sp(0);
	cout << g.dist[n - 1][1] << '\n';
}