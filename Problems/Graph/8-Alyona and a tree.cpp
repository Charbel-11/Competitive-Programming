#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e18;

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<node> nodes;
	vector<int> parent; vector<ll> dist;
	int root, n;

	vector<int> a;
	vector<int> add, cur;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		nodes.resize(n); 
		a.resize(n+1); add.resize(n+1); 
		cur.resize(n + 1); cur[0] = n;
	}

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void fill() {
		parent.resize(n);
		dist.resize(n, INF); dist[root] = 0;			
		queue<int> Q; Q.push(root);
		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto &e : nodes[cur].edges) {
				if (parent[cur] == e.v) { continue; }
				Q.push(e.v); parent[e.v] = cur;
				dist[e.v] = e.w + dist[cur];			
			}
		}
	}

	void dfs(int u, int d) {
		cur[d] = u;
		add[cur[d - 1]]++;
	
		int l = 1, r = d;
		while (l < r) {
			int m = (l + r) >> 1;
			if (dist[cur[m]] >= dist[u] - a[u])
				r = m;
			else
				l = m + 1;
		}

		add[cur[l - 1]]--;
		for (auto &e : nodes[u].edges) {
			if (parent[u] == e.v) { continue; }
			dfs(e.v, d + 1);
			add[u] += add[e.v];
		}
	}
};

int main() {
	int n; cin >> n;
	tree g(n);
	for (int i = 0; i < n; i++) { cin >> g.a[i]; }

	for (int i = 1; i < n; i++) {
		int p, w; cin >> p >> w; p--;
		g.add_edge(p, i, w);
	}

	g.fill(); g.dfs(0, 1);

	for (int i = 0; i < n; i++) {
		cout << g.add[i] << " ";
	} cout << endl;
}