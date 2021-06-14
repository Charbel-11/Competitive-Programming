#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;

vector<ll> bpf;
int spf[1000009];

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < 1000009; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) &&
			primes[j] <= spf[i] && i * primes[j] < 1000009; j++)
			spf[i * primes[j]] = primes[j];
	}
}

vector<int> factorize(int x) {
	vector<int> res;
	while (x != 1) {
		int d = spf[x]; res.push_back(d);
		while (x % d == 0) { x /= d; }
	}
	return move(res);
}

struct edge {
	int u, v, id; ll w; edge() {}
	edge(int _u, int _v, ll _w, int _id) :
		u(_u), v(_v), w(_w), id(_id) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n = 0;
	vector<edge> edges; int m = 0;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, ll w) {
		nodes[u].edges.push_back(m); edge e1(u, v, w, m++);
		nodes[v].edges.push_back(m); edge e2(v, u, w, m++);
		edges.push_back(e1); edges.push_back(e2);
	}

	ll dijkstra(int s, int k, int t) {
		vector<vector<ll>> dist(n, vector<ll>(k + 1, (ll)1e15));
		priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, greater<pair<ll, pair<int, int>>>> pq;
		dist[s][0] = 0;
		pq.push({ 0, {s, 0} });

		while (!pq.empty()) {
			pair<ll, pair<int, int>> cur = pq.top(); pq.pop();
			int cur_id = cur.second.first; int cur_k = cur.second.second;
			if (dist[cur_id][cur_k] < cur.first) { continue; }	

			for (auto &eIdx : nodes[cur_id].edges) {
				auto &e = edges[eIdx];
				if (dist[e.v][cur_k] > dist[cur_id][cur_k] + e.w) {
					dist[e.v][cur_k] = dist[cur_id][cur_k] + e.w;
					pq.push({ dist[e.v][cur_k], {e.v, cur_k} });
				}
				if (cur_k == k || bpf[e.id] >= e.w) { continue; }
				if (dist[e.v][cur_k + 1] > dist[cur_id][cur_k] + bpf[e.id]) {
					dist[e.v][cur_k + 1] = dist[cur_id][cur_k] + bpf[e.id];
					pq.push({ dist[e.v][cur_k + 1], {e.v, cur_k + 1} });
				}
			}
		}
		return *min_element(dist[t].begin(), dist[t].end());
	}
};

void fill_bpf(const graph &g) {
	bpf.clear(); bpf.resize(g.m);
	for (auto &e : g.edges) {
		vector<int> pf = factorize(e.w);
		ll res = 1000 * 1000 * 1000;
		for (int &y : pf)
			res = min(res, (e.w / y) + (2 * y));
		bpf[e.id] = res;	
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int T; cin >> T; buildSieve();
	while (T--) {
		int n, m, k; cin >> n >> m >> k;
		graph g(n);
		for (int i = 0; i < m; i++) {
			int u, v, w; cin >> u >> v >> w; u--; v--;
			g.add_edge(u, v, w);
		}
		int s, e; cin >> s >> e; s--; e--;
		fill_bpf(g);

		ll res = g.dijkstra(s, k, e);
		cout << (res == (ll)1e15 ? -1 : res) << endl;
	}
}