//https://codeforces.com/contest/1092/problem/F
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
const ll INF = 1e17;

vector<ll> a;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<ll> subtreeA, ans;
	int n;

	tree(int _n) : n(_n) { nodes.resize(n); subtreeA.resize(n, 0); ans.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, ll dist, int p) {
		subtreeA[u] = a[u];
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, dist + 1, u);
			subtreeA[u] += subtreeA[e.v];
		}
		ans[0] += dist * a[u];
	}

	void reroot(int u, int p) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			ans[e.v] = ans[u] - subtreeA[e.v];
			ans[e.v] += (subtreeA[u] - subtreeA[e.v]);

			subtreeA[u] -= subtreeA[e.v];
			subtreeA[e.v] += subtreeA[u];
			reroot(e.v, u);
			subtreeA[e.v] -= subtreeA[u];
			subtreeA[u] += subtreeA[e.v];
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	a.resize(n); for (auto &x : a) { cin >> x; }
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	t.dfs(0, 0, -1);
	t.reroot(0, -1);

	cout << *max_element(t.ans.begin(), t.ans.end()) << '\n';
}