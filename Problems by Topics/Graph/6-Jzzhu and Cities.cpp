#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>
using namespace std;

struct edge {
	int u, v, w; bool b; edge() {}
	edge(int _u, int _v, int _w, bool nb) :
		u(_u), v(_v), w(_w), b(nb) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w, bool b) {
		edge e1(u, v, w, b), e2(v, u, w, b);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dijkstra_sp(int s, vector<pair<int, bool>> &parent) {
		vector<bool> visited(n, false); vector<long long> dist(n, 1e16);
		priority_queue <pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
		dist[s] = 0ll; pq.push({ 0, s });

		for (int i = 0; i < n; i++) {
			int cur = pq.top().second; pq.pop();
			while (visited[cur]) { cur = pq.top().second; pq.pop(); }
			visited[cur] = true;
			for (auto &e : nodes[cur].edges) {
				if (dist[e.v] > dist[cur] + e.w) {
					dist[e.v] = dist[cur] + e.w;
					parent[e.v] = {  e.u,e.b };
					pq.push({ dist[e.v], e.v });
				}
				else if (dist[e.v] == dist[cur] + e.w && !e.b) {
					dist[e.v] = dist[cur] + e.w;
					parent[e.v] = { e.u,e.b };
					pq.push({ dist[e.v], e.v });
				}
			}
		}
	}
};

int main() {
	int n, m, k; cin >> n >> m >> k;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v, w; cin >> u >> v >> w;
		u--; v--;
		g.add_edge(u, v, w, 0);
	}
	set<pair<int, int>> trains;
	int res = 0;
	for (int i = 0; i < k; i++) {
		int s, y; cin >> s >> y; s--;
		if (trains.count({ s,y }) != 0) { res++; }
		else { trains.insert({ s,y }); g.add_edge(0, s, y, 1); }
	}

	vector<pair<int,bool>> parent(n, { -1 , 0 });

	g.dijkstra_sp(0, parent);
	int cantrem = 0;
	for (int i = 1; i < n; i++) {
		int t = i;
		
		if (parent[t].first == 0 && parent[t].second) {
			cantrem++;
		}
	}

	res += trains.size() - cantrem;
	cout << res << endl;
}