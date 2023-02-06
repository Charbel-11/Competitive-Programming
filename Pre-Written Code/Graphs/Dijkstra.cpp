#include <bits/stdc++.h>
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
	vector<ll> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

	//UNDIRECTED
	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dijkstra_sp(int s, vector<int> &parent) {
		vector<bool> visited(n, false);
		priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
		dist[s] = 0ll; pq.push({ 0, s });

		while(!pq.empty()) {
			int cur = pq.top().second; pq.pop();
			if (visited[cur]) { continue; }
			visited[cur] = true;

			for (auto &e : nodes[cur].edges)
				if (dist[e.v] > dist[cur] + e.w) {
					dist[e.v] = dist[cur] + e.w;
					parent[e.v] = e.u;
					pq.push({ dist[e.v], e.v });
				}
		}
	}
	void dijkstra_printPath(int s, int d, vector<int> &parent) {
		stack<int> S; S.push(d); int cur = d;
		while (parent[cur] != -1) { cur = parent[cur]; S.push(cur); }
		while (!S.empty()) { cout << S.top() << ' '; S.pop(); }
		cout << '\n';
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

}