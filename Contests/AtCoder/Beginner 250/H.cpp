#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <numeric>
using namespace std;
typedef long long ll;

const ll INF = 1e18;

struct DSU {
	vector<int> rank, parent;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}

	bool operator <(const edge& rhs) {
		return w < rhs.w;
	}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n, k;
	vector<ll> dist;
	graph(int _n, int _k) : n(_n), k(_k) { nodes.resize(n); dist.resize(n, INF); }

	//UNDIRECTED
	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dijkstra_sp() {
		vector<bool> visited(n, false);
		priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
		for (int s = 0; s < k; s++) {
			dist[s] = 0ll; pq.push({ 0, s });
		}

		while (!pq.empty()) {
			int cur = pq.top().second; pq.pop();
			if (visited[cur]) { continue; }
			visited[cur] = true;

			for (auto& e : nodes[cur].edges)
				if (dist[e.v] > dist[cur] + e.w) {
					dist[e.v] = dist[cur] + e.w;
					pq.push({ dist[e.v], e.v });
				}
		}
	}
};

struct query {
	int x, y, idx; ll t;
	query() {}
	query(int _x, int _y, ll _t, int id) :x(_x), y(_y), t(_t), idx(id) {}

	bool operator < (const query& rhs) {
		return t < rhs.t;
	}

	friend istream& operator >>(istream& is, query& rhs) {
		is >> rhs.x >> rhs.y >> rhs.t; 
		rhs.x--; rhs.y--;
		return is;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m, k; cin >> n >> m >> k;
	graph g(n, k);
	for (int i = 0; i < m; i++) {
		int u, v; ll c; cin >> u >> v >> c; u--; v--;
		g.add_edge(u, v, c);
	}

	int q; cin >> q;
	vector<bool> ans(q, false);
	vector<query> queries(q);
	for (int i = 0; i < q; i++) {
		cin >> queries[i];
		queries[i].idx = i;
	}
	sort(queries.begin(), queries.end());

	g.dijkstra_sp(); vector<edge> edges;
	for (int i = 0; i < n; i++) {
		for (auto& e : g.nodes[i].edges) {
			edges.push_back(e);
			edges.back().w += g.dist[e.u] + g.dist[e.v];
		}
	}
	sort(edges.begin(), edges.end());

	DSU dsu(n); int edgeIdx = 0;
	for (int i = 0; i < q; i++) {
		while (edgeIdx < edges.size() && edges[edgeIdx].w <= queries[i].t) {
			dsu.merge(edges[edgeIdx].u, edges[edgeIdx].v);
			edgeIdx++;
		}
		if (dsu.find(queries[i].x) == dsu.find(queries[i].y)) { ans[queries[i].idx] = true; }
	}

	for (int i = 0; i < q; i++) {
		cout << (ans[i] ? "Yes" : "No") << '\n';
	}
}