#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
const ll INF = 1ll << 60;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct graph {
	vector<vector<int>> nodes; int n;
	vector<edge> edges; int m = 0;
	vector<int> O; vector<vector<int>> ONodes;

	graph(int _n) : n(_n), nodes(_n) {}

	void add_edge(int u, int v, int w) {
		nodes[u].emplace_back(m++);
		edges.emplace_back(u, v, w);
		nodes[v].emplace_back(m++);
		edges.emplace_back(v, u, w);
	}

	vector<ll> dijkstra(int s, vector<int>& parent) {
		vector<ll> dist(n, INF); dist[s] = 0ll;
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
		pq.push({ 0, s }); vector<bool> visited(n, false);

		while (!pq.empty()) {
			if (visited[pq.top().second]) { pq.pop(); continue; }
			int cur = pq.top().second; pq.pop(); visited[cur] = true;
			for (int& x : nodes[cur]) {
				edge& e = edges[x]; ll newD = dist[cur] + e.w;
				if (dist[e.v] > newD) {
					dist[e.v] = newD; parent[e.v] = cur;
					pq.push({ dist[e.v], e.v });
				}
			}
		}
		return move(dist);
	}

	vector<ll> dijkstra(int s) {
		vector<ll> dist(n, INF); dist[s] = 0;
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
		pq.push({ 0, s }); vector<bool> visited(n, false);

		while (!pq.empty()) {
			if (visited[pq.top().second]) { pq.pop(); continue; }
			int cur = pq.top().second; pq.pop(); visited[cur] = true;
			for (int& x : nodes[cur]) {
				edge& e = edges[x]; ll newD = dist[cur] + e.w;
				if (dist[e.v] > newD) pq.push({ dist[e.v] = newD, e.v });
			}
		}
		return move(dist);
	}

	int dfsO(int cur, const int &id, vector<int>& par) {
		int res = 1; O[cur] = id; for (auto& x : nodes[cur]) {
			edge& e = edges[x];
			if (par[e.v] != cur) { continue; }
			res += dfsO(edges[x].v, id, par);
		}
		return res;
	}

	int mostVitalPoint(int s, int t) {
		vector<int> SPT(n, -1);
		vector<ll> SGT = dijkstra(t), SGS = dijkstra(s, SPT);

		vector<int> path; path.emplace_back(t);
		while (path.back() != s) { path.emplace_back(SPT[path.back()]); }
		reverse(path.begin(), path.end()); int K = (int)path.size();
		int useless = -2; vector<bool> vis(n, false);
		for (auto& x : path) vis[x] = true;
		for (int i = 0; i < n; i++) if (!vis[i]) { useless = i; break; }

		//Finding for each node to what O-component it belongs
		O.resize(n, -1); ONodes.resize(K); vector<int> S(K);
		for (int i = 0; i < K; i++) {
			O[path[i]] = i; for (auto& x : nodes[path[i]]) {
				if (i != K - 1 && edges[x].v == path[i + 1]) { continue; }
				if (SPT[edges[x].v] == path[i]) S[i] += dfsO(edges[x].v, i, SPT);
			}
		}

		for (int i = 0; i < K; i++) ONodes[i].reserve(S[i]);
		for (int i = 0; i < n; i++) ONodes[O[i]].emplace_back(i);

		vector<vector<int>> EUO(K);
		vector<vector<int>> EOO(n);
		for (int i = 0; i < (int)edges.size(); i++) {
			if (edges[i].u == SPT[edges[i].v]) { continue; }
			edge& e = edges[i];	if (O[e.u] > O[e.v]) { continue; }
			if (O[e.u] < O[e.v] && e.v != path[O[e.v]]) { EUO[O[e.v]].emplace_back(i); continue; }
			if (e.u != path[O[e.u]] && e.v != path[O[e.v]]) EOO[e.u].emplace_back(i);
		}

		//Giving nodes of O[0] respective distances
		vector<ll> PGD(n, INF); PGD[s] = 0;
		for (auto& x : ONodes[0]) PGD[x] = SGS[x];

		ll res = SGS[t]; int resIdx = -1;
		set<pair<ll, int>> H; vector<ll> key(n, INF);
		for (int i = 0; i < n; i++) if (O[i] > 1) H.insert({ INF, i });
		
		for (int i = 1; i < K - 1; i++) {

			if (i != 1) {
				H.erase({ key[path[i]], path[i] });
				for (auto& x : ONodes[i]) { H.erase({ key[x], x }); }
			}

			priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
			for (auto& x : EUO[i]) { edge& e = edges[x]; pq.push({ SGS[e.u] + e.w, e.v }); }

			while (!pq.empty()) {
				int cur = pq.top().second; if (PGD[cur] != INF) { pq.pop(); continue; }

				ll W = pq.top().first; pq.pop(); PGD[cur] = W;
				for (int& x : EOO[cur]) { edge& e = edges[x]; pq.push({ PGD[cur] + e.w, e.v }); }
			}

			ONodes[i - 1].emplace_back(path[i - 1]);
			for (auto& y : ONodes[i - 1]) for (auto& x : nodes[y]) {
				edge& e = edges[x]; if (!H.count({ key[e.v], e.v })) continue;
				ll newK = SGS[y] + e.w + SGT[e.v];
				if (newK < key[e.v]) { H.erase({ key[e.v], e.v }); H.insert({ key[e.v] = newK, e.v }); }
			}

			for (auto& y : ONodes[i]) for (auto& x : nodes[y]) {
				edge& e = edges[x]; if (!H.count({ key[e.v], e.v })) continue;
				ll newK = PGD[y] + e.w + SGT[e.v];
				if (newK < key[e.v]) { H.erase({ key[e.v], e.v }); H.insert({ key[e.v] = newK, e.v }); }
			}

			if (H.begin()->first == INF) { continue; }
			if (H.begin()->first >= res) { res = H.begin()->first; resIdx = path[i]; }
		}

		return resIdx == -1 ? useless : resIdx;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m, s, t; cin >> n >> m >> s >> t;

	graph g(n); s--; t--;
	for (int i = 0; i < m; i++) {
		int a, b; ll d; cin >> a >> b >> d;
		a--; b--; g.add_edge(a, b, d);
	}

	cout << g.mostVitalPoint(s, t) + 1;
}