#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc;
	vector<node> nodes;
	vector<int> depth, subS;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 1.0)));
		nodes.resize(n); depth.resize(n, 0);
		subS.resize(n, 1);
		anc.resize(n + 1, vector<int>(lg2 + 1, -1));
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			subS[u] += subS[e.v];
		}
	}

	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur;
				depth[e.v] = depth[cur] + 1;
				q.push(e.v); visited[e.v] = true;
			}
		}
		for (int i = 1; i <= lg2; i++)
			for (int u = 0; u < n; u++)
				anc[u][i] = anc[anc[u][i - 1]][i - 1];
	}

	//Need to preprocess before using!
	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = anc[u][i];	//furthest parent found is 2^i
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				u = anc[u][i];
				v = anc[v][i];
			}
		}

		return anc[u][0];
	}

	int dist(int u, int v) {
		int lca = LCA(u, v);
		return depth[u] + depth[v] - 2 * depth[lca];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int tt; cin >> tt;
	while (tt--) {
		int n; cin >> n; tree t(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v;
			t.add_edge(u, v);
		}
		t.dfs(0, -1);
		t.preprocess();

		vector<ll> ans(n + 1, 0);
		ll cnt = 0; int l = 0, r = 1, rSize = 0;
		for (auto& e : t.nodes[0].edges) {
			ll cur = t.subS[e.v];
			ans[0] += (cur * (cur - 1)) / 2;

			if (t.LCA(e.v, 1) == e.v) { cur -= t.subS[1]; rSize = t.subS[e.v]; }
			ans[1] += cnt * cur + cur; cnt += cur;
		}

		for (int i = 2; i < n; i++) {
			if (t.LCA(l, i) == i || t.LCA(r, i) == i) { continue; }

			ll curL = t.subS[l], curR = t.subS[r];
			if (l == 0) { curL -= rSize; }

			if (t.LCA(r, i) == r) { curR -= t.subS[i]; r = i; }
			else if (t.LCA(l, i) == l && t.LCA(i, r) == 0) { curL -= t.subS[i]; l = i; }
			else { ans[i] = curL * curR; break; }
			ans[i] = curL * curR;
		}
		ans[n] = t.dist(l, r) == n - 1;

		for (auto& x : ans) { cout << x << " "; }
		cout << '\n';
	}
}