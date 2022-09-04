#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

vector<ll> a, b;
vector<int> ans;

const ll INF = 1e17;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<ll> path;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p, ll curA, ll curB, int prefLen) {
		if (path.empty()) { path.push_back(b[u]); }
		else { path.push_back(path.back() + b[u]); }
		
		curA += a[u];
		ans[u] = upper_bound(path.begin(), path.end(), curA) - path.begin();

		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, e.u, curA, curB, prefLen);
		}

		path.pop_back();
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int qq; cin >> qq;
	while (qq--) {
		a.clear(); b.clear(); ans.clear();
		int n; cin >> n; tree t(n);
		a.resize(n); b.resize(n); ans.resize(n);

		for (int i = 1; i <= n - 1; i++) {
			int p; cin >> p; p--;
			cin >> a[i] >> b[i];
			t.add_edge(i, p);
		}

		for (auto& e : t.nodes[0].edges) {
			t.dfs(e.v, 0, 0, 0, 0);
		}

		for (int i = 1; i < n; i++) { cout << ans[i] << ' '; }
		cout << '\n';
	}
}