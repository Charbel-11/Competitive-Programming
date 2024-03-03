#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;

const int N = 100005;
const ll mod = 1000 * 1000 * 1000 + 7;
int n, q, Sq, Mk;

struct DSU {
	vector<int> rank, parent;
	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}
	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
	bool operator < (const edge& rhs) const { return w < rhs.w; }
};

struct node { vector<edge> edges; };

struct graph {
	vector<vector<int>> anc, heavy;
	vector<node> nodes; int n = 0;
	vector<edge> edges; int m = 0;
	vector<int> depth;
	int root, lg2;

	graph(int _n) : n(_n), root(0) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n);
		anc.resize(n + 1, vector<int>(lg2 + 1, -1));
		heavy.resize(n + 1, vector<int>(lg2 + 1, -1));
		depth.resize(n, 0);
	}

	void add_edge(int u, int v, int w) {
		nodes[u].edges.emplace_back(u, v, w);
		nodes[v].edges.emplace_back(v, u, w);
		edges.emplace_back(u, v, w); m++;
	}

	void KruskalMST(vector<edge>& res) {
		sort(edges.begin(), edges.end());
		DSU dsu(n); res.clear(); int i = 0;
		while (i < m && res.size() != n - 1) {
			edge& e = edges[i];
			if (!dsu.merge(e.u, e.v)) { i++; continue; }
			res.push_back(e);
		}
	}

	//Need to call this first (after adding the edges)
	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root; heavy[root][0] = -INT_MAX;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur; heavy[e.v][0] = e.w;
				depth[e.v] = depth[cur] + 1;
				q.push(e.v); visited[e.v] = true;
			}
		}
		for (int i = 1; i <= lg2; i++) {
			for (int u = 0; u < n; u++) {
				anc[u][i] = anc[anc[u][i - 1]][i - 1];
				heavy[u][i] = max(heavy[u][i - 1], heavy[anc[u][i - 1]][i - 1]);
			}
		}
	}

	//Need to preprocess before using
	//Returns the LCA of nodes u and v with the largest weight on the path between u and v in O(logn)		
	int find(int& u, int& v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		int maxWeight = -1;
		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v]) {
				maxWeight = max(maxWeight, heavy[u][i]);
				u = anc[u][i];
			}
		}

		if (u == v) { return maxWeight; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				maxWeight = max(maxWeight, heavy[u][i]); u = anc[u][i];
				maxWeight = max(maxWeight, heavy[v][i]); v = anc[v][i];
			}
		}
		maxWeight = max(maxWeight, heavy[u][0]);
		maxWeight = max(maxWeight, heavy[v][0]);

		return maxWeight;
	}

	inline int findMax(int& u, int& v) {
		return find(u, v);
	}
};

struct point {
	int x, y, index;
	bool operator<(const point& p) const { return x == p.x ? y < p.y : x < p.x; }
};
struct nodeM {
	int value, p;
};

point p[N];
nodeM T[N];

int query(int x) {
	int r = INT_MAX, p = -1;
	for (; x <= n; x += (x & -x)) {
		if (T[x].value < r) {
			r = T[x].value;
			p = T[x].p;
		}
	}
	return p;
}
void modify(int x, int w, int p) {
	for (; x > 0; x -= (x & -x)) {
		if (T[x].value > w) {
			T[x].value = w;
			T[x].p = p;
		}
	}
}

inline int dist(point& p1, point& p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

vector<int> v; int a[N];

void manhattan(graph& g) {
	for (int i = 1; i <= n; ++i) { p[i].index = i; }
	for (int dir = 1; dir <= 4; ++dir) {
		if (dir == 2 || dir == 4) {
			for (int i = 1; i <= n; ++i) { swap(p[i].x, p[i].y); }
		}
		else if (dir == 3) {
			for (int i = 1; i <= n; ++i) { p[i].x = -p[i].x; }
		}
		sort(p + 1, p + 1 + n);

		v.clear();
		for (int i = 1; i <= n; ++i) {
			a[i] = p[i].y - p[i].x;
			v.push_back(a[i]);
		}
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		for (int i = 1; i <= n; ++i) { a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1; }
		for (int i = 1; i <= n; ++i) {
			T[i].value = INT_MAX;
			T[i].p = -1;
		}
		for (int i = n; i >= 1; --i) {
			int pos = query(a[i]);
			if (pos != -1) {
				g.add_edge(p[i].index - 1, p[pos].index - 1, dist(p[i], p[pos]));
			}
			modify(a[i], p[i].x + p[i].y, i);
		}
	}
}

inline bool query(int s, int t, int k, graph& g) {
	return g.findMax(s, t) <= k;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> q >> Sq >> Mk;
	for (int i = 1; i <= n; i++) { cin >> p[i].x >> p[i].y; }

	graph g(n);
	manhattan(g);
	vector<edge> MST;
	g.KruskalMST(MST);

	graph g2(n);
	for (auto& e : MST) { g2.add_edge(e.u, e.v, e.w); }
	g2.preprocess();

	ll As, Bs, Cs, At, Bt, Ct, Ak, Bk, Ck;
	cin >> As >> Bs >> Cs >> At >> Bt >> Ct >> Ak >> Bk >> Ck;

	ll ans = 0, pow2 = 2;

	ll s, sP, t, tP, k, kP; s = t = k = 0;
	while (Sq--) {
		sP = s; tP = t; kP = k; cin >> s >> t >> k;
		ans += pow2 * (query(s - 1, t - 1, k + 1, g2)); ans %= mod;
		pow2 = (pow2 << 1) % mod; q--;
	}

	while (q--) {
		ll ns, nt, nk;
		ns = (As * s) % n; ns += (Bs * sP); ns %= n; ns += Cs; ns %= n; ns++;
		nt = (At * t) % n; nt += (Bt * tP); nt %= n; nt += Ct; nt %= n; nt++;
		nk = (Ak * k) % Mk; nk += (Bk * kP); nk %= Mk; nk += Ck; nk %= Mk;

		ans += pow2 * (query(ns - 1, nt - 1, nk + 1, g2)); ans %= mod;

		sP = s; tP = t; kP = k;	s = ns; t = nt; k = nk;
		pow2 = (pow2 << 1) % mod;
	}

	cout << ans << '\n'; 
}