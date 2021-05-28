#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; int w; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { ll v; vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	void dfs(int u, vector<int> &visited, vector<int> &ans) {
		visited[u] = true;
		for (auto &e : nodes[u].edges) {
			int v = e.v;
			if (!visited[v]) { dfs(v, visited, ans); }
		}
		ans.push_back(u);
	}
	vector<int> topological_sort() {
		vector<int> visited(n, false), ans;
		for (int i = 0; i < n; ++i)
			if (!visited[i]) { dfs(i, visited, ans); }
		reverse(ans.begin(), ans.end());
		return move(ans);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> a(n), b(n);
	ll ans = 0;
	for (auto &x : a) { cin >> x; }
	for (auto &x : b) { cin >> x; x--; }

	graph g(n);
	for (int i = 0; i < n; i++) {
		g.nodes[i].v = a[i];
		if (b[i] >= 0) { g.add_edge(i, b[i]); }
	}

	vector<int> topOrder = g.topological_sort();
	vector<int> pos, neg;
	for (int i = 0; i < n; i++) {
		int cur = topOrder[i];
		ans += g.nodes[cur].v;
		if (g.nodes[cur].v >= 0) {
			pos.push_back(cur);
			if (b[cur] >= 0) { g.nodes[b[cur]].v += g.nodes[cur].v; }
		}
		else { neg.push_back(cur); }
	}

	cout << ans << '\n';
	for (auto &x : pos) { cout << x + 1 << ' '; }
	reverse(neg.begin(), neg.end());
	for (auto &x : neg) { cout << x + 1 << ' '; }
	cout << '\n';
}