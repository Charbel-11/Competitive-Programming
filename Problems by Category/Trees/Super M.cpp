#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

vector<int> cities;

const ll INF = 1e17;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool target = 0; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<bool> dead;
	int root, n;
	int d1, d2, diameter;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); dead.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p, vector<int> &dist) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			dist[e.v] = dist[u] + 1;
			dfs(e.v, u, dist);
		}
	}

	void findDiameter() {
		diameter = 0; d1 = d2 = root;
		vector<int> dist1(n, -1), dist2(n, -1);
		dist1[root] = 0; dfs(root, -1, dist1);
		for (int i = 0; i < n; i++) {
			if (dist1[i] > diameter) { diameter = dist1[i]; d1 = i; }
		}
		dist2[d1] = 0; dfs(d1, -1, dist2);
		for (int i = 0; i < n; i++) {
			if (dist2[i] > diameter) { diameter = dist2[i]; d2 = i; }
			else if (dist2[i] == diameter && i < d2) { d2 = i; }
		}
	}

	int removeUseless(int u, int p) {
		int cur = nodes[u].target;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			int num = removeUseless(e.v, u);
			if (num == 0) { dead[e.v] = 1; }
			else { cur += num; }
		}
		return cur;
	}

	int getSize(int u, int p) {
		int res = 1;
		for (auto &e : nodes[u].edges) {
			if (e.v == p || dead[e.v]) { continue; }
			res += getSize(e.v, u);
		}
		return res;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	tree t(n); cities.resize(m);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	for (auto &x : cities) { cin >> x; x--; t.nodes[x].target = 1; }

	t.root = cities[0];
	t.removeUseless(cities[0], -1);

	int size = t.getSize(t.root, -1);
	int ans = 2 * (size - 1);
	t.findDiameter(); ans -= t.diameter;

	cout << min(t.d1, t.d2) + 1 << '\n' << ans << '\n';
}